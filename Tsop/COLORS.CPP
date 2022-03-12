//Carlos Fco. Camacho Uribe
//Ejemplo de textcolor() y textbackground()
#include <conio.h>
#include <stdio.h>
void main(){
   int i, j;
   clrscr();
   for (i=0; i<9; i++){
       for (j=0; j<50; j++)
	  cprintf("C");
       cprintf("\r\n");
       textcolor(i+1);
       textbackground(i);
       printf(" Letra: %d, Fondo: %d   ",i+1,i);
       getch();
   }
   printf("\n\tFin del programa");
   getch();
}