#include<stdio.h>
#include<conio.h>

int busquedaBin(int arr[],int elem,int primero,int ultimo){
   int mitad;
   while(primero<=ultimo){
      mitad=(primero+ultimo)/2;
      if(elem==arr[mitad])
	 return mitad;
      else
	 if(elem<arr[mitad])
	    ultimo=mitad-1;
	 else
	    primero=mitad+1;
   }
   return -1;
}

void main(){
   int dato,lugar;
   int vector[30]={1,2,2,3,5,6,7,8,9,11,13,14,14,16,18,22,23,24,25,28,30,31,31,33,37,38,42,43,44,47};
   clrscr();
   printf("\nElemento: ");
   scanf("%d",&dato);
   lugar=busquedaBin(vector,dato,0,29);
   if(lugar==-1)
      printf("No se encontro");
   else
      printf("El elemento se encuentra en la posicion %d",lugar);
   getch();
}