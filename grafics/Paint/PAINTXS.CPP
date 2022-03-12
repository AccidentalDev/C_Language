#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<MATH.H>

int x,y;

void modo(int modo){
   union REGS reg;
   reg.x.ax=modo; //guarda el valor en el registro
   int86(0x10,&reg,&reg); //ejecuta la interrupcion
}
void pixel(int x,int y,int color){
   if((x>56&&y>=1)&&(x<639&&y<424)){
      union REGS reg;
      reg.h.ah=0xc; //valor del pixel
      reg.h.al=color; //color del pixel
      reg.h.bh=0; // pagina
      reg.x.cx=x; //coordenada x
      reg.x.dx=y; //coordenada y
      int86(0x10,&reg,&reg); //ejecuta la interrupcion
   }
}
void pixel2(int x,int y,int color){
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
int clicBoton(int px,int py){
   if((px>8&&py>37)&&(px<48&&py<77))
      return -1;
   else
      return 0;
}
void lineaB(int px1,int py1,int px2,int py2,int col){
   pixel2(px1,py1,col);

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
	pixel2(xk,yk,col);
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
	pixel2(xk,yk,col);
	c++;
      }while(c<Ay);
   }
}
void layout(){
   int i,j,color=0;
   //Area de trabajo
   lineaB(56,0,56,424,15);
   lineaB(639,0,639,424,15);
   lineaB(56,424,639,424,15);
   lineaB(56,0,639,0,15);
   //rellenos
   for(i=9;i<48;i++)
      for(j=58;j<77;j++)
	 pixel2(i,j,8);//abrir-guardar
   for(i=9;i<48;i++)
      for(j=92;j<171;j++)
	 pixel2(i,j,8);//herramientas
   //relleno barra de colores
   for(int a=74;a<233;a+=20)
      for(j=433;j<472;j++){
	 for(i=a;i<a+19;i++)
	    pixel2(i,j,color);
	 if(j==452||j==471)
	    color++;
      }
   //Lineas verticales de la barra de herramientas
   for(i=8;i<50;i+=40)
      lineaB(i,37,i,77,15);
   lineaB(28,57,28,77,15);
   for(i=8;i<50;i+=20)
      lineaB(i,91,i,171,15);
   //lineas horizontales de la barra de herramientas
   for(i=37;i<80;i+=20)
      lineaB(8,i,48,i,15);
   for(i=91;i<175;i+=20)
      lineaB(8,i,48,i,15);
   //lineas horizontales de la barra de colores
   for(i=432;i<475;i+=20)
      lineaB(73,i,233,i,15);
   //lineas verticales de la barra de colores
   for(i=73;i<235;i+=20)
      lineaB(i,432,i,472,15);
   //*******Letras de exit*******
   //letra E
   for(i=42;i<53;i+=10)
      lineaB(12,i,17,i,4);
   lineaB(12,47,15,47,4);
   lineaB(12,42,12,52,4);
   //letra X
   lineaB(20,42,26,52,4);
   lineaB(20,52,26,42,4);
   //letra I
   for(i=42;i<53;i+=10)
      lineaB(30,i,34,i,4);
   lineaB(32,42,32,52,4);
   //letra T
   lineaB(38,42,44,42,4);
   lineaB(41,42,41,52,4);
}
/******************************-M-A-I-N-******************************/
void main(){
 int sel=0,xx,yy;
 clrscr();
 modo(0x4);
 modo(0x12);
 cursor(0);
 cursor(1);
 layout();
 do{
    if(lee_cursor(&x,&y,0x12)==1){
       xx=x;yy=y;
       if((xx>56&&yy>=0)&&(xx<640&&yy<424)){
	  //Dibuja algo
	  pixel(xx,yy,6);
       }else{
	  sel=clicBoton(xx,yy);
	  delay(300);
       }
    }
 }while(sel!=-1);
 getch();
 modo(0x3);
}