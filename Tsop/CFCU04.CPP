//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 04: Cambio de Contexto (Despachador multitarea)

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<setjmp.h>

#define Inicial 0
#define Listo 1
#define Ejecucion 2
#define delVar 500

jmp_buf DirSO;
char *dir_inicio_pila;

typedef struct{
   int id;
   char *nombre;
   int estado;
   void (*direccion)();
   //------------------------
   int prioridad_estatica;
   int prioridad_dinamica;//Maximo 30
   //Los dos anteriores se deben inicializar con el mismo valor
   jmp_buf RegistrosCPU;
   char Pila[4000];
   size_t tam_pila;
}BCP;

void ceder_control(BCP aptBCPejec){
   char fin;
   if(&fin>dir_inicio_pila){
      aptBCPejec->tam_pila=&fin-dir_inicio_pila+1;
      memcpy(aptBCPejec->Pila,dir_inicio_pila,aptBCPejec->tam_pila);
   }else{
      aptBCPejec->tam_pila=dir_inicio_pila-&fin+1;
      memcpy(aptBCPejec->Pila,&fin,aptBCPejec->tam_pila);
    }
   aptBCPejec->estado=Listo;
   if(!setjmp(aptBCPejec->RegistrosCPU))
      longjmp(DirSO,1);
}

void restaurar_contexto(BCP aptBCPejec){
   char colchon[4000];
   if(colchon>dir_inicio_pila)
      memcpy(dir_inicio_pila,aptBCPejec->Pila,aptBCPejec->tam_pila);
   else
      memcpy(dir_inicio_pila-aptBCPejec->tam_pila+1,aptBCPejec->Pila,aptBCPejec->tam_pila);
   //Estado en ejecucion:
   aptBCPejec->estado=Ejecucion;

   longjmp(aptBCPejec->RegistrosCPU,1);
}
//----------------Definicion de los procesos---------------
void proceso1(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,2);printf("Este es el proceso 1 y lleva %d vueltas",x++);
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso2(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,4);printf("Este es el proceso 2");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso3(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,6);printf("Este es el proceso 3");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso4(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,8);printf("Este es el proceso 4");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso5(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,10);printf("Este es el proceso 5");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso6(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,12);printf("Este es el proceso 6");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso7(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,14);printf("Este es el proceso 7");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso8(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,16);printf("Este es el proceso 8");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso9(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,18);printf("Este es el proceso 9");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
void proceso10(){
   int x=1,cont=0;
   while(1){
	 clrscr();
	 gotoxy(26,20);printf("Este es el proceso 10");
	 delay(delVar);
	 if(cont==3){
	    ceder_control();
	    cont=0;
	 }
	 cont++;
   }
}
//------------Fin definicion de los procesos------------

void burbuja(BCP L[10]){
   int b,i;
   BCP *Temp;
   do{
     b=0;
     for(i=0;i<9;i++)
	if(L[i].prioridad_dinamica>L[i+1].prioridad_dinamica){
	   Temp=&L[i];
	   *L[i]=&L[i+1];
	   *L[i+1]=Temp;
	   b=1;
	}
   }while(b==1);
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
/*
void muestraBCP(BCP l[10]){
   char *estados[2];
   estados[0]="Listo";
   estados[1]="Ejecutando";
   clrscr();
   printf("\n\tContenido del Descriptor de Procesos\n");
   printf("\n\n\t");
   printf("NOMBRE\t\tID\tESTADO\tDIRECCION\n\n\t");
   for(int i=0;i<10;i++)
	 printf("%s\t%d\t%s\t%d\n\t",l[i].nombre,l[i].id,estados[l[i].estado-1],l[i].direccion);
}
*/
//----------------------------------MAIN-----------------------------------
void main(){
   char x;
   dir_inicio_pila=&x;
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
	 list[j].prioridad_estatica=list[j].prioridad_dinamica=j+2;
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
   setjmp(DirSO);
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