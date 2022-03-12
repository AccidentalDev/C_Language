//Graficas por computadora
//Practica 06: Circulo por punto medio con mouse
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<MATH.H>
unsigned char cLinea[500][8];
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
      cLinea[cont][4]=lee_pixel(xc+y,yc+x);
      cLinea[cont][5]=lee_pixel(xc-y,yc+x);
      cLinea[cont][6]=lee_pixel(xc+y,yc-x);
      cLinea[cont][7]=lee_pixel(xc-y,yc-x);
   }
   if(ban==1){
      pixel(xc+x,yc+y,c);
      pixel(xc-x,yc+y,c);
      pixel(xc+x,yc-y,c);
      pixel(xc-x,yc-y,c);
      pixel(xc+y,yc+x,c);
      pixel(xc-y,yc+x,c);
      pixel(xc+y,yc-x,c);
      pixel(xc-y,yc-x,c);
   }
   if(ban==2){
      pixel(xc+x,yc+y,cLinea[cont][0]);
      pixel(xc-x,yc+y,cLinea[cont][1]);
      pixel(xc+x,yc-y,cLinea[cont][2]);
      pixel(xc-x,yc-y,cLinea[cont][3]);
      pixel(xc+y,yc+x,cLinea[cont][4]);
      pixel(xc-y,yc+x,cLinea[cont][5]);
      pixel(xc+y,yc-x,cLinea[cont][6]);
      pixel(xc-y,yc-x,cLinea[cont][7]);
   }
}
void circulo(int xc,int yc,int radio,int color,int b){
   int x,y,p;
   int c=0;
   x=0;
   y=radio;
   cursor(0x2);
   puntos(xc,yc,x,y,color,c,b);
   c++;
   p=1-radio;
   while(x<y){
      if(p<0){
	 x++;
	 p+=2*x+1;
      }else{
	 x++;y--;
	 p+=2*(x-y)-1;
      }
      puntos(xc,yc,x,y,color,c,b);
      c++;
   }
   cursor(0x1);
}
/******************************-M-A-I-N-******************************/
void main(){
 int xc,yc,rAnt,rAct,color=2;
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
       rAnt=sqrt(pow((xAnt-xc),2)+pow((yAnt-yc),2));
       circulo(xc,yc,rAnt,color,0);
       while(lee_cursor(&x,&y,0x12)==1){
	  xAct=x;
	  yAct=y;
	  rAct=sqrt(pow((xAct-xc),2)+pow((yAct-yc),2));
	  circulo(xc,yc,rAnt,color,2);//ant
	  circulo(xc,yc,rAct,color,0);//act
	  circulo(xc,yc,rAct,color,1);//act
	  while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
	  xAnt=xAct;
	  yAnt=yAct;
	  rAnt=sqrt(pow((xAnt-xc),2)+pow((yAnt-yc),2));
       }
    }
 }
 modo(0x3);
}