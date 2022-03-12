//Graficas por computadora
//Practica 05: Linea de Bresenham mejorada
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
   //Revisar estos codigos
   cursor(0x2);
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
	//Finaliza seccion de bandera
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
	c++;
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
	if(b==0)
	   cLinea[c]=lee_pixel(xk,yk);
	if(b==1)
	   pixel(xk,yk,col);
	if(b==2)
	   pixel(xk,yk,cLinea[c]);
	c++;
      }while(c<=Ay);
   }
   cursor(0x1);
}
/*****************************-M-A-I-N-******************************/
void main(){
 int xIni,xAct,yIni,yAct,color=2;
 int xAnt,yAnt;
 clrscr();
 modo(0x4);
 modo(0x12);
 cursor(0);
 cursor(1);
 while(lee_cursor(&x,&y,0x12)!=3){
    if(lee_cursor(&x,&y,0x12)==2)
       color++;
    if(lee_cursor(&x,&y,0x12)==1){
       xIni=x;
       yIni=y;
       xAct=x;
       yAct=y;
       xAnt=x;
       yAnt=y;
       lineaB(xIni,xAct,yIni,yAct,color,0);
       while(lee_cursor(&x,&y,0x12)==1){
	  xAct=x;
	  yAct=y;
	  lineaB(xIni,xAnt,yIni,yAnt,color,2);
	  lineaB(xIni,xAct,yIni,yAct,color,0);
	  lineaB(xIni,xAct,yIni,yAct,color,1);
	  while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
	  xAnt=xAct;
	  yAnt=yAct;
       }
    }
 }
}