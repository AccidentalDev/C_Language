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
#include<c:\Temp\Tc\Prog\tsop\cola_sop.h>

#define Inicial 0
#define Listo 1
#define Ejecucion 2
#define Bloqueado 3
#define delVar 200


jmp_buf DirSO;
char *dir_inicio_pila;
int op,i,c,e,tmp,ban,semSel,x,y;
int b1,b2,b3,b4,b5;

typedef struct{
   int id;
   char nombre[20];
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
   //clrscr();
   printf("\n\tContenido del Semaforo\n\n");
   printf("\tELEMENTOS EN COLA:         VALOR:\n");
   if(Vacia(cola_id_proc_espera))
      printf("\t   Cola Vacia");
   else{
      counter=cola_id_proc_espera.frente-1;
      do{
	counter++;
	if(counter==MAX)
	   counter=0;
	printf("\t   %s\n",Lista[cola_id_proc_espera.elems[counter]-1].nombre);
      }while(counter!=cola_id_proc_espera.final);
   }
   gotoxy(38,7);printf("%d",valor);
   getch();
}
//******************fin definicion semaforo******************
Semaforo Mesa;
Semaforo Tenedores[5];

void pensar(int phy){
   int ranVal;
   switch(phy){
	 case 1:{x=13;y=9;ceder_control();
		}break;
	 case 2:{x=16;y=10;ceder_control();
		}break;
	 case 3:{x=15;y=12;ceder_control();
		}break;
	 case 4:{x=11;y=12;ceder_control();
		}break;
	 case 5:{x=10;y=10;ceder_control();
		}break;
   }
   ranVal=random(10);ceder_control();
   for(e=0;e<=ranVal;e++){
      gotoxy(x,y);cprintf("|");sound(150);delay(delVar-100);nosound();
      gotoxy(x,y);cprintf("/");sound(150);delay(delVar-100);nosound();
      gotoxy(x,y);cprintf("�");sound(150);delay(delVar-100);nosound();
      gotoxy(x,y);cprintf("\\");sound(150);delay(delVar-100);nosound();
   }
   gotoxy(x,y);cprintf("");ceder_control();
}
void comer(int phy){
   switch(phy){
	 case 1:{x=13;y=9;ceder_control();
		}break;
	 case 2:{x=16;y=10;ceder_control();
		}break;
	 case 3:{x=15;y=12;ceder_control();
		}break;
	 case 4:{x=11;y=12;ceder_control();
		}break;
	 case 5:{x=10;y=10;ceder_control();
		}break;
   }
   for(e=0;e<=10;e++){
      gotoxy(x,y);cprintf("C");sound(300);delay(delVar);nosound();
      gotoxy(x,y);cprintf("c");sound(200);delay(delVar);nosound();
   }
   gotoxy(x,y);cprintf("");ceder_control();
}
//----------------Definicion de los procesos---------------
void Filosofo1(){
   while(1){
      pensar(1);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[4].wait();
      textcolor(6);gotoxy(11,9);cprintf("\\");textcolor(7);
      sound(900);delay(delVar+150);nosound();b5=1;
      ceder_control();
      Tenedores[0].wait();
      textcolor(6);gotoxy(15,9);cprintf("/");textcolor(7);
      sound(900);delay(delVar+150);nosound();b1=1;
      ceder_control();
      comer(1);ceder_control();
      gotoxy(13,9);cprintf("");
      Tenedores[4].signal();
      gotoxy(11,9);cprintf("\\");b5=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Tenedores[0].signal();
      gotoxy(15,9);cprintf("/");b1=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Mesa.signal();ceder_control();
   }
}
void Filosofo2(){
   while(1){
      pensar(2);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[0].wait();
      textcolor(6);gotoxy(15,9);cprintf("/");textcolor(7);
      sound(900);delay(delVar+150);nosound();b1=1;
      ceder_control();
      Tenedores[1].wait();
      textcolor(6);gotoxy(16,11);cprintf("�");textcolor(7);
      sound(900);delay(delVar+150);nosound();b2=1;
      ceder_control();
      comer(2);ceder_control();
      gotoxy(16,10);cprintf("");
      Tenedores[0].signal();
      gotoxy(15,9);cprintf("/");b1=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Tenedores[1].signal();
      gotoxy(16,11);cprintf("�");b2=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Mesa.signal();ceder_control();
   }
}
void Filosofo3(){
   while(1){
      pensar(3);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[1].wait();
      textcolor(6);gotoxy(16,11);cprintf("�");textcolor(7);
      sound(900);delay(delVar+150);nosound();b2=1;
      ceder_control();
      Tenedores[2].wait();
      textcolor(6);gotoxy(13,12);cprintf("|");textcolor(7);
      sound(900);delay(delVar+150);nosound();b3=1;
      ceder_control();
      comer(3);ceder_control();
      gotoxy(15,12);cprintf("");
      Tenedores[1].signal();
      gotoxy(16,11);cprintf("�");b2=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Tenedores[2].signal();
      gotoxy(13,12);cprintf("|");b3=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Mesa.signal();ceder_control();
   }
}
void Filosofo4(){
   while(1){
      pensar(4);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[2].wait();
      textcolor(6);gotoxy(13,12);cprintf("|");textcolor(7);
      sound(900);delay(delVar+150);nosound();b3=1;
      ceder_control();
      Tenedores[3].wait();
      textcolor(6);gotoxy(10,11);cprintf("�");textcolor(7);
      sound(900);delay(delVar+150);nosound();b4=1;
      ceder_control();
      comer(4);ceder_control();
      gotoxy(11,12);cprintf("");
      Tenedores[2].signal();
      gotoxy(13,12);cprintf("|");b3=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Tenedores[3].signal();
      gotoxy(10,11);cprintf("�");b4=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Mesa.signal();ceder_control();
   }
}
void Filosofo5(){
   while(1){
      pensar(5);ceder_control();
      Mesa.wait();ceder_control();
      Tenedores[3].wait();
      textcolor(6);gotoxy(10,11);cprintf("�");textcolor(7);
      sound(900);delay(delVar+150);nosound();b4=1;
      ceder_control();
      Tenedores[4].wait();ceder_control();
      textcolor(6);gotoxy(11,9);cprintf("\\");textcolor(7);
      sound(900);delay(delVar+150);nosound();b5=1;
      ceder_control();
      comer(5);ceder_control();
      gotoxy(10,10);cprintf("");
      Tenedores[3].signal();
      gotoxy(10,11);cprintf("�");b4=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
      Tenedores[4].signal();
      gotoxy(11,9);cprintf("\\");b5=0;
      sound(700);delay(delVar+150);nosound();ceder_control();
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
   printf("NOMBRE\t\tID\tESTADO  DIRECCION  Tama�oPila  P.ESTATICA  P.DINAMICA\n\n");
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
   gotoxy(10,10);cprintf(" �Ŀ ");
   gotoxy(10,11);cprintf("� ��� �");
   gotoxy(10,12);cprintf("  | ");

   if(b1==1){
      textcolor(6);gotoxy(15,9);
      cprintf("/");textcolor(7);
   }
   if(b2==1){
      textcolor(6);gotoxy(16,11);
      cprintf("�");textcolor(7);
   }
   if(b3==1){
      textcolor(6);gotoxy(13,12);
      cprintf("|");textcolor(7);
   }
   if(b4==1){
      textcolor(6);gotoxy(10,11);
      cprintf("�");textcolor(7);
   }
   if(b5==1){
      textcolor(6);gotoxy(11,9);
      cprintf("\\");textcolor(7);
   }
}
//----------------------------------MAIN-----------------------------------

void main(){
  char x;
  ban=1;
  b1=b2=b3=b4=b5=0;
  dir_inicio_pila=&x;

  Mesa.inicializa(4);
  for(e=0;e<5;e++)
     Tenedores[e].inicializa(1);

  randomize();
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
  strcpy(Lista[0].nombre,"Descartes (1)");
  strcpy(Lista[1].nombre,"Platon (2)");
  strcpy(Lista[2].nombre,"Carlos Marx (3)");
  strcpy(Lista[3].nombre,"John Locke (4)");
  strcpy(Lista[4].nombre,"Socrates (5)");

  //-----Fin de la inicializacion-----

  do{
     clrscr();
     textcolor(7);
     if(ban==0){
	printf("\n\tMENU:\n\t");
	printf("\n\t1-Otras 200 iteraciones");
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
		if(semSel==1){
		   clrscr();
		   printf("\n\tMESA\n");
		   Mesa.muestra();
		}else
		   if(semSel==2){
		      for(e=0;e<5;e++){
			 clrscr();
			 printf("\n\tTENEDOR %d\n",e+1);
			 Tenedores[e].muestra();
		      }
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
/*Cosas interesantes de este programa: el algoritmo del problema
de los filisofos fue rapidamente implementado en el codigo existente,
pero lo que tardo mas tiempo fue darle vida, o sea graficarlo, animarlo
y ponerle sonidos. La mayor parte del codigo de los filosofos tiene que
ver con aplicar sonidos dependiendo del evento ocurrido y con mostrar
de la manera mas amigable posible la resolucion del problema.*/