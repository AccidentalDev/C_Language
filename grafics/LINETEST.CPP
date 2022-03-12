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
void layout(int px1,int px2,int py1,int py2,int col){
   int pk,xk,yk,Ax,Ay;
   //Comienzan calculos para el algoritmo de Bresenham
   xk=px1;yk=py1;
   Ax=px1-px2;
   Ax=abs(Ax);
   Ay=py1-py2;
   Ay=abs(Ay);
   pk=(2*Ay)-Ax;
   //comienza a dibujarse la linea de bresenham
   do{
     pixel(xk,yk,col);
     if(pk<0){
	xk++;
	pk=pk+(2*Ay);
     }else{
	xk++;yk++;
	pk=pk+(2*Ay)-(2*Ax);
      }
   }while(xk<=px2||yk<=py2);
   delay(100);//1500 = 1.5 segundos
}
/*****************************-M-A-I-N-******************************/
void main(){
 int x1=5,x2=280,y1=5,y2=6,color=16;
 modo(0x13);
 for(int i=0;i<241;i++){
    layout(x1,x2,y1,y2,color);
    color++;
    y2++;
 }
 pixel(20,80,2);
 getch();
 modo(0x3);
 printf("\n\tPress any key to exit");
 getch();
}