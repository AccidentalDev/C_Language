#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<MATH.H>
#include<F:\CFCU\interupt.h>

unsigned char cLinea[5000];
int colorG=6,sel=0;

void lineaBly(int px1,int py1,int px2,int py2,int col){
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
//************************ Revisar ****************************
void lineaB(int px1,int px2,int py1,int py2,int col,int b){
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
	//Finaliza seccion de bandera
	c++;
      }while(c<Ay);
   }
   cursor(0x1);
}
void layout(){
   int i,j,color=0;
   //Area de trabajo
   lineaBly(56,20,56,424,15);
   lineaBly(639,20,639,424,15);
   lineaBly(56,424,639,424,15);
   lineaBly(56,20,639,20,15);
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
      lineaBly(i,37,i,77,15);
   lineaBly(28,57,28,77,15);
   for(i=8;i<50;i+=20)
      lineaBly(i,91,i,171,15);
   //lineas horizontales de la barra de herramientas
   for(i=37;i<80;i+=20)
      lineaBly(8,i,48,i,15);
   for(i=91;i<175;i+=20)
      lineaBly(8,i,48,i,15);
   //lineas horizontales de la barra de colores
   for(i=432;i<475;i+=20)
      lineaBly(73,i,233,i,15);
   //lineas verticales de la barra de colores
   for(i=73;i<235;i+=20)
      lineaBly(i,432,i,472,15);
   //*******Letras de exit*******
   //letra E
   for(i=42;i<53;i+=10)
      lineaBly(12,i,17,i,4);
   lineaBly(12,47,15,47,4);
   lineaBly(12,42,12,52,4);
   //letra X
   lineaBly(20,42,26,52,4);
   lineaBly(20,52,26,42,4);
   //letra I
   for(i=42;i<53;i+=10)
      lineaBly(30,i,34,i,4);
   lineaBly(32,42,32,52,4);
   //letra T
   lineaBly(38,42,44,42,4);
   lineaBly(41,42,41,52,4);
}
void clicBoton(int px,int py){
   if((px>8&&py>37)&&(px<47&&py<57)){
      gotoxy(1,1);
      printf("Se presiono el boton EXIT...");
      delay(800);
      sel=-1;
   }
   //Seleccion de colores fila superior
   if((px>73&&py>432)&&(px<93&&py<452)){
      colorG=0;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>93&&py>432)&&(px<113&&py<452)){
      colorG=2;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>113&&py>432)&&(px<133&&py<452)){
      colorG=4;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>133&&py>432)&&(px<153&&py<452)){
      colorG=6;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>153&&py>432)&&(px<173&&py<452)){
      colorG=8;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>173&&py>432)&&(px<193&&py<452)){
      colorG=10;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>193&&py>432)&&(px<213&&py<452)){
      colorG=12;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>213&&py>432)&&(px<233&&py<452)){
      colorG=14;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   //Seleccion de colores fila inferior
   if((px>73&&py>452)&&(px<93&&py<472)){
      colorG=1;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>93&&py>452)&&(px<113&&py<472)){
      colorG=3;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>113&&py>452)&&(px<133&&py<472)){
      colorG=5;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>133&&py>452)&&(px<153&&py<472)){
      colorG=7;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>153&&py>452)&&(px<173&&py<472)){
      colorG=9;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>173&&py>452)&&(px<193&&py<472)){
      colorG=11;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>193&&py>452)&&(px<213&&py<472)){
      colorG=13;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
   if((px>213&&py>452)&&(px<233&&py<472)){
      colorG=15;
      gotoxy(1,1);
      printf("Se selecciono un color...");
   }
}
void malibres(){
   int xAct,yAct,color=2;
   int xAnt,yAnt;
   xAct=x;
   yAct=y;
   xAnt=x;
   yAnt=y;
   while(lee_cursor(&x,&y,0x12)==1){
      xAct=x;
      yAct=y;
      lineaB(xAnt,xAct,yAnt,yAct,color,1);
      while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
      xAnt=xAct;
      yAnt=yAct;
   }
}
/******************************-M-A-I-N-******************************/
void main(){
 int xx,yy;
 clrscr();
 modo(0x4);
 modo(0x12);
 cursor(0);
 cursor(1);
 layout();
 do{
    if(lee_cursor(&x,&y,0x12)==1){
       xx=x;yy=y;
       if((xx>56&&yy>20)&&(xx<640&&yy<424)){
	  gotoxy(1,1);
	  printf("Entrando en modo pintar...   ");
	  cursor(2);
	  malibres();
	  cursor(1);
       }else{
	  gotoxy(1,1);
	  printf("Entrando en modo botones...  ");
	  delay(150);
	  clicBoton(xx,yy);
	  gotoxy(1,1);
	  printf("Valor de sel: %d              ",sel);
	  delay(600);
       }
    }
 }while(sel!=-1||!kbhit());
 getch();
 modo(0x3);
}