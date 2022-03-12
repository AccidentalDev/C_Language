//Carlos Francisco Camacho Uribe
//Torres de Hanoi
#include<stdio.h>
#include<conio.h>
#include<Pila.h>
#include<dos.h>
void imprime(struct pila t[]){
   int i,j,k;
   clrscr();
   printf("\n|");
   for(i=0;i<=t[0].tope;i++)
      printf("%d ", t[0].elems[i]);
   printf("\n|");
   for(j=0;j<=t[1].tope;j++)
      printf("%d ", t[1].elems[j]);
   printf("\n|");
   for(k=0;k<=t[2].tope;k++)
      printf("%d ", t[2].elems[k]);
   delay(1200);
}
void mov(struct pila &a,struct pila &b){
   entero aux;
   aux=ValorEnTope(a);
   Push(aux,b);
   Pop(a);
}
void torres(struct pila t[],int a,int b,int c,int n){
   if(n==1){
      mov(t[a],t[b]);
      imprime(t);
      return;
   }
   else{
      torres(t,a,c,b,n-1);
      mov(t[a],t[b]);
      imprime(t);
      torres(t,c,b,a,n-1);
   }
}
void main(){
   int n,z;
   clrscr();
   struct pila Torres[3];
   Inicializa(Torres[0]);
   Inicializa(Torres[1]);
   Inicializa(Torres[2]);
   printf("Torres de Hanoi\n");
   printf("De cuantos discos quieres que sea la torre\n");
   scanf("%d", &n);
   z=n;
   for(int i=0;i<n;i++){
      Torres[0].tope++;
      Torres[0].elems[i]=z--;
   }
   imprime(Torres);
   torres(Torres,0,2,1,n);
   printf("\n\nLa torre se ha movido totalmente");
   getch();
}