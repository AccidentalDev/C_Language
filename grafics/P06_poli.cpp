/*
OSCAR MARTIN RAMOS RAMIREZ
ING. EN COMPUTACION
C:397455155
*/
#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include "stdio.h"
#include <math.h>
#include "dos.h"
#include "ctype.h"
#include <fstream.h>
#include <graphics.h>
#include <alloc.h>


void modo(int modo){
   union REGS reg;
   reg.x.ax=modo;
   int86(0x10, &reg, &reg);
}
void pixel(int x, int y, int color){
   if((x>=0 && y>=0)&&(x<=640 && y<=480)){
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
/*************************************************************************/
struct Puntos{
   int x;
   int y;
   int color;
}punto;

Puntos p[5000],ladosP[10];
int /*arr[10000],*/ count=0,/* c=0,*/opcion =0;
//void polar(int &x, int &y,int xc, int yc, int r, float a);

void guarda(int x, int y){
   p[count].x =x;
   p[count].y =y;
   p[count++].color =lee_pixel(x,y);
}

void restaurar() //pone lo que habia abajo
{
   for(int i=0; i<count; i++)
      pixel(p[i].x,p[i].y,p[i].color);
   count = 0;
}

/*void guarda(int arr[], int x, int y)
{
	arr[c]=lee_pixel(x,y);c++;
}*/
void polar(int &x, int &y,int xc, int yc, int r, float a){
   float radian;
   radian=180/M_PI;
   x=xc+ceill(r*cos(a/radian));
   y=yc+ceill(r*sin(a/radian));
}
void Mlinea(int xa,int ya,int xb,int yb, int color, int bandera){
   int p, auxx, auxy, x, y,r,incx,incy,incxd,incyd;
   int dx;  //constantes de incremento
   int dy;
   auxx=1;//es el incremento en x
   auxy=1;// es el incremento en y, 1 de rigor
   dy=yb-ya;
   if(dy<0){
      auxy=-auxy; // si es pendiente negativa se decrementa y
      dy=-dy;//aqui es el valor absoluto
   }
   incy=auxy;// incremento en y
   dx=xb-xa;
   if(dx<0){
      auxx=-auxx;
      dx= - dx;
   }
   incx=auxx;
   if(dx>=dy){
      auxy=0;//tambien entra aqui en el caso de un solo punto
   }
   else{
      auxx=0;  // aqui es para la vertical
      x=dx;
      dx=dy;
      dy=x;
   }
   incxd=auxx; // variables en caso de que sea una linea recta
   incyd=auxy; // ya sea horizontal o vertical
   //valores iniciales
   x = xa;// donde se pone el primer pixel
   y = ya;

   if(bandera && (opcion ==2 || opcion==9)){
      guarda(x,y);// guarda punto si esta en 1 sino no
      pixel(x,y,color);
   }
   else
      if(bandera){
	 guarda(x,y);// guarda punto si esta en 1 sino no
      }
      else
	 pixel(x,y,color);
      int i=0;
      p = 2*dy-dx;  //parametro inicial
      while( i < dx ){
	 if(p<0){
	    x = x + incxd;  //incremento x sin mamadas
	    y = y + incyd;
	    p= p + 2*dy;
	    if(bandera  &&(opcion ==2|| opcion==9)){
	       guarda(x,y);// guarda punto si esta en 1 sino no
	       pixel(x,y,color);
	    }
	    else
	       if(bandera){
		  guarda(x,y);// guarda punto si esta en 1 sino no
	       }
	       else
		  pixel(x,y,color);
	 }
	 else{
	    y = y+incy;
	    x = x+incx;
	    p=p+2*(dy-dx);
	    if(bandera  &&(opcion ==2|| opcion==9)){
	       guarda(x,y);// guarda punto si esta en 1 sino no
	       pixel(x,y,color);
	    }
	    else
	       if(bandera){
		  guarda(x,y);// guarda punto si esta en 1 sino no
	       }
	       else
		  pixel(x,y,color);
		  // JALA PERO NO SABEMOS QUE PEDO
	 }i++;
      }
}

void poligonos(int xc,int yc,int radio, float angulo,int c,int lados){
   int an=360/lados;
   int x,y;
   for(int a=0;a<lados;a++){
      polar(x,y,xc,yc,radio,angulo);
      angulo+=an;
      punto.x =x; punto.y = y;
      ladosP[a]=punto;
   }
   if(c==2){
      for(a=0;a<lados;a++)
	 Mlinea(ladosP[a].x,ladosP[a].y,ladosP[(a+1)%lados].x,ladosP[(a+1)%lados].y,15,0);
   }
   if(c==0)
      restaurar();
   if(c==1){
      for(a=0;a<lados;a++)
	 Mlinea(ladosP[a].x,ladosP[a].y,ladosP[(a+1)%lados].x,ladosP[(a+1)%lados].y,15,1);
   }
}// fin poligonos
/*************************************************************************/
void main(void){
   modo(0x12);
   int r,radio,x,y,x1,y1,x2,y2;
   double angulo;
   cout <<"CANTIDAD DE LADOS: ";
   cin>>r;
   int lados=r;
   int aux1,aux2;
   cursor(0);//inicializo el mouse
   cursor(1);//muestro el cursor
   while (!kbhit())//mientras no presione ninguna tecla
   {
      if(lee_cursor(&x1, &y1, 0x12)==1){
	 radio=0;
	 while(lee_cursor(&x2, &y2, 0X12)==1){
	    x=x1; aux1=x2;
	    y=y1; aux2=y2;
	    double dx=x2-x1;
	    double dy=y2-y1;
	    cursor(1);//oculta el cursor
	    // por que da 0 la primera iteracion
	    if(x!=x2 && y!=y2){
	       radio=sqrt((dx*dx)+(dy*dy));
	       float radianes=atan2(dy,dx);//calcula el a
	       //angulo
	       //convierte a grados
	       angulo=radianes*(180/M_PI);cursor(2);
	       poligonos(x1,y1,radio,angulo,1,lados);
	       poligonos(x1,y1,radio,angulo,2,lados);
	       while(aux1==x2 &&aux2==y2&& !kbhit()){
		  lee_cursor(&aux1,&aux2,0x12);
		  cursor(1);
	       }cursor(2);
	       poligonos(x1,y1,radio,angulo,0,lados);
	       cursor(2);
	    }
	 }poligonos(x1,y1,radio,angulo,2,lados);
      }cursor(1);//muestra el cursor
   }
   getch();
}