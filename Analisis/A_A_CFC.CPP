//Carlos Fco. Camamcho Uribe
//Taller de Estructura de Archivos
//Captura de datos para agregarlos en archivo
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<io.h>
#include<string.h>
void main(){
  char temp[21];
  int fdes;
  clrscr();
  if((fdes=open("C:/Usuarios/alumnos.txt",2))<0)
     printf("\n\tERROR al abrir el archivo\n\t");
  else{
     printf("\n\tCAPTURA DE DATOS PARA GUARDARLOS EN ARCHIVO\n\t");
     printf("\n\tEscribe el codigo del alumno:\n\t");
     scanf("%s", &temp);
     lseek(fdes,0L,2);
     write(fdes,&temp,strlen(temp));
     write(fdes,"&",1);
     printf("\n\tescribe su nombre:\n\t");
     scanf("%s", &temp);
     fflush(stdin);
     write(fdes,&temp,strlen(temp));
     write(fdes,"&",1);
     printf("\n\tescribe su direccion:\n\t");
     scanf("%s", &temp);
     fflush(stdin);
     write(fdes,&temp,strlen(temp));
     write(fdes,"&",1);
     printf("\n\tescribe su telefono:\n\t");
     scanf("%s", &temp);
     write(fdes,&temp,strlen(temp));
     write(fdes,"&",1);
     printf("\n\tescribe su sexo (M/F):\n\t");
     scanf("%s", &temp);
     write(fdes,&temp,strlen(temp));
     write(fdes,"&",1);
     printf("\n\tescribe su calendario de ingreso:\n\t");
     scanf("%s", &temp);
     write(fdes,&temp,strlen(temp));
     write(fdes,"*",1);
     close(fdes);
  }
  getch();
}