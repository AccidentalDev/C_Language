#include<stdio.h>
#include<conio.h>
#include<graphics.h>
void main(){
 int x1,x2,y1,y2,color;
 int gdriver,gmode,errorcode;
 char op,mov;
 do{
   gdriver=9;gmode=2;
   clrscr();
   printf("\n\tNOTA: El modo de video es de 640x480 a 16 colores\n\t");
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
      do{
	setcolor(color);
	line(x1,y1,x2,y2);
	mov=getch();
	if(mov==75){
	   x1-=5;
	   x2-=5;
	   if((x1<=0)||(x2<=0)){
	      x1+=5;
	      x2+=5;
	   }
	}else
	   if(mov==77){
	      x1+=5;
	      x2+=5;
	      if((x1>=640)||(x2>=640)){
		 x1-=5;
		 x2-=5;
	      }
	   }else
	      if(mov==72){
		 y1-=5;
		 y2-=5;
		 if((y1<=0)||(y2<=0)){
		    y1+=5;
		    y2+=5;
		 }
	      }else
		 if(mov==80){
		    y1+=5;
		    y2+=5;
		    if((y1>=480)||(y2>=480)){
		       y1-=5;
		       y2-=5;
		    }
		 }else
		    if(mov=='c')
		       color++;
	cleardevice();
      }while(mov!='n');
      closegraph();
    }
   printf("\n\t?Dibujar otra linea? (s/n): ");
   scanf("%s",&op);
   fflush(stdin);
 }while(op!='n');
 /*printf("\n\tPresiona cualquier tecla para salir");
 getch();*/
}