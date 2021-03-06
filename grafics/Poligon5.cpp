//Graficas por computadora
//Practica 08: Poligonos
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>

typedef struct{
   int x;
   int y;
   int color;
}Puntos;

Puntos punto,arrPoint[5000],lados[10];
int x,y,contG=0;

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

void polar(int xc,int yc,int r,float a){
   float radian;
   radian=180/M_PI;
   punto.x=xc+ceill(r*cos(a/radian));
   punto.y=yc+ceill(r*sin(a/radian));
}

void lineaB(int px1,int py1,int px2,int py2,int col,int b){
   //cursor(0x2);
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
	//0->captura, 1->dibuja, 2->dibuja con lo capturado
	if(b==0){
	   //cLinea[c]=lee_pixel(xk,yk);
	   arrPoint[contG].x=xk;
	   arrPoint[contG].y=yk;
	   arrPoint[contG].color=col;
	   contG++;
	}
	if(b==1)
	   pixel(xk,yk,col);
	/*if(b==2)
	   pixel(xk,yk,cLinea[c]);
	*/
	//Finaliza seccion de bandera
	c++;
      }while(c<Ax);
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
	if(b==0){
	   //cLinea[c]=lee_pixel(xk,yk);
	   arrPoint[contG].x=xk;
	   arrPoint[contG].y=yk;
	   arrPoint[contG].color=col;
	   contG++;
	}
	if(b==1)
	   pixel(xk,yk,col);
	/*if(b==2)
	   pixel(xk,yk,cLinea[c]);
	*/
	//Finaliza seccion de bandera
	c++;
      }while(c<Ay);
   }
   //cursor(0x1);
}

void polys(int xc,int yc,int radio,float angulo,int caras,int c,int ban){
   cursor(0x2);
   int l,ang=360/caras;

   for(l=0;l<caras;l++){
      polar(xc,yc,radio,angulo);
      angulo+=ang;
      lados[l]=punto;
   }
   if(ban!=2){
      for(l=0;l<caras-1;l++)
	 lineaB(lados[l].x,lados[l].y,lados[l+1].x,lados[l+1].y,c,ban);
      lineaB(lados[l].x,lados[l].y,lados[0].x,lados[0].y,c,ban);
   }else{
      for(l=0;l<contG;l++)
	 pixel(arrPoint[l].x,arrPoint[l].y,arrPoint[l].color);
      contG=0;
   }
   cursor(0x1);
}

//------------------------------M-A-I-N----------------------------------
void main(){
 int xc,yc;
 int sides=3,color=2,radio,radAnt;
 float/*double*/ radianes;
 int xAct,yAct,xAnt,yAnt;
 double dx,dy,angulo,angAnt;
 clrscr();
 modo(0x4);
 modo(0x12);
 cursor(0);
 cursor(1);
 while(!kbhit()){
    if(lee_cursor(&x,&y,0x12)==2){
       sides++;
       if(sides>8)
	  sides=3;
       delay(300);
    }
    if(lee_cursor(&x,&y,0x12)==3){
       color++;
       delay(300);
    }
    gotoxy(1,1);
    printf("Lados: %d,  Color: %d",sides,color);
    if(lee_cursor(&x,&y,0x12)==1){
       xc=x;yc=y;
       xAct=x;yAct=y;
       xAnt=x;yAnt=y;
       radio=0;
       while(lee_cursor(&x,&y,0X12)==1){
	  xAct=x;
	  yAct=y;
	  dx=xAct-xc;
	  dy=yAct-yc;
	  if(dx!=0||dy!=0){
	     radio=sqrt((dx*dx)+(dy*dy));
	     radianes=atan2(dy,dx);
	     angulo=radianes*(180/M_PI);
	     polys(xc,yc,radAnt,angAnt,sides,color,2);//ant
	     polys(xc,yc,radio,angulo,sides,color,0);//act
	     polys(xc,yc,radio,angulo,sides,color,1);//act
	     while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
	     xAnt=xAct;
	     yAnt=yAct;
	     dx=xAnt-xc;
	     dy=yAnt-yc;
	     radAnt=sqrt((dx*dx)+(dy*dy));
	     radianes=atan2(dy,dx);
	     angAnt=radianes*(180/M_PI);
	  }
       }
    }
 }
  modo(0x3);
}