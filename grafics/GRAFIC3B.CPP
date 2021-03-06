//Carlos Francisco Camacho Uribe
//Taller de Graficas por Computadora
//Practica 3
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>
void main(){
 int x1,x2,y1,y2,color;
 int pk,xk,yk,Ax,Ay;
 int gdriver,gmode,errorcode;
 char op,*tempstr;
 do{
   gdriver=9;gmode=2;
   clrscr();
   printf("\n\tLINEA DE BRESENHAM\n\t");
   printf("\n\tNOTA: El rango es de 320x240 a 16 colores\n\t");
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
   initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
   errorcode=graphresult();
   if(errorcode!=grOk){
      printf("\n\tError grafico: %s\n", grapherrormsg(errorcode));
   }else{
      setcolor(7);
      outtextxy(10,300,"Carlos Francisco Camacho Uribe");
      outtextxy(10,310,"Taller de Graficas por Computadora");
      outtextxy(10,320,"Practica 3: Linea de Bresenham");
      //Comienzan calculos para el algoritmo de Bresenham
      xk=x1;yk=y1;
      Ax=x1-x2;
      Ax=abs(Ax);
      Ay=y1-y2;
      Ay=abs(Ay);
      pk=(2*Ay)-Ax;
      //Sigue impresion de P1, P2, x y y
      outtextxy(370,20,"P1 = (");//10
      outtextxy(418,20,itoa(x1,tempstr,10));//48
      outtextxy(442,20,",");outtextxy(450,20,itoa(y1,tempstr,10));//72,80
      outtextxy(474,20,")");//104
      outtextxy(370,30,"P2 = (");//10
      outtextxy(418,30,itoa(x2,tempstr,10));//48
      outtextxy(442,30,",");outtextxy(450,30,itoa(y2,tempstr,10));//72,80
      outtextxy(474,30,")");//104
      outtextxy(370,40,"x = ");//10
      outtextxy(408,40,itoa(Ax,tempstr,10));//48
      outtextxy(370,50,"y = ");//10
      outtextxy(408,50,itoa(Ay,tempstr,10));//48
      //comienza a dibujarse la linea de bresenham
      do{
	//printf("\t\t\t\t\tXk= %d      Yk= %d\n",xk,yk);
	putpixel(xk,yk,color);
	if(pk<0){
	   xk++;
	   pk=pk+(2*Ay);
	}else{
	   xk++;yk++;
	   pk=pk+(2*Ay)-(2*Ax);
	 }
      }while(xk<=x2&&yk<=y2);
      getch();
      closegraph();
   }
   printf("\n\t�Dibujar otra linea? (s/n): ");
   op=getch();
 }while(op!='n');
}