//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 01

#include<stdio.h>
#include<conio.h>
#include<dos.h>

void ventanas(){
   int i,j;
   clrscr();
   textcolor(4);
   //----------Limites del menu-----------
   for(i=1;i<80;i++)
      cprintf("Ä");
   gotoxy(1,3);
   for(j=1;j<80;j++)
      cprintf("Ä");
   //-----Limites de los comentarios------
   gotoxy(1,23);
   for(i=1;i<80;i++)
      cprintf("Ä");
   gotoxy(1,25);
   for(j=1;j<80;j++)
      cprintf("Ä");
   //---Limites de la ventana de texto----
   textcolor(2);
   gotoxy(10,7);
   for(i=1;i<30;i++)
      cprintf("Ä");
   gotoxy(10,17);
   for(j=1;j<30;j++)
      cprintf("Ä");
   for(i=8;i<17;i++){
      gotoxy(9,i);
      cprintf("³");
      gotoxy(39,i);
      cprintf("³");
   }
   gotoxy(9,7);cprintf("Ú");
   gotoxy(39,7);cprintf("¿");
   gotoxy(9,17);cprintf("À");
   gotoxy(39,17);cprintf("Ù");
}

void menu(int st){
   if(st==1){
      textcolor(7);
      textbackground(1);
      gotoxy(4,2);
      cprintf(" Limpiar ");
      gotoxy(16,2);
      textbackground(8);
      cprintf(" Continuar ");
      gotoxy(29,2);
      cprintf(" Salir ");
   }else
      if(st==2){
	 textcolor(7);
	 gotoxy(4,2);
	 cprintf(" Limpiar ");
	 gotoxy(16,2);
	 textbackground(1);
	 cprintf(" Continuar ");
	 gotoxy(29,2);
	 textbackground(8);
	 cprintf(" Salir ");
      }else
	 if(st==3){
	    textcolor(7);
	    gotoxy(4,2);
	    cprintf(" Limpiar ");
	    gotoxy(16,2);
	    cprintf(" Continuar ");
	    gotoxy(29,2);
	    textbackground(1);
	    cprintf(" Salir ");
	    textbackground(8);
	 }if(st==4){
	     sound(500);
	     delay(1000);
	     nosound();
	  }else{
	    textcolor(7);
	    gotoxy(5,2);
	    cprintf("Limpiar");
	    gotoxy(16,2);
	    cprintf("Continuar");
	    gotoxy(29,2);
	    cprintf("Salir");
	  }
}

void descripcion(int menu){
   gotoxy(2,24);
   switch(menu){
	 case 1:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("a,d = Mover ³ Limpia el contenido de la ventana");
		 }break;
	 case 2:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("a,d = Mover ³ Continua escribiendo en ventana");
		 }break;
	 case 3:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("a,d = Mover ³ Sale del programa");
		 }break;
	 default:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("Ctrl+M=Menu ³ Programa hecho por Carlos Fco. Camacho Uribe");
		 }
   }
}

void main(){
 //---[estado][entrada]
 int salida[3][3]={{4,2},{1,3},{2,4}};
 int edo_sig[3][3]={{1,2},{1,3},{2,3}};
 int estado=5,sal2=4,entrada,x,y;
 char letra,mov;
 ventanas();
 menu(sal2);
 descripcion(sal2);
 window(10,8,38,16);
 //(left,top,right,bottom)
 do{
   do{
     letra=getch();
     cprintf("%c",letra);
   }while(!kbhit()&&letra!=13);
   sal2=1;
   estado=0;
   x=wherex();
   y=wherey();
   do{
     menu(sal2);
     descripcion(sal2);
     mov=getch();
     if(mov=='d'){
	entrada=0;
	sal2=salida[estado-1][entrada-1];
	estado=edo_sig[estado-1][entrada-1];
	menu(sal2);
     }
     //Continuan las condicionales para 'a' y <Enter>
   }while(!kbhit()&&mov!=13);
   sal2=4;
   menu(sal2);
   descripcion(sal2);
   gotoxy(x,y);
 }while(estado!=3);
 getch();
}