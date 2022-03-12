/*
  Carlos Francisco Camacho Uribe
  Codigo: 398251049
  Taller de Programacion de sistemas
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
//#include<dos.h>

typedef struct{
   char simbolo[6];
   char banDirs[13];
}TabOp;

TabOp mnems[208];

int busquedaBin(char *elem,int primero,int ultimo){
   int mitad;
   while(primero<=ultimo){
      mitad=(primero+ultimo)/2;
      if(strcmpi(elem,mnems[mitad].simbolo)==0)
	 return mitad;
      else
	 if(strcmpi(elem,mnems[mitad].simbolo)<0)
	    ultimo=mitad-1;
	 else
	    primero=mitad+1;
   }
   return -1;
}

void capturaTabOp(){
   FILE *fTabOp;
   char linea[22],c;
   int cont=0,i,j,ban;
   if((fTabOp=fopen("C:/TC/Prog/Prog_sis/TabOp.TXT","r+t"))==NULL){
      printf("\n\n\tError al abrir la tabla de codigos de operacion\n\t");
      getch();
   }else{
      while(fgets(linea,30,fTabOp)!=NULL){
	 i=0;j=0;ban=1;
	 c=linea[i];
	 while(c!='\n'){
	    if(c=='\t'){
	       ban++;
	       j=0;
	       i++;
	       c=linea[i];
	    }
	    switch(ban){
	       case 1:{mnems[cont].simbolo[j]=c;
		       j++;
		       mnems[cont].simbolo[j]='\0';
		      }break;
	       case 2:{mnems[cont].banDirs[j]=c;
		       j++;
		       mnems[cont].banDirs[j]='\0';
		      }break;
	    }
	    i++;
	    c=linea[i];
	 }
	 cont++;
      }
      fclose(fTabOp);
   }
}
int esDirectiva(char *comando){
   if(strcmpi("end",comando)==0)
      return 1;
   else
      if(strcmpi("equ",comando)==0)
	 return 1;
      else
	 return 0;
}

int tipoCodOp(char *cadena){
   int pos;
   pos=busquedaBin(cadena,0,207);
   if(pos==-1){
      if(esDirectiva(cadena)==1)
	 return(210);
      else
	 return(-1);
   }else
      return(pos);
}

void printModes(int posicion){
   if(mnems[posicion].banDirs[0]=='o')
      printf("%s",mnems[posicion].banDirs);
   else{
      if(mnems[posicion].banDirs[0]=='1')
	 printf("INH ");
      if(mnems[posicion].banDirs[1]=='1')
	 printf("DIR ");
      if(mnems[posicion].banDirs[2]=='1')
	 printf("EXT ");
      if(mnems[posicion].banDirs[3]=='1')
	 printf("IMM_8 ");
      if(mnems[posicion].banDirs[4]=='1')
	 printf("IMM_16 ");
      if(mnems[posicion].banDirs[5]=='1')
	 printf("REL_8 ");
      if(mnems[posicion].banDirs[6]=='1')
	 printf("REL_16 ");
      if(mnems[posicion].banDirs[7]=='1')
	 printf("IDX ");
      if(mnems[posicion].banDirs[8]=='1')
	 printf("IDX1 ");
      if(mnems[posicion].banDirs[9]=='1')
	 printf("IDX2 ");
      if(mnems[posicion].banDirs[10]=='1')
	 printf("[IDX2] ");
      if(mnems[posicion].banDirs[11]=='1')
	 printf("[D,IDX] ");
   }
}

int revOperando(char op[]){
   int modoDir=0,pos=0;
   if(op[pos]=='\0')
      return 0;//Direccionamiento inherente
   if(op[pos]=='#'){
      modoDir=10;//Direccionamiento inmediato
      pos++;
   }
   if(op[pos]=='%')
      modoDir+=1;//En binario
   else{
      if(op[pos]=='@')
	 modoDir+=2;//En octal
      else{
	 if(op[pos]=='$')
	    modoDir+=3;//En Hexadecimal
	 else
	    if(isdigit(op[pos])!=0)
	       modoDir+=4;//En decimal
	    else
	       modoDir=-1;
      }
   }
   return modoDir;
}
char rangoOp(int base,char *op){
   char *endptr;
   long numero=0;
   if(base>10){
      base-=10;
      op++;
   }
   switch(base){
	case 1:{op++;
		numero=strtol(op,&endptr,2);
		if(numero==0)
		   return 0;
	       }break;
	case 2:{op++;
		numero=strtol(op,&endptr,8);
		if(numero==0)
		   return 0;
	       }break;
	case 3:{op++;
		numero=strtol(op,&endptr,16);
		if(numero==0)
		   return 0;
	       }break;
	case 4:{numero=strtol(op,&endptr,10);
		if(numero==0)
		   return 0;
	       }break;
	default:printf("\n\tERROR: Base numerica desconocida");
   }
   op=NULL;
   //sigue revisar el rango del numero
   if(base==4){
      if(numero>=-128&&numero<=127)
	 return 1;
      else
	 if(numero>=-32,768&&numero<=32,767)
	    return 2;
	 else
	    return 0;
   }else{
      if(numero>=0&&numero<=255)
	 return 1;
      else
	 if(numero>=0&&numero<=65,535)
	    return 2;
	 else
	    return 0;
   }

}
void operandoMain(char strOper[],int arrPos){
   int special,modoDir;
   //modoDir:0=inherente,1=Directo,2=extendido,3=IMM_8,4=IMM_16
   char /*auxOp,*/rango,reject=1/*no se acepto el modo*/;
   special=revOperando(strOper);
   if(special==0)
      modoDir=0;
   else{
      if(special==-1)
	 printf("Operando invalido");
      else{
	 //strcpy(auxOp,strOper);
	 rango=rangoOp(special,/*auxOp*/strOper);
      }
      if(special!=-1&&rango!=0){
	 if(special<10){
	    if(rango==1)
	       modoDir=1;
	    else
	       modoDir=2;
	 }else{
	    if(rango==1)
	       modoDir=3;
	    else
	       modoDir=4;
	 }
      }else
	 printf("Operando fuera de rango permitido\n\t\t");
   }

   //Sigue revisar si el codOp acepta ese modo de direccionamiento
   switch(modoDir){
	case 0:{if(mnems[arrPos].banDirs[0]=='1'){
		   printf("Inherente");
		   reject=0;
		}
	       }break;
	case 1:{if(mnems[arrPos].banDirs[1]=='1'){
		   printf("Directo");
		   reject=0;
		}else
		   if(mnems[arrPos].banDirs[2]=='1'){
		      printf("Extendido");
		      reject=0;
		   }
	       }break;
	case 2:{if(mnems[arrPos].banDirs[2]=='1'){
		   printf("Extendido");
		   reject=0;
		}
	       }break;
	case 3:{if(mnems[arrPos].banDirs[3]=='1'){
		   printf("Inmediato_8");
		   reject=0;
		}else
		   if(mnems[arrPos].banDirs[4]=='1'){
		      printf("Inmediato_16");
		      reject=0;
		   }
	       }break;
	case 4:{if(mnems[arrPos].banDirs[4]=='1'){
		   printf("Inmediato_16");
		   reject=0;
		}
	       }break;
   }
   if((modoDir==1||modoDir==2)&&reject==1)
      if(mnems[arrPos].banDirs[5]=='1'){
	 printf("Relativo_8");
	 reject=0;
      }else
	 if(mnems[arrPos].banDirs[6]=='1'){
	    printf("Relativo_16");
	    reject=0;
	 }
   if(reject==1)
      printf("No aceptado por este Cod. de Operancion");

}
/*------------------------------M-A-I-N-------------------------------*/
void main(void){
 FILE *fPoint;
 char linea[51],ruta[50],c;
 char etiqueta[15],codOp[10],operando[20];
 int i=0,j=0,cLinea=1,codPos;
 int ban=1,banCom=0,check,direct;//banderas
 //i=contador de linea;           j=contador de elemento;
 //ban=seleccion de elemento;     cLinea=contador de linea;
 //banCom=bandera de comentario;  codPos=posision del codOp en el arreglo
 //check=ya se busco y encontro el codOp; direct=es una directiva
 clrscr();

 capturaTabOp();
 /*for(int a=0;a<208;a++){
    printf("\n\t%s\t%s",mnems[a].simbolo,mnems[a].banDirs);
    //delay(600);
 }*/
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
       i=0;
       ban=1;j=0;
       c=linea[i];
       codPos=-1;
       check=0;
       direct=-1;
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
       if(operando[0]=='\0'){
	  if(codOp[0]=='\0'){
	     strcpy(codOp,etiqueta);
	     etiqueta[0]='\0';
	  }else{
	     if((direct=strcmpi("org",etiqueta))==0||(codPos=busquedaBin(etiqueta,0,207))!=-1){
		check=1;
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

       if(check==0)
	  codPos=tipoCodOp(codOp);
       printf("\n\tModos: ");

       if(codPos==210||direct==0)
	  printf("Directiva");
       else
	  if(codPos==-1)
	     printf("Codigo invalido");
	  else
	     printModes(codPos);

       //llamada a las funciones de operando...
       fflush(stdin);
       if(codPos!=210&&direct!=0)
	  printf("\n\tDireccionamiento: ");

       if(codPos!=210&&direct!=0&&codPos!=-1)
	  operandoMain(operando,codPos);

       if(banCom==1){
	  printf("\n\t* La linea contiene un comentario *");
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