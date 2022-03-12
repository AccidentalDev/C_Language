//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 04: Cambio de Contexto (Despachador multitarea)

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<setjmp.h>
#include<mem.h>
#include<string.h>

#define Inicial 0
#define Listo 1
#define Ejecucion 2
#define delVar 500

jmp_buf DirSO;
char *dir_inicio_pila;
int op,i,c,tmp;

typedef struct{
   int id;
   char nombre[14];
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

BCP *aptBCPejec;
BCP Lista[10];

void ceder_control(){
   char fin;
   if(&fin>dir_inicio_pila){
      aptBCPejec->tam_pila=&fin-dir_inicio_pila+1;
      memcpy(aptBCPejec->Pila,dir_inicio_pila,aptBCPejec->tam_pila);
   }else{
      aptBCPejec->tam_pila=dir_inicio_pila-&fin+1;
      memcpy(aptBCPejec->Pila,&fin,aptBCPejec->tam_pila);
    }
   aptBCPejec->estado=Listo;
   if(!setjmp(aptBCPejec->RegistrosCPU)){
      longjmp(DirSO,1);
   }
}

void restaurar_contexto(){
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
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 1 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso2(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 2 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso3(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 3 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso4(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 4 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso5(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 5 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso6(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 6 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso7(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 7 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso8(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 8 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso9(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 9 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
void proceso10(){
   int x=1;
   while(1){
      clrscr();
      gotoxy(26,20);printf("Este es el proceso 10 y lleva %d vueltas",x++);
      sound(200);
      delay(50);
      nosound();
      delay(delVar);
      ceder_control();
   }
}
//------------Fin definicion de los procesos------------

/*void iteraciones(){
   for(i=0;i<17;i++){
      //Elegir siguiente proceso
      aptBCPejec=&Lista[0];
      for(int c=0;c<10;c++)
	 if(aptBCPejec->prioridad_estatica<Lista[c].prioridad_estatica)
	    aptBCPejec=&Lista[c];
      //Envejecer procesos
      for(int j=0;j<10;j++)
	 Lista[j].prioridad_dinamica++;
      //Reestablecer prioridad dinamica
      Lista[0].prioridad_dinamica=Lista[0].prioridad_estatica;

      if(aptBCPejec->estado==Inicial){
	 aptBCPejec->estado=Ejecucion;
	 (aptBCPejec->direccion)();
	 aptBCPejec->estado=Listo;
      }else
	 if(aptBCPejec->estado==Listo)
	    restaurar_contexto();
   }
}*/

void muestraBCP(){
   char estados[2][14];
   strcpy(estados[0],"Listo");
   strcpy(estados[1],"Ejecutando");
   clrscr();
   printf("\n\tContenido del Descriptor de Procesos\n");
   printf("\n\n");
   printf("NOMBRE\t\tID\tESTADO\t  DIRECCION Tama¤oPila  P.ESTATICA  P.DINAMICA\n\n");
   for(int i=0;i<10;i++){
      printf("%s\t%d\t%s",Lista[i].nombre,Lista[i].id,estados[Lista[i].estado]);
      gotoxy(38,i+6);
      printf("%d",Lista[i].direccion);
      gotoxy(48,i+6);printf("%d",Lista[i].tam_pila);
      gotoxy(62,i+6);printf("%d",Lista[i].prioridad_estatica);
      gotoxy(72,i+6);printf("%d\n",Lista[i].prioridad_dinamica);
   }
   getch();
}

void modifPrior(){
   clrscr();
   for(int i=0;i<10;i++){
      printf("\nIntroduce la nueva prioridad del proceso %d: ",i+1);
      scanf("%d",&Lista[i].prioridad_estatica);
      Lista[i].prioridad_dinamica=Lista[i].prioridad_estatica;
   }
}
//----------------------------------MAIN-----------------------------------


void main(){
   char x;
   dir_inicio_pila=&x;

   //-----Inicializacion del BCP-----
   Lista[0].direccion=&proceso1;
   Lista[1].direccion=&proceso2;
   Lista[2].direccion=&proceso3;
   Lista[3].direccion=&proceso4;
   Lista[4].direccion=&proceso5;
   Lista[5].direccion=&proceso6;
   Lista[6].direccion=&proceso7;
   Lista[7].direccion=&proceso8;
   Lista[8].direccion=&proceso9;
   Lista[9].direccion=&proceso10;
   for(int j=0;j<10;j++){
      Lista[j].estado=0;
      Lista[j].id=j+1;
      Lista[j].prioridad_estatica=Lista[j].prioridad_dinamica=j+1;
   }
   strcpy(Lista[0].nombre,"Proceso 1");
   strcpy(Lista[1].nombre,"Proceso 2");
   strcpy(Lista[2].nombre,"Proceso 3");
   strcpy(Lista[3].nombre,"Proceso 4");
   strcpy(Lista[4].nombre,"Proceso 5");
   strcpy(Lista[5].nombre,"Proceso 6");
   strcpy(Lista[6].nombre,"Proceso 7");
   strcpy(Lista[7].nombre,"Proceso 8");
   strcpy(Lista[8].nombre,"Proceso 9");
   strcpy(Lista[9].nombre,"Proceso 10");
   //-----Fin de la inicializacion-----
   i=0;
   setjmp(DirSO);

   //--------------Inicio de iteraciones--------------
   for(;i++<17;){
      //Elegir siguiente proceso
      aptBCPejec=&Lista[0];
      for(c=0;c<10;c++)
	 if(aptBCPejec->prioridad_dinamica<Lista[c].prioridad_dinamica){
	    tmp=c;
	    aptBCPejec=&Lista[tmp];
	 }
      //Envejecer procesos
      for(c=0;c<10;c++)
	 Lista[c].prioridad_dinamica++;
      //Reestablecer prioridad dinamica
      Lista[tmp].prioridad_dinamica=Lista[tmp].prioridad_estatica;

      if(aptBCPejec->estado==Inicial){
	 aptBCPejec->estado=Ejecucion;
	 (aptBCPejec->direccion)();
	 aptBCPejec->estado=Listo;
      }else
	 if(aptBCPejec->estado==Listo)
	    restaurar_contexto();
   }
   //---------------Fin de iteraciones----------------
   do{
     clrscr();
     printf("\n\tMENU:\n\t");
     printf("\n\t1-Otras 17 iteraciones");
     printf("\n\t2-Mostrar el contenido del descriptor de procesos");
     printf("\n\t3-Modificar prioridades");
     printf("\n\t4-Salir");
     printf("\n\n\tOpcion: ");
     scanf("%d",&op);

     switch(op){
	case 1:{//--------------Inicio de iteraciones--------------
		for(i=0;i<17;i++){
		   //Elegir siguiente proceso
		   aptBCPejec=&Lista[0];
		   for(c=0;c<10;c++){
		      if(aptBCPejec->prioridad_dinamica<Lista[c].prioridad_dinamica)
			 aptBCPejec=&Lista[c];
		   }
		   //Envejecer procesos
		   for(c=0;c<10;c++)
		      Lista[c].prioridad_dinamica++;
		   //Reestablecer prioridad dinamica
		   Lista[0].prioridad_dinamica=Lista[0].prioridad_estatica;

		   if(aptBCPejec->estado==Inicial){
		      aptBCPejec->estado=Ejecucion;
		      (aptBCPejec->direccion)();
		      aptBCPejec->estado=Listo;
		   }else
		      if(aptBCPejec->estado==Listo)
			 restaurar_contexto();
		}
		//---------------Fin de iteraciones----------------
	       }break;
	case 2:muestraBCP();
	       break;
	case 3:modifPrior();
	       break;
	case 4:printf("\n\n\tFin del Programa");
	       break;
	default:printf("\n\tDebes seleccionar un numero de entre el 1 y el 4");
     }
   }while(op!=4);
   delay(1000);
}
//Manual C++: http://www.usc.es/~genp/doc/cursos/C++/indice.html
//Ctrl+F8 = Activar breakpoint en la linea seleccionada
//(usarlo con setjmp y longjmp)
/*Este programa me mostro que aveces es necesario mantener
la mente clara para asi poder analizar correctamente los
problemas, porque si no, suele ocurrir que omitamos errores
basicos que nos pueden tener buscando otros errores que en
realidad no existen*/