//Graficas por computadora
//Practica 07: Elipses por punto medio con mouse
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<MATH.H>
unsigned char cLinea[2000][4];
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

void puntos(int xc,int yc,int x,int y,int c,int cont,int ban){
   if(ban==0){
      cLinea[cont][0]=lee_pixel(xc+x,yc+y);
      cLinea[cont][1]=lee_pixel(xc-x,yc+y);
      cLinea[cont][2]=lee_pixel(xc+x,yc-y);
      cLinea[cont][3]=lee_pixel(xc-x,yc-y);
   }
   if(ban==1){
      pixel(xc+x,yc+y,c);
      pixel(xc-x,yc+y,c);
      pixel(xc+x,yc-y,c);
      pixel(xc-x,yc-y,c);
   }
   if(ban==2){
      pixel(xc+x,yc+y,cLinea[cont][0]);
      pixel(xc-x,yc+y,cLinea[cont][1]);
      pixel(xc+x,yc-y,cLinea[cont][2]);
      pixel(xc-x,yc-y,cLinea[cont][3]);
   }
}
void elipse(int xc,int yc,long rx,long ry,int color,int b){
   long p,px,py,rx2,ry2,x2rx2,x2ry2;
   int x,y;
   int contador=0;
   cursor(0x2);
   rx2=rx*rx;
   ry2=ry*ry;
   x2rx2=2*rx2;
   x2ry2=2*ry2;
   //Inician calculos para region 1
   x=0;
   y=ry;
   puntos(xc,yc,x,y,color,contador,b);
   contador++;
   p=ceil(ry2-rx2*ry+(0.25*rx2));
   px=0;
   py=x2rx2*y;
   while(px<py){
      x++;
      px+=x2ry2;
      if(p>=0){
	 y--;
	 py-=x2rx2;
      }
      if(p<0)
	 p+=ry2+px;
      else
	 p+=ry2+px-py;
      puntos(xc,yc,x,y,color,contador,b);
      contador++;
   }
   //Inician calculos para region 2
   p=ceil(ry2*(x+0.5)*(x+0.5)+rx2*(y-1)*(y-1)-rx2*ry2);
   while(y>0){
      y--;
      py-=x2rx2;
      if(p<=0){
	 x++;
	 px+=x2ry2;
      }
      if(p>0)
	 p+=rx2-py;
      else
	 p+=rx2-py+px;
      puntos(xc,yc,x,y,color,contador,b);
      contador++;
   }
   cursor(0x1);
}
/******************************-M-A-I-N-******************************/
void main(){
 int xc,yc,color=2;
 long rxAnt,rxAct,ryAnt,ryAct;
 int xAct,yAct,xAnt,yAnt;
 clrscr();
 modo(0x4);
 modo(0x12);
 cursor(0);
 cursor(1);
 while(lee_cursor(&x,&y,0x12)!=3){
    if(lee_cursor(&x,&y,0x12)==2){
       color++;
       delay(300);
    }
    gotoxy(1,1);
    printf("Color: %d",color);
    if(lee_cursor(&x,&y,0x12)==1){
       xc=x;yc=y;
       xAct=x;
       yAct=y;
       xAnt=x;
       yAnt=y;
       rxAnt=abs(xc-x);
       ryAnt=abs(yc-y);
       elipse(xc,yc,rxAnt,ryAnt,color,0);
       while(lee_cursor(&x,&y,0x12)==1){
	  xAct=x;
	  yAct=y;
	  rxAct=abs(xc-xAct);
	  ryAct=abs(yc-yAct);
	  if(xc+rxAct>=640||xc-rxAct<=0){
	     elipse(xc,yc,rxAnt,ryAnt,color,2);//ant,2
	     elipse(xc,yc,rxAct,ryAct,color,0);//act,0
	     elipse(xc,yc,rxAct,ryAct,color,1);//act,1
	     while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
	     yAnt=yAct;
	     ryAnt=abs(yc-yAnt);
	  }
	  if(yc+ryAct>=480||yc-ryAct<=0){
	     elipse(xc,yc,rxAnt,ryAnt,color,2);//ant,2
	     elipse(xc,yc,rxAct,ryAct,color,0);//act,0
	     elipse(xc,yc,rxAct,ryAct,color,1);//act,1
	     while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
	     xAnt=xAct;
	     rxAnt=abs(xc-xAnt);
	  }
	  else{
	     elipse(xc,yc,rxAnt,ryAnt,color,2);//ant,2
	     elipse(xc,yc,rxAct,ryAct,color,0);//act,0
	     elipse(xc,yc,rxAct,ryAct,color,1);//act,1
	     while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
	     xAnt=xAct;
	     yAnt=yAct;
	     rxAnt=abs(xc-xAnt);
	     ryAnt=abs(yc-yAnt);
	  }
       }
    }
 }
 modo(0x3);
}