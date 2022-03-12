//Carlos Fco. Camacho Uribe
//Taller de Programacion de Sistemas
//Practica 01
#include<stdio.h>
#include<conio.h>
#include<string.h>
void main(){
   char cadena[30],temp[30],*et=0,*mnem=0,*op=0,*com=0;
   clrscr();
   printf("\n\n\tEscribe una linea de programa\n");
   printf("\t(<etiqueta> <mnemonco> <operando> <comentarios>):\n\t");
   fflush(stdin);
   gets(cadena);
   strcpy(temp,cadena);
   et=strtok(temp," ");
   mnem=strtok(NULL," ");
   op=strtok(NULL," ");
   com=strtok(NULL," ");
   printf("\n\n\tEtiqueta: %s",et);
   printf("\n\tMnemonico: %s",mnem);
   printf("\n\tOperandos: %s",op);
   printf("\n\tComentarios: %s",com);
   printf("\n\nPresione cualquier tecla para salir del programa");
   getch();
}