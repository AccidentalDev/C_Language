//Prueba de modos de video
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
void dibuja(int m){
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
   printf("\n\tModo %X Hx",m);
   delay(3000);
}
/*****************************-M-A-I-N-******************************/
void main(){
 int mod;
 for(mod=0x28;mod<=0x40;mod++){
    modo(mod);
    dibuja(mod);
    clrscr();
 }
}