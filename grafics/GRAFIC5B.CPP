//Graficas por computadora
//Practica 05: Linea de Bresenham mejorada
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<MATH.H>
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
void lineaB(int px1,int px2,int py1,int py2,int col){
   int pk,xk,yk,Ax,Ay;
   int incX,incY,xFin,yFin;
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
   pk=(2*Ay)-Ax;
   //comienza a dibujarse la linea de bresenham
   if(Ax>Ay){
      /*if(px1>px2){
	 xk=px2;
	 yk=py2;
	 xFin=px1;
      }else{*/
	 xk=px1;
	 yk=py1;
	 xFin=px2;
      //}
      do{
	pixel(xk,yk,col);
	if(pk<0){
	   xk+=incX;
	   pk=pk+(2*Ay);
	}else{
	   xk+=incX;yk+=incY;
	   pk=pk+(2*Ay)-(2*Ax);
	 }
      }while(xk<=xFin);
   }else{
      if(py1>py2){
	 xk=px2;
	 yk=py2;
	 yFin=py1;
      }else{
	 xk=px1;
	 yk=py1;
	 yFin=py2;
      }
      do{
	pixel(xk,yk,col);
	if(pk<0){
	   yk+=incY;
	   pk=pk+(2*Ax);
	}else{
	   yk+=incY;xk+=incX;
	   pk=pk+(2*Ax)-(2*Ay);
	 }
      }while(yk<=yFin);
   }
   getch();
}
/*****************************-M-A-I-N-******************************/
void main(){
 int x1,x2,y1,y2,color;
 char op;
 do{
   clrscr();
   printf("\n\tLINEA DE BRESENHAM\n\t");
   printf("\n\tNOTA: El rango es de 320x200 a 256 colores\n\t");
   printf("\n\tEscribe la coordenada x1: ");
   scanf("%d",&x1);
   printf("\n\tEscribe la coordenada y1: ");
   scanf("%d",&y1);
   printf("\n\tEscribe la coordenada x2: ");
   scanf("%d",&x2);
   printf("\n\tEscribe la coordenada y2: ");
   scanf("%d",&y2);
   printf("\n\tEscribe el color: ");
   scanf("%d",&color);
   modo(0x13);
   lineaB(x1,x2,y1,y2,color);
   modo(0x3);
   printf("\n\t¨Dibujar otra linea? (s/n): ");
   op=getch();
 }while(op!='n');
}