//Carlos Fco. Camamcho Uribe
//Taller de Estructura de Archivos
//Lectura de registros en archivo
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<io.h>
#include<string.h>
typedef struct{
   int folio;
   char nombre[21];
   float total;
}Fact;

void main(){
   Fact facturas[8];
   char c,temp[21];
   int desc,pos=0,reg=0,campo=1;
   clrscr();
   printf("\n\tLECTURA DE ARCHIVOS PARA ALMACENAR EN REGISTRO\n\t");
   printf("\n\tPresiona cualquier tecla para continuar...\n\t");
   getch();
   if((desc=open("C:/Usuarios/Fact.txt",0))>=0){
	  while(read(desc,&c,1)!=0){
		 if((c!=',')&&(c!='*')){
			temp[pos]=c;
			pos++;
		 }else{
			if(c==','){
			   temp[pos]='\0';
			   pos=0;
			   switch(campo){
					 case 1:{facturas[reg].folio=atoi(temp);
							 campo++;
							}break;
					 case 2:{strcpy(facturas[reg].nombre,temp);
							 campo++;
							}break;
					 default: printf("\n\tError al escribir en registro (campo no existente)");
			   }
			}else
			   if(c=='*'){
				  temp[pos]='\0';
				  facturas[reg].total=atof(temp);
				  pos=0;
				  reg++;
				  campo=1;
			   }
		 }
	  }
	  close(desc);
	  printf("\n\tArchivo leido con exito\n\t");
	  getch();
   }else
	  printf("\n\tError al abrir el archivo");
   for(int i=0;i<reg;i++)
	  printf("\n\t%d %s %f",facturas[i].folio,facturas[i].nombre,facturas[i].total);
   getch();
}