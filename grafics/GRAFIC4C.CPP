//Carlos Francisco Camacho Uribe
//Taller de Graficas por Computadora
//Practica 4
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>
void main(){
 int Cx,Dx,Cy,Dy,color,x,y,k;
 int yTx,coords[2][100],i,xTmp,yTmp;
 float r,pk;
 int gdriver,gmode,errorcode;
 char op,*tempstr;
 do{
   gdriver=9;gmode=2;
   clrscr();
   printf("\n\tNOTA: El rango es de x=320 a 640 y=0 a 240, a 16 colores\n\t");
   printf("Radio maximo = 35\n\t");
   printf("\n\tEscribe la coordenada Cx: ");
   scanf("%d",&Cx);
   printf("\n\tEscribe la coordenada Cy: ");
   scanf("%d",&Cy);
   printf("\n\tEscribe la coordenada Dx: ");
   scanf("%d",&Dx);
   printf("\n\tEscribe la coordenada Dy: ");
   scanf("%d",&Dy);
   printf("\n\tEscribe el color: ");
   scanf("%d",&color);
   initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
   errorcode=graphresult();
   if(errorcode!=grOk){
      printf("\n\tError grafico: %s\n", grapherrormsg(errorcode));
   }else{
      cleardevice();
      setcolor(7);
      r=sqrt(pow((Dx-Cx),2)+pow((Dy-Cy),2));
      outtextxy(320,300,"Carlos Francisco Camacho Uribe");
      outtextxy(320,310,"Taller de Graficas por Computadora");
      outtextxy(320,320,"Practica 4: Circulo por punto medio");
      outtextxy(10,20,"C = (");
      outtextxy(49,20,itoa(Cx,tempstr,10));
      outtextxy(72,20,",");outtextxy(80,20,itoa(Cy,tempstr,10));
      outtextxy(104,20,")");
      outtextxy(10,30,"D = (");
      outtextxy(49,30,itoa(Dx,tempstr,10));
      outtextxy(72,30,",");outtextxy(80,30,itoa(Dy,tempstr,10));
      outtextxy(104,30,")");
      outtextxy(10,40,"r = ");outtextxy(44,40,itoa(r,tempstr,10));
      pk=(5/4)-r;
      y=r;
      x=0;
      k=0;
      outtextxy(10,190,"K   Pk+1   Xk+1   Yk+1");
      outtextxy(10,210,itoa(k,tempstr,10));
      outtextxy(50,210,itoa(pk,tempstr,10));
      outtextxy(100,210,itoa(x,tempstr,10));
      outtextxy(157,210,itoa(y,tempstr,10));
      yTx=210;
      putpixel(x+Cx,y+Cy,color);
      coords[0][0]=x;
      coords[1][0]=y;
      do{
	 if(pk<0){
	    x++;
	    pk=pk+(2*x)+1;
	 }else{
	    x++;y--;
	    pk=pk+(2*x)+1-(2*y);
	 }
	 k++;
	 coords[0][k]=x;
	 coords[1][k]=y;
	 yTx+=10;
	 outtextxy(10,yTx,itoa(k,tempstr,10));
	 outtextxy(50,yTx,itoa(pk,tempstr,10));
	 outtextxy(100,yTx,itoa(x,tempstr,10));
	 outtextxy(157,yTx,itoa(y,tempstr,10));
	 putpixel(x+Cx,y+Cy,color);
      }while(x<y);
      //Termino el calculo del primer octante
      for(i=0;i<k+1;i++){
	 coords[0][k+1+i]=coords[1][i];
	 coords[1][k+1+i]=coords[0][i];
      }
      coords[0][k+i+1]=-1;
      for(i=k+1;coords[0][i]!=-1;i++)
	 putpixel(coords[0][i]+Cx,coords[1][i]+Cy,color);
      for(i=0;coords[0][i]!=-1;i++){
	 xTmp=coords[0][i]-(coords[0][i]*2);
	 yTmp=coords[1][i]-(coords[1][i]*2);
	 putpixel(xTmp+Cx,yTmp+Cy,color);
      }
      for(i=0;coords[0][i]!=-1;i++){
	 xTmp=coords[0][i]-(coords[0][i]*2);
	 putpixel(xTmp+Cx,coords[1][i]+Cy,color);
      }
      for(i=0;coords[0][i]!=-1;i++){
	 yTmp=coords[1][i]-(coords[1][i]*2);
	 putpixel(coords[0][i]+Cx,yTmp+Cy,color);
      }
      getch();
      closegraph();
    }
   printf("\n\t�Dibujar otro circulo? (s/n): ");
   op=getch();
   fflush(stdin);
 }while(op!='n');
}