//Graficas por computadora
//Practica: Curvas de SPLINE
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<MATH.H>
unsigned char cLinea[5000];
int x,y;

void modo(int modo){
   union REGS reg;
   reg.x.ax=modo; //guarda el valor en el registro
   int86(0x10,&reg,&reg); //ejecuta la interrupcion
}
void pixel(int x,int y,int color){
   union REGS reg;
   reg.h.ah=0xc; //valor del pixel
   reg.h.al=color; //color del pixel
   reg.h.bh=0; // pagina
   reg.x.cx=x; //coordenada x
   reg.x.dx=y; //coordenada y
   int86(0x10,&reg,&reg); //ejecuta la interrupcion
}
unsigned char lee_pixel(int x,int y){
   union REGS reg;
   reg.h.ah=13;//pixel
   reg.x.bx=0;
   reg.x.cx=x;
   reg.x.dx=y;
   int86(0x10,&reg,&reg);
   return(reg.h.al);//color del pixel
}
void cursor(int opc){
   union REGS reg;
   reg.x.ax=opc;//0=init, 1=show, 2=hide
   int86(0x33,&reg,&reg);
}
int lee_cursor(int *x,int *y,int modo){
   union REGS reg;
   reg.x.ax=3; //lee el estado
   int86(0x33,&reg,&reg);

   if(modo==0x3){
      reg.x.cx/=8;
      reg.x.dx/=8;
   }
   if(modo==0x13)
      reg.x.cx/=2;
   *x=reg.x.cx;
   *y=reg.x.dx;
   return(reg.x.bx);
   //Return: 0=ninguno, 1=izquierdo, 2=derecho, 3=ambos
}
void lineaB(int px1,int px2,int py1,int py2,int col,int b){
   cursor(0x2);
   pixel(px1,py1,col);

   int pk,xk,yk,Ax,Ay;
   int incX,incY;
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
	if(b==0)
	   cLinea[c]=lee_pixel(xk,yk);
	if(b==1)
	   pixel(xk,yk,col);
	if(b==2)
	   pixel(xk,yk,cLinea[c]);
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
	if(b==0)
	   cLinea[c]=lee_pixel(xk,yk);
	if(b==1)
	   pixel(xk,yk,col);
	if(b==2)
	   pixel(xk,yk,cLinea[c]);
	c++;
      }while(c<Ay);
   }
   cursor(0x1);
}
void curva(int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int color,int bn){
   double time;
   int xx,yy;
   for(time=0;time<=1.0;time+=0.001){
      xx=pow(1-time,3)*x0+3*time*pow(1-time,2)*x1+3*pow(time,2)*(1-time)*x2+pow(time,3)*x3;
      yy=pow(1-time,3)*y0+3*time*pow(1-time,2)*y1+3*pow(time,2)*(1-time)*y2+pow(time,3)*y3;
      //Inicia seccion de bandera
      if(bn==0)
	 cLinea[time*1000]=lee_pixel(xx,yy);
      if(bn==1)
	 pixel(xx,yy,color);
      if(bn==2)
	 pixel(xx,yy,cLinea[time*1000]);
   }
}
/*****************************-M-A-I-N-******************************/
void main(){
 int p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y,color=2;
 int p1xn,p1yn,p2xn,p2yn,p3xn,p3yn;
 int clicBan=0;
 clrscr();
 modo(0x4);
 modo(0x12);
 cursor(0);
 cursor(1);
 while(!kbhit()){
    if(lee_cursor(&x,&y,0x12)==2)
       color++;
    if(lee_cursor(&x,&y,0x12)==1){
       if(clicBan==0){
	  clicBan++;
	  p0x=x,p0y=y;
	  p3x=x;
	  p3y=y;
	  p3xn=x;
	  p3yn=y;
	  lineaB(p0x,p3x,p0y,p3y,color,0);
	  while(lee_cursor(&x,&y,0x12)==1){
	     p3x=x;
	     p3y=y;
	     lineaB(p0x,p3xn,p0y,p3yn,color,2);
	     lineaB(p0x,p3x,p0y,p3y,color,0);
	     lineaB(p0x,p3x,p0y,p3y,color,1);
	     while(lee_cursor(&x,&y,0x12)==1&&p3x==x&&p3y==y);
	     p3xn=p3x;
	     p3yn=p3y;
	  }
       }
       if(clicBan==1){
	  clicBan++;
	  p1x=x,p1y=y;
	  p1xn=x,p1yn=y;
	  curva(p0x,p0y,p1x,p1y,p3x,p3y,p3x,p3y,color,0);
	  while(lee_cursor(&x,&y,0x12)==1){
	     p1x=x;
	     p1y=y;
	     curva(p0x,p0y,p1xn,p1yn,p3x,p3y,p3x,p3y,color,2);
	     curva(p0x,p0y,p1x,p1y,p3x,p3y,p3x,p3y,color,0);
	     curva(p0x,p0y,p1x,p1y,p3x,p3y,p3x,p3y,color,1);
	     while(lee_cursor(&x,&y,0x12)==1&&p1x==x&&p1y==y);
	     p1xn=p1x;
	     p1yn=p1y;
	  }
       }
       if(clicBan==2){
	  clicBan=0;
	  p2x=x,p2y=y;
	  p2xn=x,p2yn=y;
	  curva(p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y,color,0);
	  while(lee_cursor(&x,&y,0x12)==1){
	     p2x=x;
	     p2y=y;
	     curva(p0x,p0y,p1x,p1y,p2xn,p2yn,p3x,p3y,color,2);
	     curva(p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y,color,0);
	     curva(p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y,color,1);
	     while(lee_cursor(&x,&y,0x12)==1&&p2x==x&&p2y==y);
	     p2xn=p2x;
	     p2yn=p2y;
	  }
       }
    }
 }
}