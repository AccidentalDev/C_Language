//Convertidor de entero a hexadecimal
#include<stdio.h>
#include<conio.h>
void main(){
   char op;
   int dato;
   do{
     clrscr();
     printf("\n\n\tEscribe un numero entero: ");
     scanf("%d",&dato);
     printf("\n\n\ten hexadecimal es: %X",dato);
     printf("\n\n\tconvertir otro numero?\n\t");
     op=getch();
   }while(op!='n');
}