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
   int banDirs[12];
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
   char linea[22],c,auxCh[2];
   int cont=0,i,j,ban,aux;
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
	       case 2:{if(isdigit(c)==0)
			  aux=-1;
		       else{
			  auxCh[0]=c;
			  auxCh[1]='\0';
			  aux=atoi(auxCh);
		       }
		       mnems[cont].banDirs[j]=aux;
		       j++;
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
   if(strcmpi("org",comando)==0)
      return 1;
   if(strcmpi("end",comando)==0)
      return 1;
   if(strcmpi("equ",comando)==0)
      return 1;
   if(strcmpi("fcc",comando)==0)
      return 1;
   if(strcmpi("dc",comando)==0)
      return 1;
   if(strcmpi("dc.b",comando)==0)
      return 1;
   if(strcmpi("dc.w",comando)==0)
      return 1;
   if(strcmpi("dc.l",comando)==0)
      return 1;
   if(strcmpi("db",comando)==0)
      return 1;
   if(strcmpi("dw",comando)==0)
      return 1;
   if(strcmpi("ds",comando)==0)
      return 1;
   if(strcmpi("ds.b",comando)==0)
      return 1;
   if(strcmpi("ds.w",comando)==0)
      return 1;
   if(strcmpi("ds.l",comando)==0)
      return 1;
   if(strcmpi("rmb",comando)==0)
      return 1;
   if(strcmpi("rmw",comando)==0)
      return 1;
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
   if(mnems[posicion].banDirs[0]==-1)
      printf("Codigo de operacion omitido");
   else{
      if(mnems[posicion].banDirs[0]!=0)
	 printf("INH ");
      if(mnems[posicion].banDirs[1]!=0)
	 printf("DIR ");
      if(mnems[posicion].banDirs[2]!=0)
	 printf("EXT ");
      if(mnems[posicion].banDirs[3]!=0)
	 printf("IMM_8 ");
      if(mnems[posicion].banDirs[4]!=0)
	 printf("IMM_16 ");
      if(mnems[posicion].banDirs[5]!=0)
	 printf("REL_8 ");
      if(mnems[posicion].banDirs[6]!=0)
	 printf("REL_16 ");
      if(mnems[posicion].banDirs[7]!=0)
	 printf("IDX ");
      if(mnems[posicion].banDirs[8]!=0)
	 printf("IDX1 ");
      if(mnems[posicion].banDirs[9]!=0)
	 printf("IDX2 ");
      if(mnems[posicion].banDirs[10]!=0)
	 printf("[IDX2] ");
      if(mnems[posicion].banDirs[11]!=0)
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
	    if(isdigit(op[pos])!=0||op[pos]=='-')
	       modoDir+=4;//En decimal
	    else
	       modoDir=-1;
      }
   }
   return modoDir;
}
char rangoOp(int base,char *op){
   char *endptr,idxBan=0,dIdxBan=0;
   long numero=65539;

   if(strcmpi(op,"a")==0||strcmpi(op,"b")==0||strcmpi(op,"d")==0)
      return 1;

   if(base>10&&base<20){
      base-=10;
      op++;
   }else
      if(base>20&&base<30){
	 base-=20;
	 idxBan=1;
      }else{
	 if(base>30){
	    base-=30;
	    dIdxBan=1;
	 }
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
	//default:printf("\n\tERROR: Base numerica desconocida\n\t");
   }
   op=NULL;

   //sigue revisar el rango del numero
   if(idxBan==1){
      if((numero>=-16)&&(numero<=15))
	 return 2;
      else
	 if((numero>=-256)&&(numero<=255))
	    return 3;
	 else
	    if((numero>=-32768)&&(numero<=32767))
	       return 4;
	    else
	       return 0;
   }else{
      if(dIdxBan==1){
	 if(numero>=0&&numero<=65535)
	    return 5;
	 else
	    return 0;
      }else{
	 if(base==4){
	    if((numero>=-128)&&(numero<=127))
	       return 1;
	    else
	       if((numero>=-32768)&&(numero<=32767))
		  return 2;
	       else
		  return 0;
	 }else{
	    if(numero>=0&&numero<=255)
	       return 1;
	    else
	       if(numero>=0&&numero<=65535)
		  return 2;
	       else
		  return 0;
	 }
      }
   }
}
char str2idx(char rango,char *elem){
   int leng,cont=0;
   char aux[4];

   if(elem[0]=='-'||elem[0]=='+'){
      if(rango==2||rango==1){
	 elem++;
	 if(strcmpi(elem,"x")==0||strcmpi(elem,"y")==0||strcmpi(elem,"sp")==0)
	    return 1;
	 else
	    return 0;
      }else
	 return 0;
   }else{
      leng=strlen(elem);
      if(elem[leng-1]=='+'||elem[leng-1]=='-'){
	 if(rango==2||rango==1){
	    while(cont<leng-1){
	       aux[cont]=elem[cont];
	       cont++;
	    }

	    if(strcmpi(aux,"x")==0||strcmpi(aux,"y")==0||strcmpi(aux,"sp")==0)
	       return 1;
	    else
	       return 0;
	 }else
	    return 0;
      }else{
	 if(strcmpi(elem,"x")==0||strcmpi(elem,"y")==0||strcmpi(elem,"sp")==0||strcmpi(elem,"pc")==0)
	    return 1;
	 else
	    return 0;
      }
   }
}
int indexed(char str[]){
   char ban=0,cad2ban=0,aux[11],*cad1,*cad2,rank;
   int i=0,base;

   if(strchr(str,'[')!=NULL){
      if(strchr(str,']')==NULL)
	 return -1;
      do{
	 if(str[i+1]==']')
	    aux[i]='\0';
	 else
	    aux[i]=str[i+1];
	 i++;
      }while(str[i]!=']');
      ban=1;
   }else
      strcpy(aux,str);
   //Sigue partir en dos a aux
   cad1=strtok(aux,",");
   cad2=strtok(NULL,",");

   base=revOperando(cad1);
   /*if(base==-1)
      if(ban==0)
	 return -1;*/

   if(ban==0)
      base+=20;
   else
      base+=30;

   rank=rangoOp(base,cad1);
   if(rank==0)
      return -1;

   cad2ban=str2idx(rank,cad2);

   if(cad2ban==1){
      if(rank==2)
	 return 21;//idx
      if(rank==3)
	 return 22;//idx1
      if(rank==4)
	 return 23;//idx2
      if(rank==5)
	 return 24;//[idx2]
      if(rank==1){
	 if(ban==1){
	    if(strcmpi(cad1,"d")==0)
	       return 25;//[d,idx]
	    else
	       return -1;
	 }else
	    return 26;//idx de acumulador
      }
   }else
      return -1;
   return -1;
}
void operandoMain(char strOper[],int arrPos){
   int special,modoDir,posDir;
   //modoDir:0=inherente,1=Directo,2=extendido,3=IMM_8,4=IMM_16
   //        5=IDX,6=IDX1,7=IDX2,8=[idx2],9=[d,idx]

   char errBan=0,rango=0,reject=1/*no se acepto el modo*/;

   //Revisa si en la cadena hay una coma:
   if(strchr(strOper,',')!=NULL){
      special=indexed(strOper);
   }else
      special=revOperando(strOper);

   if(special==0)
      modoDir=0;
   else{
      if(special==-1){
	 printf("Operando invalido\t");
	 errBan=1;
      }else{
	 if(special<20)
	    rango=rangoOp(special,strOper);
      }
      if(rango==0){
	 if(special==21)
	    modoDir=5;//idx
	 else
	    if(special==22)
	       modoDir=6;//idx1
	    else
	       if(special==23)
		  modoDir=7;//idx2
	       else
		  if(special==24)
		     modoDir=8;//[idx2]
		  else
		     if(special==25)
			modoDir=9;//[d,idx2]
		     else
			if(special==26)
			   modoDir=10;//idx acumulador
      }else{
	 if(special<10){
	    if(rango==1)
	       modoDir=1;
	    else
	       modoDir=2;
	 }else{
	    if(special<20){
	       if(rango==1)
		  modoDir=3;
	       else
		  modoDir=4;
	    }
	 }
      }
   }

   //Sigue revisar si el codOp acepta ese modo de direccionamiento
   switch(modoDir){
	case 0:{if(mnems[arrPos].banDirs[0]!=0){
		   printf("Inherente");
		   posDir=0;
		   reject=0;
		}
	       }break;
	case 1:{if(mnems[arrPos].banDirs[1]!=0){
		   printf("Directo");
		   posDir=1;
		   reject=0;
		}else
		   if(mnems[arrPos].banDirs[2]!=0){
		      printf("Extendido");
		      posDir=2;
		      reject=0;
		   }
	       }break;
	case 2:{if(mnems[arrPos].banDirs[2]!=0){
		   printf("Extendido");
		   posDir=2;
		   reject=0;
		}
	       }break;
	case 3:{if(mnems[arrPos].banDirs[3]!=0){
		   printf("Inmediato_8");
		   posDir=3;
		   reject=0;
		}else
		   if(mnems[arrPos].banDirs[4]!=0){
		      printf("Inmediato_16");
		      posDir=4;
		      reject=0;
		   }
	       }break;
	case 4:{if(mnems[arrPos].banDirs[4]!=0){
		   printf("Inmediato_16");
		   posDir=4;
		   reject=0;
		}
	       }break;
	case 5:{if(mnems[arrPos].banDirs[7]!=0){
		   printf("IDX");
		   posDir=7;
		   reject=0;
		}
	       }break;
	case 6:{if(mnems[arrPos].banDirs[8]!=0){
		   printf("IDX1");
		   posDir=8;
		   reject=0;
		}
	       }break;
	case 7:{if(mnems[arrPos].banDirs[9]!=0){
		   printf("IDX2");
		   posDir=9;
		   reject=0;
		}
	       }break;
	case 8:{if(mnems[arrPos].banDirs[10]!=0){
		   printf("[IDX2]");
		   posDir=10;
		   reject=0;
		}
	       }break;
	case 9:{if(mnems[arrPos].banDirs[11]!=0){
		   printf("[D,IDX]");
		   posDir=11;
		   reject=0;
		}
	       }break;
	case 10:{if(mnems[arrPos].banDirs[7]!=0){
		   printf("IDX de acumulador");
		   posDir=7;
		   reject=0;
		}
	       }break;
   }
   if((modoDir==1||modoDir==2)&&reject==1)
      if(mnems[arrPos].banDirs[5]!=0){
	 printf("Relativo_8");
	 posDir=5;
	 reject=0;
      }else
	 if(mnems[arrPos].banDirs[6]!=0){
	    printf("Relativo_16");
	    posDir=6;
	    reject=0;
	 }
   if(reject==1){
      if(errBan==0)
	 printf("No aceptado por este Cod. de Operancion");
   }else
      printf("\n\tLongitud: %d",mnems[arrPos].banDirs[posDir]);
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
    printf("\n\t%s\t",mnems[a].simbolo);
    printf("%d",mnems[a].banDirs[0]);
    printf("%d",mnems[a].banDirs[1]);
    printf("%d",mnems[a].banDirs[2]);
    printf("%d",mnems[a].banDirs[3]);
    printf("%d",mnems[a].banDirs[4]);
    printf("%d",mnems[a].banDirs[5]);
    printf("%d",mnems[a].banDirs[6]);
    printf("%d",mnems[a].banDirs[7]);
    printf("%d",mnems[a].banDirs[8]);
    printf("%d",mnems[a].banDirs[9]);
    printf("%d",mnems[a].banDirs[10]);
    printf("%d",mnems[a].banDirs[11]);
    delay(300);
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
	     if((direct=esDirectiva(etiqueta))==1||(codPos=busquedaBin(etiqueta,0,207))!=-1){
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

       /*printf("\n\tModos: ");
       if(codPos==210||direct==1)
	  printf("Directiva");
       else
	  if(codPos==-1)
	     printf("Codigo invalido");
	  else
	     printModes(codPos);*/

       //llamada a las funciones de operando...
       fflush(stdin);
       if(codPos!=210&&direct!=1)
	  printf("\n\tDireccionamiento: ");

       if(codPos!=210&&direct!=1&&codPos!=-1)
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