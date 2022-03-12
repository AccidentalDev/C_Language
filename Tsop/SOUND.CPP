#include <dos.h>
#include <stdio.h>
#include <conio.h>
void main(){
   int freq;
   char op;
   do{
     clrscr();
     printf("\n\t¨De que frecuencia el sonido? (de 30 a 1000)\n\t");
     scanf("%d",&freq);
     fflush(stdin);
     printf("\n\n\tReproduciendo un sonido de %d Hz",freq);
     sound(freq);//500
     delay(300);//1000
     nosound();
     printf("\n\n\tSonido finalizado");
     printf("\n\n\t¨Escuchar otro sonido? (s/n)\n\t");
     op=getch();
   }while(op!='n');
}