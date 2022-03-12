#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void main(){
   int tecla;
   char op;
   do{
     clrscr();
     _setcursortype(_NOCURSOR);
     do{
       gotoxy(1,6);
       printf("\tPresione una tecla\n");
     }while(!kbhit());
     tecla=getch();
     if(tecla==0)
	tecla=getch();
     _setcursortype(_NORMALCURSOR);
     printf("\n\tEl codigo de la tecla presionada es: %d", tecla);
     printf("\n\n\t¨Revisar otra tecla? (s/n)\n\t");
     op=getch();
   }while(op!='n');
   printf("\n\tPresione cualquier tecla para salir del programa");
   getch();
}