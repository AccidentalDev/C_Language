/*
  Carlos Francisco Camacho Uribe
  Codigo: 398251049
  Taller de Programacion de sistemas
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>

void main(void){
 FILE *fPoint;
 char linea[51],ruta[50],c;
 char etiqueta[15],codOp[10],operando[20];
 int i=0,j=0,ban=1,cLinea=1,banCom=0;

 clrscr();
 printf("\n\n\tEscribe la ruta y el nombre del archivo a abrir (sin extension):\n\t");
 scanf("%s",&ruta);
 fflush(stdin);
 strcat(ruta,".asm");
 if((fPoint=fopen(ruta,"rt"))==NULL){
    printf("\n\n\tError al abrir el archivo\n\t");
 }else{
    printf("\n    ****************************************************");
    while(fgets(linea,50,fPoint)!=NULL){
       etiqueta[0]='\0';
       codOp[0]='\0';
       operando[0]='\0';
       c=linea[i];
       ban=1;j=0;
       while(c!='\n'&&c!='\0'){
	  if(c==';'){
	     banCom=1;
	     break;
	  }
	  switch(ban){
	       case 1:{if(c!=' '&&c!='\t'){
			  etiqueta[j]=c;
			  j++;
			  etiqueta[j]='\0';
		       }
		      }break;
	       case 2:{if(c!=' '&&c!='\t'){
			  codOp[j]=c;
			  j++;
			  codOp[j]='\0';
		       }
		      }break;
	       case 3:{if(c!=' '&&c!='\t'){
			  operando[j]=c;
			  j++;
			  operando[j]='\0';
		       }
		      }break;
	       default:printf("\n\n\tError en la clasificacion de la linea\n\t");
	  }
	  if(c==' '||c=='\t')
	     if(j!=0){
		ban++;
		if(ban==4)
		   ban=1;
		j=0;
	     }
	  i++;
	  c=linea[i];
       }
       i=0;
       if(operando[0]=='\0'){
	  if(codOp[0]=='\0'){
	     strcpy(codOp,etiqueta);
	     etiqueta[0]='\0';
	  }else{
	     if(strcmpi("org",etiqueta)==0){
		strcpy(operando,codOp);
		strcpy(codOp,etiqueta);
		etiqueta[0]='\0';
	     }
	  }
       }
       printf("\n\n\tLinea: %d",cLinea++);
       printf("\n\tEtiqueta: %s",etiqueta);
       printf("\n\tCodOp: %s",codOp);
       printf("\n\tOperando: %s",operando);
       if(banCom==1){
	  printf("\n\t*La linea contiene un comentario*");
	  banCom=0;
       }
       getch();
    }
    printf("\n    ****************************************************\n");
    fclose(fPoint);
 }
 printf("\n\n\tPresiona cualquier tecla para salir del programa");
 getch();
}