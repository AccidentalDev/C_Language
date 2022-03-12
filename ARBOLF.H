//Carlos Francisco Camacho Uribe
//Taller de Estructura de Datos
//Arboles binarios
#include <stdio.h>
#include <conio.h>
//#include<iostream.h>
typedef int tipo_elem;
typedef struct nodo{
	 tipo_elem info;//NRR
	 int codigo;
	 int nivel;
	 struct nodo *der,*izq;
}*Nodo;

void preorden(Nodo R,FILE *pIndex){
	 if(R!=NULL){
		fwrite(&R->codigo,sizeof(R->codigo),1,pIndex);
		fwrite(&R->info,sizeof(R->info),1,pIndex);
		preorden(R->izq,pIndex);
		preorden(R->der,pIndex);
	 }
}
void  orden(Nodo R,FILE *pIndex){
	 if(R!=NULL){
		orden(R->izq,pIndex);
		fwrite(&R->codigo,sizeof(R->codigo),1,pIndex);
		fwrite(&R->info,sizeof(R->info),1,pIndex);
		orden(R->der,pIndex);
	 }
}
void postorden(Nodo R,FILE *pIndex){
	 if(R!=NULL){
		postorden(R->izq,pIndex);
		postorden(R->der,pIndex);
		fwrite(&R->codigo,sizeof(R->codigo),1,pIndex);
		fwrite(&R->info,sizeof(R->info),1,pIndex);
	 }
}

void Inicializa(Nodo &R){
	 R=NULL;
}

void Inserta(int n,int cod,tipo_elem x,Nodo &R){
	 if(R==NULL){
		R=new nodo;
		R->codigo=cod;
		R->info=x;
		R->nivel=n;
		R->izq=NULL;
		R->der=NULL;
	 }
	 else
		if(cod>R->codigo)
	 Inserta(n+1,cod,x,R->der);
		else
	 if(cod<R->codigo)
		Inserta(n+1,cod,x,R->izq);
}

Nodo busquedaBin(int cod,Nodo R){  //Necesita modificarse el valor que regresa
   Nodo temp;
   temp=R;
   if(temp==NULL)
      return(temp);
   else
      if(temp->codigo==cod)
	 return(temp);
      else
	 if(cod>temp->codigo)
	    return busquedaBin(cod,temp->der);
	 else
	    return busquedaBin(cod,temp->izq);
}

Nodo temp2;
void elimCaso3(Nodo T){
	 Nodo temp3=T;
	 if(temp3->der!=NULL)
		elimCaso3(temp3->der);
	 else{
		temp2->codigo=temp3->codigo;
		temp2->info=temp3->info;
		temp2->nivel=temp3->nivel;
		temp2=temp3;
		temp3=temp3->izq;
	 }
	 T=temp3;
}

void eliminar(int x,Nodo &R){
   Nodo temp=R;
   if(temp==NULL)
      printf("\nElemento no encontrado\n");
   else
      if(x<temp->codigo)
	 eliminar(x,temp->izq);
      else
	 if(x>temp->codigo)
	    eliminar(x,temp->der);
	 else{
	    temp2=temp;
	    if(temp2->der==NULL)
	       temp=temp2->izq;
	    else
	       if(temp2->izq==NULL)
		  temp=temp2->der;
	       else
		  elimCaso3(temp2->izq);
	 }
	 delete(temp2);
	 R=temp;
}

/*---------------------------------MAIN------------------------------*/
/*
void main(){
	 Nodo Raiz;
	 int dato,aux;
	 char sel2;
	 int sel;
	 Inicializa(Raiz);
	 do{clrscr();
	printf("\nArboles Binarios\n");
	printf("\nHaz tu seleccion:\n");
	printf("1. Insertar un elemento.\n");
	printf("2. Eliminar un elemento.\n");
	printf("3. El nivel en el que se encuentra un elemento.\n\n");
	printf("4. Recorrer el arbol en preorden.\n");
	printf("5. Recorrer el arbol en orden.\n");
	printf("6. Recorrer el arbol en postorden.\n\n");
	printf("7. Salir del programa.\n");
	cin>>sel;
	switch(sel){
	 case 1:{do{
			 clrscr();
			 printf("\nEscribe el elemento a insertar:\n");
			 cin>>dato;
			 Inserta(0,dato,Raiz);
			 printf("\n¨Quieres insertar otro elemento? s/n\n");
			 cin>>sel2;
		 }while(sel2=='s');
		}break;
	 case 2:{do{
			 clrscr();
			 printf("\nEscribe el elemento a eliminar:\n");
			 cin>>dato;
			 eliminar(dato,Raiz);
			 printf("\n¨Quieres eliminar otro elemento? s/n\n");
			 cin>>sel2;
		 }while(sel2=='s');
		}break;
	 case 3:{do{
			 clrscr();
			 printf("\nEscribe el elemento del que quieres saber su nivel en el arbol\n");
			 cin>>dato;
			 aux=busquedaBin(dato,Raiz);
			 if(aux==-1)
					printf("\nEse elemento no se encuentra en el arbol\n");
			 else
					printf("\nEl elemento que buscas esta en el nivel %d\n",aux);
			 printf("\n¨Quieres saber el nivel de otro elemento? s/n\n");
			 cin>>sel2;
		 }while(sel2=='s');
		}break;
	 case 4:{clrscr();
		 printf("\n\t");
		 preorden(Raiz);
		 getch();
		}break;
	 case 5:{clrscr();
		 printf("\n\t");
		 orden(Raiz);
		 getch();
		}break;
	 case 6:{clrscr();
		 printf("\n\t");
		 postorden(Raiz);
		 getch();
		}break;
	 case 7:{printf("\nPresione cualquier tecla para salir del programa\n");
		}break;
	 default:{printf("\nDebes elegir de entre el 1 y el 6\n");
			getch();}
	 }
	 }while(sel!=7);
	 getch();
}*/