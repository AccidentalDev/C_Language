//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 01

#include<stdio.h>
#include<conio.h>

void ventanas(){
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
}
void descripcion(int menu){
   gotoxy(3,24);
   switch(menu){
	 case 1:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("Limpia el contenido de la ventana");
		 }break;
	 case 2:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("Continua escribiendo en ventana");
		 }break;
	 case 3:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("Sale del programa");
		 }break;
	 default:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("Programa hecho por Carlos Fco. Camacho Uribe");
		 }
   }
}

void main(){
 int sel=0;
 //---[estado][entrada]
 int salida[3][2]={{4,2},{1,3},{2,4}}
 int edo_sig[3][2]={{1,2},{1,3},{2,3}}
 ventanas();
 descripcion(sel);
 getch();
}