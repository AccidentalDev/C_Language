//Carlos Francisco Camacho Uribe
//Taller de Graficas por Computadora
//Practica 4
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>
void main(){
 int Cx,Dx,Cy,Dy,color,x,y,k=0;
 int yTx;
 float r,pk;
 int gdriver,gmode,errorcode;
 char op,*tempstr;
 do{
   gdriver=9;gmode=2;
   clrscr();
   printf("\n\tNOTA: El rango es de x=320 a 640 y=0 a 240, a 16 colores\n\t");
   printf("\n\tEscribe la coordenada Cx: ");
   scanf("%d",&Cy);
   printf("\n\tEscribe la coordenada Cy: ");
   scanf("%d",&Cx);
   printf("\n\tEscribe la coordenada Dx: ");
   scanf("%d",&Dy);
   printf("\n\tEscribe la coordenada Dy: ");
   scanf("%d",&Dx);
   printf("\n\tEscribe el color: ");
   scanf("%d",&color);
   initgraph(&gdriver,&gmode,"e:\\tc\\bgi");
   errorcode=graphresult();
   if(errorcode!=grOk){
      printf("\n\tError grafico: %s\n", grapherrormsg(errorcode));
   }else{
      setcolor(7);
      r=sqrt(pow((Dx-Cx),2)+pow((Dy-Cy),2));
      outtextxy(10,20,"C = (");
      outtextxy(48,20,itoa(Cy,tempstr,10));
      outtextxy(72,20,",");outtextxy(80,20,itoa(Cx,tempstr,10));
      outtextxy(104,20,")");
      outtextxy(10,30,"D = (");
      outtextxy(48,30,itoa(Dy,tempstr,10));
      outtextxy(72,30,",");outtextxy(80,30,itoa(Dx,tempstr,10));
      outtextxy(104,30,")");
      outtextxy(10,40,"r = ");outtextxy(44,40,itoa(r,tempstr,10));
      pk=(5/4)-r;
      y=r;
      x=Cx;
      y=y+Cy;
      outtextxy(10,200,"K   Pk+1   Xk+1   Yk+1");
      outtextxy(10,210,itoa(k,tempstr,10));
      outtextxy(100,210,itoa(x,tempstr,10));
      outtextxy(157,210,itoa(y,tempstr,10));
      yTx=210;
      putpixel(x,y,color);
      do{
	 if(pk<0){
	    x++;
	    pk=pk+(2*x)+1;
	 }else{
	    x++;y--;
	    pk=pk+(2*x)+1-(2*y);
	 }
	 k++;
	 yTx+=10;
	 outtextxy(10,yTx,itoa(k,tempstr,10));
	 outtextxy(100,yTx,itoa(x,tempstr,10));
	 outtextxy(157,yTx,itoa(y,tempstr,10));
	 putpixel(x,y,color);
      }while(x<=y);
      getch();
      closegraph();
    }
   printf("\n\t¨Dibujar otro circulo? (s/n): ");
   op=getch();
   fflush(stdin);
 }while(op!='n');
}