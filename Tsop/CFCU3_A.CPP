//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 03: Descriptor de Procesos (BCP)
#include<stdio.h>
#include<conio.h>
#include<dos.h>

#define Listo 1
#define Ejecucion 2

typedef struct{
   int id;
   char /*nombre[10];*/*nombre;
   int estado;
   void (*direccion)();
}BCP;

void proceso1(){
   clrscr();
   gotoxy(26,10);printf("Este es el proceso 1");
   delay(2000);
}
void proceso2(){
   clrscr();
   gotoxy(20,6);printf("Este es el proceso 2");
   delay(2000);
}
void proceso3(){
   clrscr();
   gotoxy(28,18);printf("Este es el proceso 3");
   delay(2000);
}
void proceso4(){
   clrscr();
   gotoxy(3,15);printf("Este es el proceso 4");
   delay(2000);
}
void proceso5(){
   clrscr();
   gotoxy(31,9);printf("Este es el proceso 5");
   delay(2000);
}
void proceso6(){
   clrscr();
   gotoxy(26,10);printf("Este es el proceso 6");
   delay(2000);
}
void proceso7(){
   clrscr();
   gotoxy(17,20);printf("Este es el proceso 7");
   delay(2000);
}
void proceso8(){
   clrscr();
   gotoxy(35,14);printf("Este es el proceso 8");
   delay(2000);
}
void proceso9(){
   clrscr();
   gotoxy(20,5);printf("Este es el proceso 9");
   delay(2000);
}
void proceso10(){
   clrscr();
   gotoxy(28,18);printf("Este es el proceso 10");
   delay(2000);
}

void iteraciones(int &count,BCP Lista[10]){
   BCP *BCPprocEjec;
   for(int i=0;i<17;i++){
      BCPprocEjec=&Lista[count];
      BCPprocEjec->estado=2;
      (BCPprocEjec->direccion)();
      BCPprocEjec->estado=1;
      if(count==9)
	   count=0;
	else
	   count++;
   }
}
void muestraBCP(BCP l[10]){
   char *estados[2];
   estados[0]="Listo";
   estados[1]="Ejecutando";
   clrscr();
   printf("\n\tContenido del Descriptor de Procesos\n");
   printf("\n\t");
   printf("Nombre       ID      Estado      Direccion\n\t");
   for(int i=0;i<10;i++)
      printf("%s     %d      %s       %d\n\t",l[i].nombre,l[i].id,estados[l[i].estado-1],l[i].direccion);
}
//----------------------------------MAIN-----------------------------------
void main(){
   BCP list[10];
   int cont=0,op;
   //-----Inicializacion del BCP-----
   list[0].direccion=&proceso1;
   list[1].direccion=&proceso2;
   list[2].direccion=&proceso3;
   list[3].direccion=&proceso4;
   list[4].direccion=&proceso5;
   list[5].direccion=&proceso6;
   list[6].direccion=&proceso7;
   list[7].direccion=&proceso8;
   list[8].direccion=&proceso9;
   list[9].direccion=&proceso10;
   for(int j=0;j<10;j++){
      list[j].estado=1;
      list[j].id=j+1;
   }
   list[0].nombre="Proceso 1";
   list[1].nombre="Proceso 2";
   list[2].nombre="Proceso 3";
   list[3].nombre="Proceso 4";
   list[4].nombre="Proceso 5";
   list[5].nombre="Proceso 6";
   list[6].nombre="Proceso 7";
   list[7].nombre="Proceso 8";
   list[8].nombre="Proceso 9";
   list[9].nombre="Proceso 10";
   //-----Fin de la inicializacion-----
   iteraciones(cont,list);
   do{
     clrscr();
     printf("\n\tMENU:\n\t");
     printf("\n\t1-Otras 17 iteraciones");
     printf("\n\t2-Mostrar el contenido del descriptor de procesos");
     printf("\n\t3-Salir");
     printf("\n\n\tOpcion: ");
     scanf("%d",&op);
   if(op==1)
      iteraciones(cont,list);
   else
      if(op==2){
	 muestraBCP(list);
	 getch();
      }
   }while(op!=3);
}