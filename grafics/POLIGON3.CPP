//Graficas por computadora
//Practica 08: Poligonos
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>

struct Puntos{
   int x;
   int y;
   int color;
}punto;

Puntos p[5000],ladosP[10];
int opcion=0,count=0;

void modo(int modo){
   union REGS reg;
   reg.x.ax=modo;
   int86(0x10, &reg, &reg);
}
void pixel(int x, int y, int color){
   if((x>=0&&y>=0)&&(x<=640&&y<=480)){
      union REGS reg;
      reg.h.ah=0xc;
      reg.h.al=color;
      reg.h.bh=0;
      reg.x.cx=x;
      reg.x.dx=y;
      int86(0x10, &reg, &reg);
   }
}

void cursor(int opcion){
   union REGS reg;
   reg.x.ax=opcion;
   int86(0x33, &reg, &reg);
}

int lee_cursor(int *x, int *y, int modo){
   union REGS reg;
   reg.x.ax=3;
   int86(0X33, &reg, &reg);
   if(modo==0x3){
      reg.x.cx/=8;
      reg.x.dx/=8;
   }
   if(modo==0x13)
      reg.x.cx/=2;
   *x=reg.x.cx;
   *y=reg.x.dx;
   return(reg.x.bx);
}

int lee_pixel(int x, int y){
   union REGS reg;
   reg.h.ah=13;
   reg.x.bx=0;
   reg.x.cx=x;
   reg.x.dx=y;
   int86(0x10, &reg, &reg);
   return(reg.h.al);
}

void polar(int &x,int &y,int xc,int yc,int r,float a){
   float radian;
   radian=180/M_PI;
   x=xc+ceill(r*cos(a/radian));
   y=yc+ceill(r*sin(a/radian));
}

void lineaB(int px1,int py1,int px2,int py2,int col,int b){
   pixel(px1,py1,col);
   //-----------fin-------
   int pk,xk,yk,Ax,Ay;
   int incX,incY;//xFin,yFin;
   int c=0;
   //Calculos preliminares
   if(px1<px2)
      incX=1;
   else
      if(px1>px2)
	 incX=-1;
      else
	 incX=0;
   if(py1<py2)
      incY=1;
   else
      if(py1>py2)
	 incY=-1;
      else
	 incY=0;
   //Comienzan calculos para el algoritmo de Bresenham
   Ax=px1-px2;
   Ax=abs(Ax);
   Ay=py1-py2;
   Ay=abs(Ay);
   //comienza a dibujarse la linea de bresenham
   if(Ax>Ay){
      pk=(2*Ay)-Ax;
      xk=px1;
      yk=py1;
      do{
	if(pk<0){
	   xk+=incX;
	   pk=pk+(2*Ay);
	}else{
	   xk+=incX;yk+=incY;
	   pk=pk+2*(Ay-Ax);
	 }
	//Inicia seccion de bandera
	//0->captura, 1->dibuja, 2->dibuja lo capturado
	if(b==0){
	   //cLinea[c]=lee_pixel(xk,yk);
	   p[count].x=xk;
	   p[count].y=yk;
	   p[count].color=lee_pixel(xk,yk);
	   count++;
	}
	if(b==1)
	   pixel(xk,yk,col);
	/*if(b==2)
	   pixel(xk,yk,cLinea[c]);*/
	c++;
	//Finaliza seccion de bandera
      }while(c<=Ax);
   }else{
      pk=(2*Ax)-Ay;
      xk=px1;
      yk=py1;
      do{
	if(pk<0){
	   yk+=incY;
	   pk=pk+(2*Ax);
	}else{
	   yk+=incY;xk+=incX;
	   pk=pk+2*(Ax-Ay);
	 }
	//Inicia seccion de bandera
	//0->captura, 1->dibuja, 2->dibuja lo capturado
	if(b==0){
	   //cLinea[c]=lee_pixel(xk,yk);
	   p[count].x=xk;
	   p[count].y=yk;
	   p[count].color=lee_pixel(xk,yk);
	   count++;
	}
	if(b==1){
	   pixel(xk,yk,col);
	}
	/*if(b==2){
	   pixel(xk,yk,cLinea[c]);
	}*/
	c++;
	//Finaliza seccion de bandera
      }while(c<=Ay);
   }
}
void restaurar(){
   for(int i=0; i<count; i++)
      pixel(p[i].x,p[i].y,p[i].color);
   count=0;
}
void poligonos(int xc,int yc,int radio,float angulo,int c,int lados,int col){
   int an=360/lados;
   int x,y;
   cursor(0x2);
   for(int a=0;a<lados;a++){
      polar(x,y,xc,yc,radio,angulo);
      angulo+=an;
      punto.x =x; punto.y = y;
      ladosP[a]=punto;
   }
   if(c==0||c==1){
      for (a=0;a<lados;a++)
	 lineaB(ladosP[a].x,ladosP[a].y,ladosP[(a+1)%lados].x,ladosP[(a+1)%lados].y,col,c);
   }else
      restaurar();
   cursor(0x1);
}

//------------------------------M-A-I-N----------------------------------
void main(){
 modo(0x12);
 int radio,x,y,x1,y1,x2,y2,color=2;
 double angulo;
 double dx,dy;
 int lados=3,aux1,aux2;
 float radianes;
 cursor(0);
 cursor(1);
 while(!kbhit()){
    if(lee_cursor(&x,&y,0x12)==2){
       lados++;
       if(lados>8)
	  lados=3;
       delay(300);
    }
    if(lee_cursor(&x,&y,0x12)==3){
       color++;
       delay(300);
    }
    gotoxy(1,1);
    printf("Lados: %d,  Color: %d",lados,color);
    if(lee_cursor(&x1, &y1, 0x12)==1){
       radio=0;
       while(lee_cursor(&x2, &y2, 0X12)==1){
	  x=x1; aux1=x2;
	  y=y1; aux2=y2;
	  dx=x2-x1;
	  dy=y2-y1;
	  if(x!=x2 && y!=y2){
	     radio=sqrt((dx*dx)+(dy*dy));
	     radianes=atan2(dy,dx);
	     angulo=radianes*(180/M_PI);
	     poligonos(x1,y1,radio,angulo,1,lados,color);
	     poligonos(x1,y1,radio,angulo,0,lados,color);
	     while(lee_cursor(&x2,&y2,0x12)==1&&aux1==x&&aux2==y);
	     poligonos(x1,y1,radio,angulo,2,lados,color);
	  }
       }poligonos(x1,y1,radio,angulo,0,lados,color);
    }
 }
 getch();
}