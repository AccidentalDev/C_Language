//Carlos Francisco Camacho Uribe
//Cola.h
#define MAX 10
#define valor_error -999
typedef int entero;
typedef short int posicion;
typedef enum logico{false=0,true};

typedef struct{
   entero elems[MAX];
   posicion frente,final;
}Cola;

void Inicializa(Cola &C){
   C.frente=0;
   C.final=MAX-1;
}
logico Vacia(Cola C){
   if((C.frente==0&&C.final==MAX-1)||(C.frente==C.final+1))
      return(true);
   else
      return(false);
}
logico Llena(Cola C){
   if((C.frente==1&&C.final==MAX-1)||(C.frente==0&&C.final==MAX-2)||(C.frente==C.final+2))
      return(true);
   else
      return(false);
}
logico PoneEnCola(entero x,Cola &C){
   if(Llena(C))
      return(false);
   else{
      if(C.final==MAX-1)
	 C.final=0;
      else
	 C.final++;
      C.elems[C.final]=x;
      return(true);
   }
}
logico QuitaDeCola(Cola &C){
   if(Vacia(C))
      return(false);
   else{
      if(C.frente==MAX-1)
	 C.frente=0;
      else
	 C.frente++;
      return(true);
   }
}
entero ValorEnTope(Cola C){
   if(!Vacia(C))
      return(C.elems[C.frente]);
   else
      return(valor_error);
}