//Prueba de funciones
#include<conio.h>
#include<stdio.h>
void main(){
   int i,j;
   clrscr();
   textcolor(4);
//-------------------Limites del menu-------------------
   for(i=1;i<80;i++)
      cprintf("�");
   gotoxy(1,3);
   for(j=1;j<80;j++)
      cprintf("�");
//--------------Limites de los comentarios--------------
   gotoxy(1,23);
   for(i=1;i<80;i++)
      cprintf("�");
   gotoxy(1,25);
   for(j=1;j<80;j++)
      cprintf("�");
//-------------Limites de la ventana de texto-----------
   textcolor(2);
   gotoxy(10,7);
   for(i=1;i<30;i++)
      cprintf("�");
   gotoxy(10,17);
   for(j=1;j<30;j++)
      cprintf("�");
   for(i=8;i<17;i++){
      gotoxy(9,i);
      cprintf("�");
      gotoxy(39,i);
      cprintf("�");
   }
   gotoxy(9,7);cprintf("�");
   gotoxy(39,7);cprintf("�");
   gotoxy(9,17);cprintf("�");
   gotoxy(39,17);cprintf("�");
   getch();
}//Alt+179=�  �=170   �=191  �=192  �=217  �=218