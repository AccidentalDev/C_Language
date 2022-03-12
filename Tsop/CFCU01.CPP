//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 01

#include<stdio.h>
#include<conio.h>

void ventanas(){
   int i;
   clrscr();
   gotoxy(1,4);
   for(i=1;i<80;i++)
      printf("_");
}
void descripcion(int menu){
   gotoxy(3,24);
   switch(menu){
	 case 1:{clreol();
		 textcolor(9);
		 textbackground(8);
		 printf("Limpia el contenido de la ventana");
		 }break;
	 case 2:{clreol();
		 textcolor(9);
		 textbackground(8);
		 printf("Continua escribiendo en ventana");
		 }break;
	 case 3:{clreol();
		 textcolor(9);
		 textbackground(8);
		 printf("Sale del programa");
		 }break;
	 default:{clreol();
		 textcolor(9);
		 textbackground(8);
		 printf("Programa hecho por Carlos Fco. Camacho Uribe");
		 }
   }
}