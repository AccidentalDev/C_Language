#include<stdio.h>
#include<conio.h>
#include<string.h>
void main(){
 char *cadena="Carlos";
 int tamanyo;

 clrscr();
 tamanyo=strlen(cadena);
 printf("\n\n\tLetra final: %c",cadena[tamanyo-1]);
 getch();
}