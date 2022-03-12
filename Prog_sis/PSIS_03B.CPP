//Carlos Fco. Camacho Uribe
//Taller de Programacion de Sistemas
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<io.h>
#include<stdlib.h>
void ensambla(char cadena[]){
   char temp[30],*et=0,*mnem=0,*op=0,*com=0,*check=0;
   int operando;
   strcpy(temp,cadena);
   if(temp[0]!='\t'){
      et=strtok(temp,"\t");
      mnem=strtok(NULL," ");
   }else{
      mnem=strtok(temp," ");
      mnem=mnem+1;
   }
   op=strtok(NULL," ");
   com=strtok(NULL," ");
   printf("\n\tEtiqueta: %s",et);
   printf("\n\tMnemonico: %s",mnem);
   printf("\n\tOperandos: %s",op);
   printf("\n\tComentarios: %s",com);
   check=strchr(op,'#');
   if(check==0){
      check=strchr(op,'_');
      if(check==0){
	 check=strchr(op,',');
	 if(check==0){
	    operando=atoi(op);
	    if(operando>255)
	       printf("\n\t**Es un modo de direccionamiento extendido**\n");
	    else
	       printf("\n\t**Es un modo de direccionamiento directo**\n");
	 }else
	    printf("\n\t**Es un modo de direccionamiento indexado**\n");
      }else
	 printf("\n\t**Es un modo de direccionamiento inherente**\n");
   }else{
      if(strlen(op)>4)
	 printf("\n\t**Es un modo de direccionamiento extendido**\n");
      else
	 printf("\n\t**Es un modo de direccionamiento inmediato**\n");
    }
}
//----------------------------------MAIN-----------------------------------
void main(){
 char linea[30];
 char *path=0,*name=0,tmp;
 int contloc,file,posnull,endFile;
 clrscr();
 path="C:/Temp/";
 name="test.asm";
 strcat(path,name);
 /*printf("\n\tEscribe el nombre del archivo .asm a abrir:\n\t");
 gets(name);
 printf("\n\tEscribe la ruta:\n\t");
 gets(path);*/
 if((file=open(path,0))<0)
    printf("\n\tError al abrir el archivo\n\t");
 else{
    for(int j=0;(endFile=read(file,&tmp,1))!=0;j++){
       for(int i=0;i<30&&tmp!='\n'&&endFile!=0;i++){
	  linea[i]=tmp;
	  endFile=read(file,&tmp,1);
	  posnull=i;
       }
       linea[posnull+1]='\0';
       ensambla(linea);
    }
 close(file);
 }
 getch();
}
