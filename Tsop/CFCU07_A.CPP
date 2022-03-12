//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 07: Problema del Productor-Consumidor

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<setjmp.h>
#include<mem.h>
#include<string.h>
#include<c:\Temp\Tc\Prog\tsop\cola_sop.h>

#define Inicial 0
#define Listo 1
#define Ejecucion 2
#define Bloqueado 3
#define delVar 500


jmp_buf DirSO;
char *dir_inicio_pila;
int buffer=0;
int op,i,c,tmp,ban,semSel;

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
BCP Lista[3];

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
      void muestra();//agregar parametro para elegir entre Leer y Escribir
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
Semaforo leer;
Semaforo escribir;
//----------------Definicion de los procesos---------------
void Productor(){
   int sigValor=0;
   while(1){
      sigValor+=3;ceder_control();
      escribir.wait();
      buffer=sigValor;ceder_control();
      leer.signal();ceder_control();
   }
}
void Consumidor(){
   int NewVal=0;
   while(1){
      leer.wait();
      NewVal=buffer;ceder_control();
      escribir.signal();
      //Mostrar el valor recuperado:
      cprintf(" %d",NewVal);delay(1000);ceder_control();
   }
}
/*void proceso3(){
   while(1){
      exclusion.wait();
      printf("\n\n\t⁄+++++++ø (p3)\n\r");ceder_control();
      printf("\t≥+++++++≥ (p3)\n\r");ceder_control();
      printf("\t¿+++++++Ÿ (p3)\n\r");ceder_control();
      sound(300);
      delay(50);
      nosound();
      delay(1000);
      exclusion.signal();
   }
}
void proceso4(){
   while(1){
      exclusion.wait();
      printf("\n\n\t⁄///////ø (p4)\n\r");ceder_control();
      printf("\t≥///////≥ (p4)\n\r");ceder_control();
      printf("\t¿///////Ÿ (p4)\n\r");ceder_control();
      sound(350);
      delay(50);
      nosound();
      delay(1000);
      exclusion.signal();
   }
}
void proceso5(){
   while(1){
      exclusion.wait();
      printf("\n\n\t⁄ßßßßßßßø (p5)\n\r");ceder_control();
      printf("\t≥ßßßßßßß≥ (p5)\n\r");ceder_control();
      printf("\t¿ßßßßßßßŸ (p5)\n\r");ceder_control();
      sound(400);
      delay(50);
      nosound();
      delay(1000);
      exclusion.signal();
   }
}
void proceso6(){
   while(1){
      exclusion.wait();
      printf("\n\n\t⁄¶¶¶¶¶¶¶ø (p6)\n\r");ceder_control();
      printf("\t≥¶¶¶¶¶¶¶≥ (p6)\n\r");ceder_control();
      printf("\t¿¶¶¶¶¶¶¶Ÿ (p6)\n\r");ceder_control();
      sound(450);
      delay(50);
      nosound();
      delay(1000);
      exclusion.signal();
   }
}
void proceso7(){
   while(1){
      exclusion.wait();
      printf("\n\n\t⁄=======ø (p7)\n\r");ceder_control();
      printf("\t≥=======≥ (p7)\n\r");ceder_control();
      printf("\t¿=======Ÿ (p7)\n\r");ceder_control();
      sound(500);
      delay(50);
      nosound();
      delay(1000);
      exclusion.signal();
   }
}
void proceso8(){
   while(1){
      exclusion.wait();
      printf("\n\n\t⁄¬¬¬¬¬¬¬ø (p8)\n\r");ceder_control();
      printf("\t≥≈≈≈≈≈≈≈≥ (p8)\n\r");ceder_control();
      printf("\t¿¡¡¡¡¡¡¡Ÿ (p8)\n\r");ceder_control();
      sound(550);
      delay(50);
      nosound();
      delay(1000);
      exclusion.signal();
   }
}
void proceso9(){
   while(1){
      exclusion.wait();
      printf("\n\n\t⁄.......ø (p9)\n\r");ceder_control();
      printf("\t≥.......≥ (p9)\n\r");ceder_control();
      printf("\t¿.......Ÿ (p9)\n\r");ceder_control();
      sound(600);
      delay(50);
      nosound();
      delay(1000);
      exclusion.signal();
   }
}
void proceso10(){
   while(1){
      exclusion.wait();
      printf("\n\n\t⁄<<<<<<<ø (p10)\n\r");ceder_control();
      printf("\t≥>>>>>>>≥ (p10)\n\r");ceder_control();
      printf("\t¿<<<<<<<Ÿ (p10)\n\r");ceder_control();
      sound(650);
      delay(50);
      nosound();
      delay(1000);
      exclusion.signal();
   }
}*/
//------------Fin definicion de los procesos------------

void muestraBCP(){
   char estados[3][14];
   strcpy(estados[0],"Listo");
   strcpy(estados[1],"Ejecutando");
   strcpy(estados[2],"Bloqueado");
   clrscr();
   printf("\n\tContenido del Descriptor de Procesos\n");
   printf("\n\n");
   printf("NOMBRE\t\tID\tESTADO  DIRECCION  Tama§oPila  P.ESTATICA  P.DINAMICA\n\n");
   for(int i=0;i<2;i++){
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
   for(int i=0;i<2;i++){
      printf("\nIntroduce la nueva prioridad del proceso %d: ",i+1);
      scanf("%d",&Lista[i].prioridad_estatica);
      Lista[i].prioridad_dinamica=Lista[i].prioridad_estatica;
   }
}
//----------------------------------MAIN-----------------------------------

void main(){
  char x;
  ban=1;
  dir_inicio_pila=&x;

  leer.inicializa(0);
  escribir.inicializa(1);

  //-----Inicializacion del BCP-----
  Lista[0].direccion=&Productor;
  Lista[1].direccion=&Consumidor;
  /*Lista[2].direccion=&proceso3;
  Lista[3].direccion=&proceso4;
  Lista[4].direccion=&proceso5;
  Lista[5].direccion=&proceso6;
  Lista[6].direccion=&proceso7;
  Lista[7].direccion=&proceso8;
  Lista[8].direccion=&proceso9;
  Lista[9].direccion=&proceso10;*/

  for(int j=0;j<2;j++){
     Lista[j].estado=0;
     Lista[j].id=j+1;
     Lista[j].prioridad_estatica=Lista[j].prioridad_dinamica=5/*j+1*/;
  }
  strcpy(Lista[0].nombre,"Productor");
  strcpy(Lista[1].nombre,"Consumidor");
  /*strcpy(Lista[2].nombre,"Proceso 3");
  strcpy(Lista[3].nombre,"Proceso 4");
  strcpy(Lista[4].nombre,"Proceso 5");
  strcpy(Lista[5].nombre,"Proceso 6");
  strcpy(Lista[6].nombre,"Proceso 7");
  strcpy(Lista[7].nombre,"Proceso 8");
  strcpy(Lista[8].nombre,"Proceso 9");
  strcpy(Lista[9].nombre,"Proceso 10");*/
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
	case 1:{printf("\n\n\t");
		i=0;
		setjmp(DirSO);
		ban=0;
		//--------------Inicio de iteraciones--------------
		for(;i++<100;){
		   //Elegir siguiente proceso
		   aptBCPejec=&Lista[0];
		   for(c=1;c<2;c++){
		      if(aptBCPejec->prioridad_dinamica<Lista[c].prioridad_dinamica)
			 aptBCPejec=&Lista[c];
		   }
		   //Envejecer procesos
		   for(c=0;c<2;c++)
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
		printf("\n\n\tPresiona cualquier tecla para continuar");
		getch();
	       }break;
	case 2:muestraBCP();
	       break;
	case 3:modifPrior();
	       break;
	case 4:{printf("\n\tSelecciona el semaforo:");
		printf("\n\n\t1-Leer\n\t2-Escribir\n\n\t");
		scanf("%d",&semSel);
		if(semSel==1)
		   leer.muestra();
		else
		   if(semSel==2)
		      escribir.muestra();
		   else{
		      printf("\n\n\tComando invalido");
		      delay(1500);
		   }
	       }break;
	case 5:printf("\n\n\tFin del Programa");
	       break;
	default:{printf("\n\tDebes seleccionar un numero de entre el 1 y el 4");
		 delay(2000);
		}
     }
  }while(op!=5);
  delay(1000);
}
//Ctrl+F8 = Activar breakpoint en la linea seleccionada
/*Este programa es interesante por el hecho de que
se puede probar fielmente el algoritmo del preblema
del Productor-Consumidor; ademas, gracias a que los
programas anteriores en los que se baso este estan
completamente depurados, no existio ningun problema
grave a la hora de ejecutarlo.*/