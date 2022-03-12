//Carlos Francisco Camacho Uribe
//Pila.h
#define MAX 50
#define valor_error -999
typedef int entero;
typedef short int posicion;
typedef enum logico{false=0,true};

struct pila{
   entero elems[MAX];
   posicion tope;
};

void Inicializa(struct pila &P){
   P.tope=-1;
}
logico Vacia(struct pila P){
   if(P.tope==-1)
      return(true);
   else
      return(false);
}
logico Llena(struct pila P){
   if(P.tope==MAX-1)
      return(true);
   else
      return(false);
}
logico Push(entero x,struct pila &P){
   if(Llena(P))
      return(false);
   else{
      P.tope++;
      P.elems[P.tope]=x;
      return(true);
   }
}
logico Pop(struct pila &P){
   if(Vacia(P))
      return(false);
   else{
      P.tope--;
      return(true);
   }
}
entero ValorEnTope(struct pila P){
   if(Vacia(P))
      return(valor_error);
   else
      return(P.elems[P.tope]);
}