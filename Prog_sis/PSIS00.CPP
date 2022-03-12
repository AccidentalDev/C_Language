#include<stdio.h>
#include<conio.h>
void main(void){
 FILE *fPoint;
 char linea[51],ruta[50],car;
 int i=0,j=0,ban=1;
 clrscr();
 printf("\n\n\tEscribe la ruta y el nombre del archivo a abrir:\n\t");
 scanf("%s",&ruta);
 fflush(stdin);
 if((fPoint=fopen(ruta,"rt"))==NULL){
    printf("\n\n\tError al abrir el archivo\n\t");
    getch();
 }else{
    printf("\n    ****************************************************\n");
    while(fgets(linea,50,fPoint)!=NULL){
       car=linea[i];
       while(c!='\n'||c!='\0'||c!=';'){
	  switch(ban){
	       case 1:{if(c!=' '||c!='\t')
			  etiqueta[j++]=c;
		      }break;
	       case 2:{if(c!=' '||c!='\t')
			  codOp[j++]=c;
		      }break;
	       case 3:{if(c!=' '||c!='\t')
			  operando[j++]=c;
		      }break;
	       default:
	  }
       }
    }
    printf("\n    ****************************************************\n");
    fclose(fPoint);
 }
 printf("\n\n\tPresiona cualquier tecla para salir del programa");
 getch();
}