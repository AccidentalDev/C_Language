//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 08: Problema de los Filosofos comensales

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<setjmp.h>
#include<mem.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<c:\Tc\Prog\tsop\cola_sop.h>

#define Inicial 0
#define Listo 1
#define Ejecucion 2
#define Bloqueado 3
#define delVar 100


jmp_buf DirSO;
char *dir_inicio_pila;
int op,i,c,e,tmp,ban,semSel,x,y;

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
BCP Lista[5];

void ceder_control(){
   char fin;
   if(&fin>dir_inicio_pila){
      aptBCPejec->tam_pila=&fin-dir_inicio_pila+1;
      memcpy(aptBCPejec->Pila,dir_inicio_pila,aptBCPejec->tam_pila);
   }else{
      aptBCPejec->tam_pila=dir_inicio_pila-&fin+1;
      memcpy(aptBCPejec->Pila,&fin,aptBCPejec->tam_pila);
    }
   if(aptBCPejec->estado!=Bloqueado)
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

void bloquear(){
   aptBCPejec->estado=Bloqueado;
   ceder_control();
}
void desbloquear(int ident){
   Lista[ident-1].estado=Listo;
}
//******************Definicion del semaforo******************
class Semaforo{
   protected:
      int valor;
      Cola cola_id_proc_espera;
   public:
      Semaforo();
      void wait();
      void signal();
      void muestra();
      void inicializa(int);
};
Semaforo::Semaforo(){
   valor=1;
   Inicializa(cola_id_proc_espera);
}
void Semaforo::inicializa(int num){
   valor=num;
}
void Semaforo::wait(){
   if(valor>0)
      valor--;
   else{
      PoneEnCola(aptBCPejec->id,cola_id_proc_espera);
      bloquear();
   }
}
void Semaforo::signal(){
   if(!(Vacia(cola_id_proc_espera))){
      tmp=ValorEnTope(cola_id_proc_espera);
      QuitaDeCola(cola_id_proc_espera);
      desbloquear(tmp);
   }else
      valor++;
}
void Semaforo::muestra(){//Modificar para que muestre cuales estan en cola
   int counter=0;
   clrscr();
   printf("\n\tContenido del Semaforo\n\n\n");
   printf("\tELEMENTOS EN COLA:         VALOR:\n");
   if(Vacia(cola_id_proc_espera))
      printf("\t   Cola Vacia");
   else{
      counter=cola_id_proc_espera.frente-1;
      do{
	counter++;
	if(counter==MAX)
	   counter=0;
	printf("\t      %d\n",cola_id_proc_espera.elems[counter]);
      }while(counter!=cola_id_proc_espera.final);
   }
   gotoxy(38,6);printf("%d",valor);
   getch();
}
//******************fin definicion semaforo******************
Semaforo Mesa;
Semaforo Tenedores[5];

void pensar(int phy){
   int ranVal;
   switch(phy){
	 case 1:{x=13;y=9;
		}break;
	 case 2:{x=16;y=10;
		}break;
	 case 3:{x=15;y=12;
		}break;
	 case 4:{x=11;y=12;
		}break;
	 case 5:{x=10;y=10;
		}break;
   }
   randomize();
   ranVal=random(10);
   for(e=0;e<=ranVal;e++){
      gotoxy(x,y);cprintf("|");delay(delVar);
      gotoxy(x,y);cprintf("/");delay(delVar);
      gotoxy(x,y);cprintf("Ä");delay(delVar);
      gotoxy(x,y);cprintf("\\");delay(delVar);
   }
   gotoxy(x,y);cprintf("");
}
void comer(int phy){
   switch(phy){
	 case 1:{x=13;y=9;
		}break;
	 case 2:{x=16;y=10;
		}break;
	 case 3:{x=15;y=12;
		}break;
	 case 4:{x=11;y=12;
		}break;
	 case 5:{x=10;y=10;
		}break;
   }
   for(e=0;e<=10;e++){
      gotoxy(x,y);cprintf("C");delay(delVar);
      gotoxy(x,y);cprintf("c");delay(delVar);
   }
   gotoxy(x,y);cprintf("");
}
//----------------Definicion de los procesos---------------
void Filosofo1(){
   while(1){
      pensar(1);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[4].wait();ceder_control();
      Tenedores[0].wait();ceder_control();
      comer(1);ceder_control();
      gotoxy(13,9);cprintf("");
      Tenedores[4].signal();ceder_control();
      Tenedores[0].signal();ceder_control();
      Mesa.signal();ceder_control();
   }
}
void Filosofo2(){
   while(1){
      pensar(2);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[0].wait();ceder_control();
      Tenedores[1].wait();ceder_control();
      comer(2);ceder_control();
      gotoxy(16,10);cprintf("");
      Tenedores[0].signal();ceder_control();
      Tenedores[1].signal();ceder_control();
      Mesa.signal();ceder_control();
   }
}
void Filosofo3(){
   while(1){
      pensar(3);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[1].wait();ceder_control();
      Tenedores[2].wait();ceder_control();
      comer(3);ceder_control();
      gotoxy(15,12);cprintf("");
      Tenedores[1].signal();ceder_control();
      Tenedores[2].signal();ceder_control();
      Mesa.signal();ceder_control();
   }
}
void Filosofo4(){
   while(1){
      pensar(4);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[2].wait();ceder_control();
      Tenedores[3].wait();ceder_control();
      comer(4);ceder_control();
      gotoxy(11,12);cprintf("");
      Tenedores[2].signal();ceder_control();
      Tenedores[3].signal();ceder_control();
      Mesa.signal();ceder_control();
   }
}
void Filosofo5(){
   while(1){
      pensar(5);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[3].wait();ceder_control();
      Tenedores[4].wait();ceder_control();
      comer(5);ceder_control();
      gotoxy(10,10);cprintf("");
      Tenedores[3].signal();ceder_control();
      Tenedores[4].signal();ceder_control();
      Mesa.signal();ceder_control();
   }
}
//------------Fin definicion de los procesos------------

void muestraBCP(){
   char estados[3][14];
   strcpy(estados[0],"Listo");
   strcpy(estados[1],"Ejecutando");
   strcpy(estados[2],"Bloqueado");
   clrscr();
   printf("\n\tContenido del Descriptor de Procesos\n");
   printf("\n\n");
   printf("NOMBRE\t\tID\tESTADO  DIRECCION  Tama¤oPila  P.ESTATICA  P.DINAMICA\n\n");
   for(int i=0;i<5;i++){
      printf("%s\t%d\t%s",Lista[i].nombre,Lista[i].id,estados[Lista[i].estado-1]);
      gotoxy(36,i+7);
      printf("%d",Lista[i].direccion);
      gotoxy(48,i+7);printf("%d",Lista[i].tam_pila);
      gotoxy(62,i+7);printf("%d",Lista[i].prioridad_estatica);
      gotoxy(72,i+7);printf("%d\n",Lista[i].prioridad_dinamica);
   }
   getch();
}

void modifPrior(){
   clrscr();
   for(int i=0;i<5;i++){
      printf("\nIntroduce la nueva prioridad del proceso %d: ",i+1);
      scanf("%d",&Lista[i].prioridad_estatica);
      Lista[i].prioridad_dinamica=Lista[i].prioridad_estatica;
   }
}
void dibujaMesa(){
   clrscr();
   gotoxy(10,9); cprintf(" \\  /");
   gotoxy(10,10);cprintf(" ÚÄ¿ ");
   gotoxy(10,11);cprintf("Ä ÀÄÙ Ä");
   gotoxy(10,12);cprintf("  | ");
}
//----------------------------------MAIN-----------------------------------

void main(){
  char x;
  ban=1;
  dir_inicio_pila=&x;

  Mesa.inicializa(4);
  for(e=0;e<5;e++)
     Tenedores[e].inicializa(1);

  //-----Inicializacion del BCP-----
  Lista[0].direccion=&Filosofo1;
  Lista[1].direccion=&Filosofo2;
  Lista[2].direccion=&Filosofo3;
  Lista[3].direccion=&Filosofo4;
  Lista[4].direccion=&Filosofo5;

  for(int j=0;j<5;j++){
     Lista[j].estado=0;
     Lista[j].id=j+1;
     Lista[j].prioridad_estatica=Lista[j].prioridad_dinamica=5;
  }
  strcpy(Lista[0].nombre,"Filosofo 1");
  strcpy(Lista[1].nombre,"Filosofo 2");
  strcpy(Lista[2].nombre,"Filosofo 3");
  strcpy(Lista[3].nombre,"Filosofo 4");
  strcpy(Lista[4].nombre,"Filosofo 5");

  //-----Fin de la inicializacion-----

  do{
     clrscr();
     textcolor(7);
     if(ban==0){
	printf("\n\tMENU:\n\t");
	printf("\n\t1-Otras 100 iteraciones");
	printf("\n\t2-Mostrar el contenido del descriptor de procesos");
	printf("\n\t3-Modificar prioridades");
	printf("\n\t4-Muestra Semaforos");
	printf("\n\t5-Salir");
	printf("\n\n\tOpcion: ");
	scanf("%d",&op);
     }else
	op=1;

     switch(op){
	case 1:{_setcursortype(_NOCURSOR);
		dibujaMesa();
		i=0;
		setjmp(DirSO);
		ban=0;
		//--------------Inicio de iteraciones--------------
		for(;i++<100;){
		   //Elegir siguiente proceso
		   aptBCPejec=&Lista[0];
		   for(c=1;c<5;c++){
		      if(aptBCPejec->prioridad_dinamica<Lista[c].prioridad_dinamica)
			 aptBCPejec=&Lista[c];
		   }
		   //Envejecer procesos
		   for(c=0;c<5;c++)
		      if(Lista[c].estado!=Bloqueado)
			 Lista[c].prioridad_dinamica++;
		   //Reestablecer prioridad dinamica
		   if(aptBCPejec->estado!=Bloqueado)
		      aptBCPejec->prioridad_dinamica=aptBCPejec->prioridad_estatica;

		   if(aptBCPejec->estado==Inicial){
		      aptBCPejec->estado=Ejecucion;
		      (aptBCPejec->direccion)();
		      aptBCPejec->estado=Listo;
		   }else
		      if(aptBCPejec->estado==Listo)
			 restaurar_contexto();
		}
		//---------------Fin de iteraciones----------------
		_setcursortype(_NORMALCURSOR);
		cprintf("\n\n\n\n\nPresiona cualquier tecla para continuar");
		getch();
	       }break;
	case 2:muestraBCP();
	       break;
	case 3:modifPrior();
	       break;
	case 4:{printf("\n\tSelecciona el semaforo:");
		printf("\n\n\t1-Mesa\n\t2-Tenedores\n\n\t");
		scanf("%d",&semSel);
		if(semSel==1)
		   Mesa.muestra();
		else
		   if(semSel==2){
		      for(e=0;e<5;e++)
			 Tenedores[e].muestra();
		   }else{
		      printf("\n\n\tComando invalido");
		      delay(1500);
		   }
	       }break;
	case 5:printf("\n\n\tFin del Programa");
	       break;
	default:{printf("\n\tDebes seleccionar un numero de entre el 1 y el 5");
		 delay(2000);
		}
     }
  }while(op!=5);
  delay(1000);
}
//Ctrl+F8 = Activar breakpoint en la linea seleccionada
