//Graficas por computadora
//Practica 01
#include<stdio.h>
#include<conio.h>
#include<dos.h>
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
void dibuja(/*int m*/){
   int col=0,cont=0;
   for(int i=25;i<=150;i++)
      for(int j=25;j<=150;j++){
	 cont++;
	 if((i!=j)&&(i!=j-1)&&(i!=j+1))
	    pixel(j,i,col);
	 if(cont==5){//10
	    col++;
	    cont=0;
	 }
      }
   //gotoxy(2,155);
   //printf("\n\tPresiona cualquier tecla");
   getch();//delay(3000);
}
/*****************************-M-A-I-N-******************************/
void main(){
 int mod;
 char op;
 do{
    clrscr();
    printf("\n\tModos de Video\n\t");
    printf("\n\t     MODO  COLORES   RESOLUCION");
    printf("\n\t 1.   0x4       4      320x200");
    printf("\n\t 2.   0x5       4      320x200");
    printf("\n\t 3.   0x6       2      640x200");
    printf("\n\t 4.  0x12      16      640x480");
    printf("\n\t 5.  0x13     256      320x200");
    printf("\n\t 6.  0x5c     256      640x480");
    printf("\n\t 7.  0x5d     256      800x600");
    printf("\n\t 8.  0x5e     256     1024x768");
    printf("\n\t 9. 0x103     256      800x600");
    printf("\n\t10. 0x105   65536      640x480");
    printf("\n\t11. 0x106   65536      800x600");
    printf("\n\t12. 0x107   65536     1024x768");
    printf("\n\n\tEscribe el modo de video a usar (ej. 0x12):\n\t");
    scanf("%x",&mod);
    fflush(stdin);
    modo(mod);
    dibuja(/*mod*/);
    modo(0x3);
    printf("\n\n\t�Hacer otra prueba? (s/n)\n\t");
    op=getch();
 }while(op!='n');
}
