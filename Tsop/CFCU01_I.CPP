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
   switch(st){
	case 1:{textcolor(7);
		textbackground(1);
		gotoxy(4,2);
		cprintf(" Limpiar ");
		gotoxy(15,2);
		textbackground(8);
		cprintf(" Continuar ");
		gotoxy(28,2);
		cprintf(" Salir ");
	       }break;
	case 2:{textcolor(7);
		gotoxy(4,2);
		cprintf(" Limpiar ");
		gotoxy(15,2);
		textbackground(1);
		cprintf(" Continuar ");
		gotoxy(28,2);
		textbackground(8);
		cprintf(" Salir ");
	       }break;
	case 3:{textcolor(7);
		gotoxy(4,2);
		cprintf(" Limpiar ");
		gotoxy(15,2);
		cprintf(" Continuar ");
		gotoxy(28,2);
		textbackground(1);
		cprintf(" Salir ");
		textbackground(8);
	       }break;
	case 4:{sound(500);
		delay(300);
		nosound();
	       }break;
	default:{gotoxy(1,2);
		 clreol();
		 textcolor(7);
		 gotoxy(4,2);
		 cprintf(" Limpiar ");
		 gotoxy(15,2);
		 cprintf(" Continuar ");
		 gotoxy(28,2);
		 cprintf(" Salir ");
		}
   }
}

void descripcion(int menu1){
   gotoxy(2,24);
   switch(menu1){
	 case 1:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf(" Limpia el contenido de la ventana");
		 }break;
	 case 2:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf(" Continua escribiendo en ventana");
		 }break;
	 case 3:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf(" Sale del programa");
		 }break;
	 default:{clreol();
		 textcolor(7);
		 textbackground(8);
		 cprintf("Ctrl+M=Menu ³ Programa hecho por Carlos Fco. Camacho Uribe");
		 }
   }
}

//----------------------------MAIN------------------------------------------
void main(){
 //---[estado][entrada]
 int salida[3][3]={{2,4,1},{3,1,2},{4,2,3}};
 int edo_sig[3][3]={{2,1,1},{3,1,1},{3,2,1}};
 int estado=5,sal2=5,entrada,x,y;
 char letra,mov;
 ventanas();
 menu(sal2);
 descripcion(sal2);
 do{
   window(10,8,38,16);
   //(left,top,right,bottom)
   if(estado==2)
      gotoxy(x,y);
   else{
      if(estado==1){
	 gotoxy(1,1);
	 clrscr();
      }
   }
   do{
     letra=getch();
     cprintf("%c",letra);
   }while(!kbhit()&&letra!=13);
   x=wherex();
   y=wherey();
   sal2=1;
   estado=1;
   window(1,1,80,25);
   do{
     menu(sal2);
     descripcion(sal2);
     mov=getch();
     if(mov==0)
	mov=getch();
     if(mov==77){
	entrada=1;
	sal2=salida[estado-1][entrada-1];
	estado=edo_sig[estado-1][entrada-1];
     }else{
	if(mov==75){
	   entrada=2;
	   sal2=salida[estado-1][entrada-1];
	   estado=edo_sig[estado-1][entrada-1];
	}else
	   if(mov==13)
	      sal2=5;
      }
   }while(!kbhit()&&mov!=13);
   menu(sal2);
   descripcion(sal2);
 }while(estado!=3);
}
/*Conclusiones:
El implementar este programa me ha dado la oportunidad
de aplicar varios de mis conocimientos que he adquirido
a lo largo de mi carrera, como la maquina de estado
finito, ademas he logrado utilizar muchas funciones
de C que no habia usado y que me permiten darle una
mejor presentacion y dinamismo a mis programas.
Ademas he podido darme una peque¤a idea de lo que es
implementar un editor de texto, el cual es un trabajo
ciertamente inmenso*/