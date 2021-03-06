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

typedef struct{
   char simbolo[6];
   int banDirs[12];
}TabOp;
typedef struct{
   char etiqueta[8];
   long valor;
}tbs;

TabOp mnems[208];
tbs tabSim[12];
int cLinea=1;

FILE *fRRR;
char errBan,*ruta4=NULL;//para el archivo de errores

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
   if((fTabOp=fopen("C:/TC30/bin/cfcu/TabOp.TXT","r+t"))==NULL){
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
long rangoOp(int base,char *op){
   char *endptr,idxBan=0,dIdxBan=0,dirva=0;
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
	 if(base>30&&base<40){
	    base-=30;
	    dIdxBan=1;
	 }else
	    if(base>40&&base<50){
	       base-=40;
	       dirva=1;
	    }else
	       if(base>50&&base<60){
		  base-=50;
		  dirva=2;
	       }else
		  if(base>60){
		     base-=60;
		     dirva=3;
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
	/*default:{fRRR=fopen(ruta4,"a+t");
		 fprintf(fRRR,"%02d\tBase numerica desconocida\n",cLinea);
		 fclose(fRRR);
		 errBan=1;
		}*/
   }
   op=NULL;

   //sigue revisar el rango del numero
   if(dirva==3){
      if((numero>=0)&&(numero<=0xFFFF))
	 return numero;
      else
	 return -1;
   }

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
	    return -1;
      }else{
	 if(dirva==1){
	    if(numero>=0&&numero<=255)
	       return 1;
	    else
	       if(numero>=0&&numero<=65535)
		  return 2;
	       else
		  if(numero>=0&&numero<=0xFFFFFFFF)
		     return 3;
		  else
		     return -1;
	 }else{
	    if(dirva==2){
	       if(numero>=1&&numero<=4096)
		  return numero;
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
			return -1;
	       }
	    }
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
   char ban=0,cad2ban=0,aux[17],*cad1,*cad2,rank;
   int i=0,base;

   if(strchr(str,'[')!=NULL){
      if(strchr(str,']')==NULL){
	 fRRR=fopen(ruta4,"a+t");
	 fprintf(fRRR,"%02d\tFalto cierre de corchetes\n",cLinea);
	 fclose(fRRR);
	 errBan=1;
	 return -1;
      }
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
int operandoMain(char strOper[],int arrPos){
   int special,modoDir,posDir,length=0;
   //modoDir:0=inherente,1=Directo,2=extendido,3=IMM_8,4=IMM_16
   //        5=IDX,6=IDX1,7=IDX2,8=[idx2],9=[d,idx]

   char errBn=0,rango=0,reject=1/*no se acepto el modo*/;

   //Revisa si en la cadena hay una coma:
   if(strchr(strOper,',')!=NULL){
      special=indexed(strOper);
   }else
      special=revOperando(strOper);

   if(special==0)
      modoDir=0;
   else{
      if(special==-1){
	 if(errBan==0){
	    fRRR=fopen(ruta4,"a+t");
	    fprintf(fRRR,"%02d\tOperando invalido\n",cLinea);
	    fclose(fRRR);
	    errBan=1;
	 }
	 errBn=1;
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
		   //printf("Inherente");
		   posDir=0;
		   reject=0;
		}
	       }break;
	case 1:{if(mnems[arrPos].banDirs[1]!=0){
		   //printf("Directo");
		   posDir=1;
		   reject=0;
		}else
		   if(mnems[arrPos].banDirs[2]!=0){
		      //printf("Extendido");
		      posDir=2;
		      reject=0;
		   }
	       }break;
	case 2:{if(mnems[arrPos].banDirs[2]!=0){
		   //printf("Extendido");
		   posDir=2;
		   reject=0;
		}
	       }break;
	case 3:{if(mnems[arrPos].banDirs[3]!=0){
		   //printf("Inmediato_8");
		   posDir=3;
		   reject=0;
		}else
		   if(mnems[arrPos].banDirs[4]!=0){
		      //printf("Inmediato_16");
		      posDir=4;
		      reject=0;
		   }
	       }break;
	case 4:{if(mnems[arrPos].banDirs[4]!=0){
		   //printf("Inmediato_16");
		   posDir=4;
		   reject=0;
		}
	       }break;
	case 5:{if(mnems[arrPos].banDirs[7]!=0){
		   //printf("IDX");
		   posDir=7;
		   reject=0;
		}
	       }break;
	case 6:{if(mnems[arrPos].banDirs[8]!=0){
		   //printf("IDX1");
		   posDir=8;
		   reject=0;
		}
	       }break;
	case 7:{if(mnems[arrPos].banDirs[9]!=0){
		   //printf("IDX2");
		   posDir=9;
		   reject=0;
		}
	       }break;
	case 8:{if(mnems[arrPos].banDirs[10]!=0){
		   //printf("[IDX2]");
		   posDir=10;
		   reject=0;
		}
	       }break;
	case 9:{if(mnems[arrPos].banDirs[11]!=0){
		   //printf("[D,IDX]");
		   posDir=11;
		   reject=0;
		}
	       }break;
	case 10:{if(mnems[arrPos].banDirs[7]!=0){
		   //printf("IDX de acumulador");
		   posDir=7;
		   reject=0;
		}
	       }break;
   }
   if((modoDir==1||modoDir==2)&&reject==1)
      if(mnems[arrPos].banDirs[5]!=0){
	 //printf("Relativo_8");
	 posDir=5;
	 reject=0;
      }else
	 if(mnems[arrPos].banDirs[6]!=0){
	    //printf("Relativo_16");
	    posDir=6;
	    reject=0;
	 }
   if(reject==1){
      if(errBn==0){
	 fRRR=fopen(ruta4,"a+t");
	 fprintf(fRRR,"%02d\tOperando no aceptado por este Cod. de Operancion\n",cLinea);
	 fclose(fRRR);
	 errBan=1;
      }
      return 0;
   }else{
      length=mnems[arrPos].banDirs[posDir];
      return length;
   }
}
int directivas(char *dva,char *op){
   int leng,base,rango;
   if(strcmpi(dva,"org")!=0)
   if(strcmpi(dva,"fcc")==0){
      leng=strlen(op);
      //printf("%d",leng-2);
      return leng-2;
   }else{
      base=revOperando(op);
      if(strcmpi(dva,"ds")==0||strcmpi(dva,"ds.b")==0||strcmpi(dva,"rmb")==0||strcmpi(dva,"ds.w")==0||strcmpi(dva,"rmw")==0||strcmpi(dva,"ds.l")==0){
	 base+=50;
	 rango=rangoOp(base,op);
	 if(rango==0){
	    fRRR=fopen(ruta4,"a+t");
	    fprintf(fRRR,"%02d\tOperando fuera de rango\n",cLinea);
	    fclose(fRRR);
	    errBan=1;
	    return 0;
	 }else{
	    if(strcmpi(dva,"ds")==0||strcmpi(dva,"ds.b")==0||strcmpi(dva,"rmb")==0){
	       //printf("%d",rango);
	       return rango;
	    }else
	       if(strcmpi(dva,"ds.w")==0||strcmpi(dva,"rmw")==0){
		  //printf("%d",rango*2);
		  return rango*2;
	       }else
		  if(strcmpi(dva,"ds.l")==0){
		     //printf("%d",rango*4);
		     return rango*4;
		  }
	 }
      }else{
	 base+=40;
	 rango=rangoOp(base,op);
	 if(strcmpi(dva,"dc")==0||strcmpi(dva,"dc.b")==0||strcmpi(dva,"db")==0){
	    if(rango==1){
	       //printf("1");
	       return 1;
	    }else{
	       fRRR=fopen(ruta4,"a+t");
	       fprintf(fRRR,"%02d\tOperando fuera de rango\n",cLinea);
	       fclose(fRRR);
	       errBan=1;
	       return 0;
	    }
	 }else{
	    if(strcmpi(dva,"dc.w")==0||strcmpi(dva,"dw")==0){
	       if(rango<=2){
		  //printf("2");
		  return 2;
	       }else{
		  fRRR=fopen(ruta4,"a+t");
		  fprintf(fRRR,"%02d\tOperando fuera de rango\n",cLinea);
		  fclose(fRRR);
		  errBan=1;
		  return 0;
	       }
	    }else{
	       if(strcmpi(dva,"dc.l")==0){
		  if(rango<=3){
		     //printf("4");
		     return 4;
		  }else{
		     fRRR=fopen(ruta4,"a+t");
		     fprintf(fRRR,"%02d\tOperando fuera de rango\n",cLinea);
		     fclose(fRRR);
		     errBan=1;
		     return 0;
		  }
	       }
	    }
	 }
      }
   }
   return 0;
}
void etiquetas(char *et,char *mnem,char *op,unsigned int cLoc,int &cont){
   long num;
   int base;
   char esta=0;

   for(int i=0;i<=cont;i++){
      if(strcmpi(et,tabSim[i].etiqueta)==0)
	 esta=1;
   }
   if(esta==1){
      fRRR=fopen(ruta4,"a+t");
      fprintf(fRRR,"%02d\tEtiqueta ya declarada\n",cLinea);
      fclose(fRRR);
      errBan=1;
   }else{
      strcpy(tabSim[cont].etiqueta,et);
      if(strcmpi(mnem,"equ")==0){
	 base=revOperando(op);
	 base+=60;
	 num=rangoOp(base,op);
	 tabSim[cont].valor=num;
      }else
	 tabSim[cont].valor=cLoc;
      cont++;
   }
}
/*--------------------------------M-A-I-N---------------------------------*/
void main(void){
 FILE *fPoint,*fLST,*fTBS;
 char linea[51],ruta[50],*ruta1,*ruta2,*ruta3,c;
 char etiqueta[17],codOp[17],operando[19];
 unsigned int contloc=0,codLong=0;
 int i,j,codPos,etC=0;
 int ban=1,/*banCom=0,*/check,direct,comillas,endBan=0,nada;//banderas
 //i=contador de linea;               j=contador de elemento;
 //ban=seleccion de elemento;         cLinea=contador de linea (global);
 //banCom=bandera de comentario;      codPos=posision del codOp en el arreglo
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
	//delay(300);
 }*/
 printf("\n\n\tEscribe la ruta y el nombre del archivo a abrir (sin extension):\n\t");
 scanf("%s",&ruta);
 fflush(stdin);

 strcpy(ruta2,ruta);
 strcat(ruta2,".lst");
 strcpy(ruta3,ruta);
 strcat(ruta3,".tbs");
 strcpy(ruta4,ruta);
 strcat(ruta4,".rrr");

 strcpy(ruta1,ruta);
 strcat(ruta1,".asm");
 if((fPoint=fopen(ruta1,"rt"))==NULL){
    printf("\n\n\tError al abrir el archivo .ASM\n\t");
 }else{
    if((fLST=fopen(ruta2,"wt"))==0)
       printf("\n\tError al crear el archivo .LST\n\t");
    else{
       fprintf(fLST,"ENSAMBLADOR Beta 0.4.3\n");
       fprintf(fLST,"Creado por: Carlos Fco. Camacho Uribe\n");
       fprintf(fLST,"Codigo: 398251049\n");
       fprintf(fLST,"Ingenieria en Computacion, CUCEI UdeG\n\n\n");
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
	  comillas=0;
	  errBan=0;
	  nada=0;
	  while(c!='\n'&&c!='\0'){
	     if(c==';'){
		//banCom=1;
		break;
	     }
	     if(c=='"'){
		if(comillas==1)
		   comillas=0;
		else
		   comillas=1;
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
		       }else
			  if(comillas==1){
			     codOp[j]=c;
			     j++;
			     codOp[j]='\0';
			  }
		      }break;
	       case 3:{if(c!=' '&&c!='\t'){
			  operando[j]=c;
			  j++;
			  operando[j]='\0';
		       }else
			  if(comillas==1){
			     codOp[j]=c;
			     j++;
			     codOp[j]='\0';
			  }
		      }break;
	       default:printf("\n\n\tError en la clasificacion de la linea\n\t");
	     }
	     if(c==' '||c=='\t')
		if(j!=0){
		   if(comillas!=1){
		      ban++;
		      if(ban==4)
			 ban=1;
		      j=0;
		   }
		}
	     i++;
	     c=linea[i];
	  }
	  if(operando[0]=='\0'){
	     if(codOp[0]=='\0'){
		if(etiqueta[0]=='\0')
		   nada=1;
		else{
		   strcpy(codOp,etiqueta);
		   etiqueta[0]='\0';
		}
	     }else{
		if((direct=esDirectiva(etiqueta))==1||(codPos=busquedaBin(etiqueta,0,207))!=-1){
		   check=1;
		   strcpy(operando,codOp);
		   strcpy(codOp,etiqueta);
		   etiqueta[0]='\0';
		}
	     }
	  }
	  if(check==0&&nada!=1)
	     codPos=tipoCodOp(codOp);

	  if(strcmpi(codOp,"org")==0){
	     int base;
	     long num;
	     base=revOperando(operando);
	     base+=60;
	     num=rangoOp(base,operando);
	     if(num==-1){
		fRRR=fopen(ruta4,"a+t");
		fprintf(fRRR,"%02d\tOperando invalido\n",cLinea);
		fclose(fRRR);
		errBan=1;
	     }else
		contloc=num;
	  }
	  if(strcmpi(codOp,"end")==0)
	     endBan=1;
	  else
	     if(endBan==1){
		endBan=0;
		fRRR=fopen(ruta4,"a+t");
		fprintf(fRRR,"%02d\tCualquier instruccion invalida despues de un END\n",cLinea);
		fclose(fRRR);
		errBan=1;
	     }

	  if(etiqueta[0]!='\0'){
	     if(endBan==1){
		fRRR=fopen(ruta4,"a+t");
		fprintf(fRRR,"%02d\tNo debe haber ninguna etiqueta definida para la directiva END\n",cLinea);
		fclose(fRRR);
		errBan=1;
	     }else
		etiquetas(etiqueta,codOp,operando,contloc,etC);
	  }

	  if(direct==1)
	     codLong=directivas(codOp,operando);


	  if(strcmpi(codOp,"equ")==0)
	     if(etiqueta[0]=='\0'){
		fRRR=fopen(ruta4,"a+t");
		fprintf(fRRR,"%02d\tDebe haber una etiqueta definida para la directiva EQU\n",cLinea);
		fclose(fRRR);
		errBan=1;
	     }
	  if(direct!=1)
	     if(codPos==-1&&nada!=1){
		fRRR=fopen(ruta4,"a+t");
		fprintf(fRRR,"%02d\tCodigo desconocido\n",cLinea);
		fclose(fRRR);
		errBan=1;
	     }

	  if(comillas==1){
	     fRRR=fopen(ruta4,"a+t");
	     fprintf(fRRR,"%02d\tFalto cierre de comillas en el operando\n",cLinea);
	     fclose(fRRR);
	     errBan=1;
	  }
	  //llamada a las funciones de operando...
	  //fflush(stdin);
	  /*if(codPos!=210&&direct!=1)
	     printf("\n\tDireccionamiento: ");*/

	  if(codPos!=210&&direct!=1&&codPos!=-1)
	     codLong=operandoMain(operando,codPos);

	  /*if(banCom==1){
	     printf("\n\t* La linea contiene un comentario *");
	     banCom=0;
	  }*/
	  fprintf(fLST,"%02d\t",cLinea);
	  if(nada!=1){
	     if(strcmpi(codOp,"equ")==0)
		fprintf(fLST,"%04X",tabSim[etC-1].valor);
	     else
		fprintf(fLST,"%04X",contloc);
	     fprintf(fLST,"\t%s",etiqueta);
	     fprintf(fLST,"\t%s",codOp);
	     fprintf(fLST,"\t%s\n",operando);
	     if(errBan==1)
		fprintf(fLST,"   ***** ERROR *****\n");
	  }else
	     fprintf(fLST,"\n");

	  contloc+=codLong;
	  cLinea++;
       }
       fclose(fLST);
    }
    fclose(fPoint);
    printf("\n\n\t���Archivo leido con exito!!!\n\n\t");

    if(errBan==1)
       printf("Se encontraron errores en el archivo\n\n\t");

    if((fTBS=fopen(ruta3,"wt"))==0)
       printf("\n\tError al crear el archivo .TBS\n\t");
    else{
       fprintf(fTBS,"SIMBOLO\tVALOR");
       for(int i=0;i<etC;i++){
	  fprintf(fTBS,"\n%s",tabSim[i].etiqueta);
	  fprintf(fTBS,"\t%04X",tabSim[i].valor);
       }
       fclose(fTBS);
    }
 }
 printf("\n\tPresiona cualquier tecla para salir del programa");
 getch();
}