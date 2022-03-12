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
   char codMaq[8][5];
}TabOp;
typedef struct{
   char etiqueta[8];
   long valor;
}tbs;
typedef struct{
   unsigned int cLoc;
   char etiq[8];
   char cod[6];
   char oper[26];
   int errors,pcm0,pcm1;
}arrCods;
typedef struct{
   char tipo[3],dirIni[5];
   unsigned char longitud;
   char codigo[36],chksum[3];
}s19;

TabOp mnems[208];
tbs tabSim[12];
arrCods codigoAll[50];
s19 arrS19[6];

int cLinea=1,posCodMq[2]={0,0};
long operG=0;
char idxPrePos,idxAcum=0,rr[4],pasos=1,s19c=0;

FILE *fRRR;
char errBan=0,errAux=0,*ruta4=NULL;//para el archivo de errores

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
   char linea[40],c,auxCh[2];
   int cont=0,i,j,k,ban,aux;
   if((fTabOp=fopen("C:/TC/Prog/Prog_sis/TabOp2.TXT","rt"))==NULL){
      printf("\n\n\tError al abrir la tabla de codigos de operacion\n\t");
      getch();
   }else{
      while(fgets(linea,40,fTabOp)!=NULL){
	 i=0;j=0;k=0;ban=1;
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
	       case 3:{if(c==','){
			  mnems[cont].codMaq[j][k]='\0';
			  j++;
			  k=0;
		       }else{
			  mnems[cont].codMaq[j][k]=c;
			  k++;
		       }
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
      return 2;
   if(strcmpi("equ",comando)==0)
      return 3;
   if(strcmpi("fcc",comando)==0)
      return 4;
   if(strcmpi("dc",comando)==0)
      return 5;
   if(strcmpi("dc.b",comando)==0)
      return 6;
   if(strcmpi("dc.w",comando)==0)
      return 7;
   if(strcmpi("dc.l",comando)==0)
      return 8;
   if(strcmpi("db",comando)==0)
      return 9;
   if(strcmpi("dw",comando)==0)
      return 10;
   if(strcmpi("ds",comando)==0)
      return 11;
   if(strcmpi("ds.b",comando)==0)
      return 12;
   if(strcmpi("ds.w",comando)==0)
      return 13;
   if(strcmpi("ds.l",comando)==0)
      return 14;
   if(strcmpi("rmb",comando)==0)
      return 15;
   if(strcmpi("rmw",comando)==0)
      return 16;
   return 0;
}
int tipoCodOp(char *cadena){
   int pos;
   pos=busquedaBin(cadena,0,207);
   if(pos==-1){
      if(esDirectiva(cadena)>0)
	 return(210);
      else
	 return(-1);
   }else
      return(pos);
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
	 else{
	    //if(isdigit(op[pos])!=0||op[pos]=='-')
	       modoDir+=4;//En decimal
	    /*else
	       modoDir=-1;*/
	 }
      }
   }
   return modoDir;
}
char buscaEt(char *symbol){
   for(int i=0;i<12;i++)
      if(strcmp(symbol,tabSim[i].etiqueta)==0)
	 return i;
   return -1;
}
long rangoOp(int base,char *op){
   char *endptr,idxBan=0,dIdxBan=0,dirva=0;
   long numero=65539;

   if(strcmpi(op,"a")==0){
      idxAcum=1;
      return 1;
   }else
      if(strcmpi(op,"b")==0){
	 idxAcum=2;
	 return 1;
      }else
	 if(strcmpi(op,"d")==0){
	    idxAcum=3;
	    return 1;
	 }

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
		//if(numero==0&&(strcmpi(op,"0")!=0/*||strcmpi(op,"")!=0*/))
		//   return 0;
	       }break;
	case 2:{op++;
		numero=strtol(op,&endptr,8);
		//if(numero==0)
		//   return 0;
	       }break;
	case 3:{op++;
		numero=strtol(op,&endptr,16);
		//if(numero==0)
		//   return 0;
	       }break;
	case 4:{int n=buscaEt(op);
		if(n>=0)
		   numero=tabSim[n].valor;
		else{
		   if(isdigit(op[0])!=0||op[0]=='-')
		      numero=strtol(op,&endptr,10);
		   else{
		      if(pasos==2){
			 codigoAll[cLinea].errors++;
			 fRRR=fopen(ruta4,"a+t");
			 fprintf(fRRR,"%02d\tSimbolo no declarado\n",cLinea);
			 fclose(fRRR);
			 errBan++;
		      }
		   }
		}
	       }break;
	/*default:{fRRR=fopen(ruta4,"a+t");
		 fprintf(fRRR,"%02d\tBase numerica desconocida\n",cLinea);
		 fclose(fRRR);
		 errBan++;
		}*/
   }
   op=NULL;
   operG=numero;
   //sigue revisar el rango del numero
   if(dirva==3){
      if((numero>=0&&numero<=0xFFFF)||pasos==1)
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
	    if((numero>=-32768&&numero<=32767)||pasos==1)
	       return 4;
	    else
	       return 0;
   }else{
      if(dIdxBan==1){
	 if((numero>=0&&numero<=65535)||pasos==1)
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
		  if((numero>=0&&numero<=0xFFFFFFFF)||pasos==1)
		     return 3;
		  else
		     return -1;
	 }else{
	    if(dirva==2){
	       if((numero>=1&&numero<=4096)||pasos==1)
		  return numero;
	       else
		  return 0;
	    }else{
	       if(base==4){
		  if((numero>=-128)&&(numero<=127))
		     return 1;
		  else
		     if((numero>=-32768&&numero<=32767)||pasos==1)
			return 2;
		     else
			return 0;
	       }else{
		  if(numero>=0&&numero<=255)
		     return 1;
		  else
		     if((numero>=0&&numero<=65535)||pasos==1)
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
      if(elem[0]=='+')
	 idxPrePos=1;//pre+
      else
	 if(elem[0]=='-')
	    idxPrePos=2;//pre-
      if(rango==2||rango==1){
	 elem++;
	 if(strcmpi(elem,"x")==0||strcmpi(elem,"y")==0||strcmpi(elem,"sp")==0){
	    return 1;
	 }else
	    return 0;
      }else
	 return 0;
   }else{
      leng=strlen(elem);
      if(elem[leng-1]=='+'||elem[leng-1]=='-'){
	 if(elem[leng-1]=='+')
	    idxPrePos=3;//pos+
	 else
	    if(elem[leng-1]=='-')
	       idxPrePos=4;//pos-
	 if(rango==2||rango==1){
	    while(cont<leng-1){
	       aux[cont]=elem[cont];
	       cont++;
	    }
	    if(strcmpi(aux,"x")==0||strcmpi(aux,"y")==0||strcmpi(aux,"sp")==0){
	       return 1;
	    }else
	       return 0;
	 }else
	    return 0;
      }else{
	 if(strcmpi(elem,"x")==0||strcmpi(elem,"y")==0||strcmpi(elem,"sp")==0||strcmpi(elem,"pc")==0){
	    idxPrePos=0;//sin signo
	    return 1;
	 }else
	    return 0;
      }
   }
}
int indexed(char str[]){
   char ban=0,cad2ban=0,aux[28],*cad1,*cad2,rank;
   int i=0,base;

   if(strchr(str,'[')!=NULL){
      if(strchr(str,']')==NULL){
	 fRRR=fopen(ruta4,"a+t");
	 fprintf(fRRR,"%02d\tFalto cierre de corchetes\n",cLinea);
	 fclose(fRRR);
	 errBan++;
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
   if(str[0]!=','){
      cad1=strtok(aux,",");
      cad2=strtok(NULL,",");
   }else{
      cad1="0";
      i=0;
      while(aux[i]!='\0'){
	 i++;
	 cad2[i-1]=aux[i];
      }
   }

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
   strcpy(rr,cad2);

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
	 if(errBan==errAux){
	    fRRR=fopen(ruta4,"a+t");
	    fprintf(fRRR,"%02d\tOperando invalido\n",cLinea);
	    fclose(fRRR);
	    errBan++;
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
	 errBan++;
      }
      return 0;
   }else{
      length=mnems[arrPos].banDirs[posDir];
      if(pasos==1){
	 posCodMq[0]=arrPos;
	 posCodMq[1]=posDir;
      }
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
	    errBan++;
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
	       errBan++;
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
		  errBan++;
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
		     errBan++;
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
      errBan++;
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

//************** Funciones para el archivo s19 **************
void calculaCHKSM(int pos){
   //En esta funcion tambien se calcula el campo longitud.
   int aux=0,chk=0;
   char dirH[3],dirL[3],cod[3],strAux[6],*endptr,codLen;

   dirH[0]=arrS19[pos].dirIni[0];
   dirH[1]=arrS19[pos].dirIni[1];
   dirH[2]='\0';
   dirL[0]=arrS19[pos].dirIni[2];
   dirL[1]=arrS19[pos].dirIni[3];
   dirL[2]='\0';

   if(strcmp(arrS19[pos].tipo,"s1")!=0){
      arrS19[pos].longitud=strlen(arrS19[pos].codigo)+3;
      for(int i=0;i<strlen(arrS19[pos].codigo);i++){
	 aux+=arrS19[pos].codigo[i];
      }
   }else{
      arrS19[pos].longitud=(strlen(arrS19[pos].codigo)/2)+3;
      for(int i=0;i<strlen(arrS19[pos].codigo);i+=2){
	 cod[0]=arrS19[pos].codigo[i];
	 cod[1]=arrS19[pos].codigo[i+1];
	 cod[2]='\0';
	 aux+=strtol(cod,&endptr,16);
      }
   }

   aux+=arrS19[pos].longitud;
   aux+=strtol(dirH,&endptr,16);
   aux+=strtol(dirL,&endptr,16);

   chk=0xFFFF-aux;
   itoa(chk,strAux,16);
   codLen=strlen(strAux);

   arrS19[pos].chksum[0]=toupper(strAux[codLen-2]);
   arrS19[pos].chksum[1]=toupper(strAux[codLen-1]);
}
void imprimeS19(FILE *ps19){
   for(int i=0;i<s19c;i++){
      fprintf(ps19,"%s ",arrS19[i].tipo);
      fprintf(ps19,"%02X ",arrS19[i].longitud);
      fprintf(ps19,"%s ",arrS19[i].dirIni);
      if(strcmp(arrS19[i].tipo,"s1")==0)
	 fprintf(ps19,"%s",arrS19[i].codigo);
      else
	 for(int j=0;j<strlen(arrS19[i].codigo);j++)
	    fprintf(ps19,"%02X",arrS19[i].codigo[j]);

      fprintf(ps19," %s\n",arrS19[i].chksum);
   }
}
void appendS1(char cod[],char tipo){
   //Tipo: 1=cod del mnemonico,2=cod del operando,3=cod de directiva
   char longAux,longAux2;
   longAux=strlen(arrS19[s19c].codigo)+strlen(cod);
   if(longAux>32){//se paso del rango de los 16 bytes (2 caracteres por byte)
      longAux2=strlen(cod);
      if(longAux-longAux2==32){//se pasa el codigo completo a otro s1
      }
   }else
      strcat(arrS19[s19c].codigo,cod);
}
//************** Fin de funciones para el s19 **************

void printCodMaq(FILE *lst,int pos,long rel){
   int leng,aux;
   char s1aux[7];
   s1aux[0]='\0';
   if(pos!=0){//No es inherente
      if(pos!=7){//No es indexado
	 if(pos==5||pos==6){//Relativos
	    long resta=operG-rel;
	    if(pos==5){
	       if(resta<0||resta>255){
		  char cod[8],codLen;
		  ltoa(resta,cod,16);
		  codLen=strlen(cod);
		  cod[codLen-2]=toupper(cod[codLen-2]);
		  cod[codLen-1]=toupper(cod[codLen-1]);
		  fprintf(lst,"%c%c",cod[codLen-2],cod[codLen-1]);

		  //a continuacion escribe en el arreglo s19
		  sprintf(s1aux,"%c%c",cod[codLen-2],cod[codLen-1]);
		  appendS1(s1aux,2);
	       }else{
		  fprintf(lst,"%02X",resta);
		  //a continuacion escribe en el arreglo s19
		  sprintf(s1aux,"%02X",resta);
		  appendS1(s1aux,2);
	       }
	    }else{
	       fprintf(lst,"%04X",resta);
	       //a continuacion escribe en el arreglo s19
	       sprintf(s1aux,"%04X",resta);
	       appendS1(s1aux,2);
	    }
	 }else{
	    aux=strlen(mnems[posCodMq[0]].codMaq[pos])/2;
	    leng=(mnems[posCodMq[0]].banDirs[posCodMq[1]])-aux;
	    if(leng==1){
	       fprintf(lst,"%02X",operG);
	       //a continuacion escribe en el arreglo s19
	       sprintf(s1aux,"%02X",operG);
	       appendS1(s1aux,2);
	    }else
	       if(leng==2){
		  fprintf(lst,"%04X",operG);
		  //a continuacion escribe en el arreglo s19
		  sprintf(s1aux,"%04X",operG);
		  appendS1(s1aux,2);
	       }else
		  if(leng==3){
		     fprintf(lst,"%06X",operG);
		     //a continuacion escribe en el arreglo s19
		     sprintf(s1aux,"%06X",operG);
		     appendS1(s1aux,2);
		  }
	 }
      }else{//Indexados
	 char xb[9]="00000000",*endptr;
	 long xbInt;
	 switch(posCodMq[1]){
	      case 7:{//IDX
		      char rr1,rr2;
		      char binario[30],i;
		      if(idxAcum>0){
			 strcpy(xb,"11100100");
			 rr1=3;rr2=4;
			 if(idxAcum==2){
			    xb[7]='1';
			 }else
			    if(idxAcum==3){
			       xb[6]='1';
			    }
			 idxAcum=0;
		      }else{
			 rr1=0;rr2=1;
			 if(idxPrePos==0){//sin signo
			    ltoa(operG,binario,2);
			    strrev(binario);
			    if(operG>=0){
			       aux=strlen(binario);
			       for(leng=0,i=7;leng<aux&&leng<5;leng++,i--)
				  xb[i]=binario[leng];
			    }else{
			       xb[7]=binario[0];
			       xb[6]=binario[1];
			       xb[5]=binario[2];
			       xb[4]=binario[3];
			       xb[3]=binario[4];
			    }
			 }else{//con signo
			    if(operG<1||operG>8){
			       fRRR=fopen(ruta4,"a+t");
			       fprintf(fRRR,"%02d\tNo se admite 0 en pre/post-incremento/decremento\n",cLinea);
			       fclose(fRRR);
			       errBan++;
			    }
			    xb[2]='1';

			    char rrAux[4];
			    strcpy(rrAux,rr);
			    i=0;
			    if(idxPrePos>2){//post
			       xb[3]='1';
			       while(rrAux[i+1]!='\0'){
				  rr[i]=rrAux[i];
				  i++;
			       }
			       rr[i]='\0';
			    }else{//pre
			       while(rrAux[i]!='\0'){
				  rr[i]=rrAux[i+1];
				  i++;
			       }
			    }

			    if(idxPrePos==1||idxPrePos==3){//incremento
			       operG--;
			       ltoa(operG,binario,2);
			       strrev(binario);
			       aux=strlen(binario);
			       for(leng=0,i=7;leng<aux&&leng<4;leng++,i--)
				  xb[i]=binario[leng];
			    }else{//decremento
			       operG=operG-(operG*2);
			       ltoa(operG,binario,2);
			       strrev(binario);
			       xb[7]=binario[0];
			       xb[6]=binario[1];
			       xb[5]=binario[2];
			       xb[4]=binario[3];
			    }
			 }
		      }
		      if(strcmpi(rr,"y")==0){
			 xb[rr2]='1';
		      }else
			 if(strcmpi(rr,"sp")==0){
			    xb[rr1]='1';
			 }else
			    if(strcmpi(rr,"pc")==0){
			       xb[rr1]='1';
			       xb[rr2]='1';
			    }
		      xbInt=strtol(xb,&endptr,2);
		      fprintf(lst,"%02X",xbInt);
		      //a continuacion escribe en el arreglo s19
		      sprintf(s1aux,"%02X",xbInt);
		      appendS1(s1aux,2);
		     }break;
	      case 8:case 9:{//IDX1,IDX2
		      strcpy(xb,"11100000");
		      if(posCodMq[1]==9)
			 xb[6]='1';
		      if(strcmpi(rr,"y")==0){
			 xb[4]='1';
		      }else
			 if(strcmpi(rr,"sp")==0){
			    xb[3]='1';
			 }else
			    if(strcmpi(rr,"pc")==0){
			       xb[3]='1';
			       xb[4]='1';
			    }
		      if(operG<0)
			 xb[7]='1';
		      xbInt=strtol(xb,&endptr,2);
		      fprintf(lst,"%02X",xbInt);

		      //a continuacion escribe en el arreglo s19
		      sprintf(s1aux,"%02X",xbInt);
		      appendS1(s1aux,2);

		      if(posCodMq[1]==8){
			 if(xb[7]=='1'){
			    char cod[8],codLen;
			    ltoa(operG,cod,16);
			    codLen=strlen(cod);
			    cod[codLen-2]=toupper(cod[codLen-2]);
			    cod[codLen-1]=toupper(cod[codLen-1]);
			    fprintf(lst,"%c%c",cod[codLen-2],cod[codLen-1]);
			    //fprintf(lst,"    ---%02X",operG);
			    //fprintf(lst,"    ;IDX1 (9 bits)");
			    //a continuacion escribe en el arreglo s19
			    sprintf(s1aux,"%c%c",cod[codLen-2],cod[codLen-1]);
			    appendS1(s1aux,2);
			 }else{
			    fprintf(lst,"%02X",operG);
			    //a continuacion escribe en el arreglo s19
			    sprintf(s1aux,"%02X",operG);
			    appendS1(s1aux,2);
			 }
		      }else{
			 fprintf(lst,"%04X",operG);
			 //a continuacion escribe en el arreglo s19
			 sprintf(s1aux,"%04X",operG);
			 appendS1(s1aux,2);
		      }
		     }break;
	      case 10:case 11:{//[IDX2],[D,IDX]
		       if(posCodMq[1]==10)
			  strcpy(xb,"11100011");
		       else{
			  strcpy(xb,"11100111");
			  idxAcum=0;
		       }
		       if(strcmpi(rr,"y")==0){
			 xb[4]='1';
		       }else
			 if(strcmpi(rr,"sp")==0){
			    xb[3]='1';
			 }else
			    if(strcmpi(rr,"pc")==0){
			       xb[3]='1';
			       xb[4]='1';
			    }
		       xbInt=strtol(xb,&endptr,2);
		       fprintf(lst,"%02X",xbInt);
		       //a continuacion escribe en el arreglo s19
		       sprintf(s1aux,"%02X",xbInt);
		       appendS1(s1aux,2);
		       if(posCodMq[1]==10){
			  fprintf(lst,"%04X",operG);
			  //a continuacion escribe en el arreglo s19
			  sprintf(s1aux,"%04X",operG);
			  appendS1(s1aux,2);
		       }
		      }break;
	 }
      }
   }
}
void drvaCodMaq(FILE *lst,char *op,int dir){
   char aux[3],s1aux[30];
   s1aux[0]='\0';
   switch(dir){
       case 4:{//fcc
	       int opLeng=strlen(op);
	       for(int i=1;i<opLeng-1;i++){
		  fprintf(lst,"%02X",op[i]);

		  //a continuacion escribe en el arreglo s19
		  sprintf(aux,"%02X",op[i]);
		  strcat(s1aux,aux);
	       }
	       appendS1(s1aux,3);
	      }break;
       case 5:case 6:case 9:{//dc, dc.b, db
	       fprintf(lst,"%02X",operG);
	       //a continuacion escribe en el arreglo s19
	       sprintf(s1aux,"%02X",operG);
	       appendS1(s1aux,3);
	      }break;
       case 7:case 10:{//dc.w, dw
	       fprintf(lst,"%04X",operG);
	       //a continuacion escribe en el arreglo s19
	       sprintf(s1aux,"%04X",operG);
	       appendS1(s1aux,3);
	      }break;
       case 8:{//dc.l
	       fprintf(lst,"%08X",operG);
	       //a continuacion escribe en el arreglo s19
	       sprintf(s1aux,"%08X",operG);
	       appendS1(s1aux,3);
	      }break;
   }
}
void paso2(FILE *plst){
   char endBan=0,direct,nada,fin,firstS1=0;
   fin=cLinea;
   for(int iL=1;iL<fin;iL++){
      cLinea=iL;
      direct=-1;
      errAux=errBan;
      posCodMq[0]=codigoAll[iL].pcm0;
      posCodMq[1]=codigoAll[iL].pcm1;

      if(codigoAll[iL].etiq[0]=='\0'&&codigoAll[iL].cod[0]=='\0'&&codigoAll[iL].oper[0]=='\0')
	 nada=1;
      else
	 nada=0;

      if(strcmpi(codigoAll[iL].cod,"end")==0)
	 endBan=1;
      else
	 if(endBan==1){
	    endBan=0;
	    fRRR=fopen(ruta4,"a+t");
	    fprintf(fRRR,"%02d\tCualquier instruccion invalida despues de un END\n",iL);
	    fclose(fRRR);
	    errBan++;
	 }

      if(codigoAll[iL].pcm0==210)
	 direct=esDirectiva(codigoAll[iL].cod);

      if(direct>0)
	 directivas(codigoAll[iL].cod,codigoAll[iL].oper);


      if(strcmpi(codigoAll[iL].cod,"equ")==0)
	 if(codigoAll[iL].etiq[0]=='\0'){
	    fRRR=fopen(ruta4,"a+t");
	    fprintf(fRRR,"%02d\tDebe haber una etiqueta definida para la directiva EQU\n",iL);
	    fclose(fRRR);
	    errBan++;
	 }

      if(codigoAll[iL].pcm0!=210&&direct<1&&codigoAll[iL].pcm0!=-1)
	 operandoMain(codigoAll[iL].oper,codigoAll[iL].pcm0);


      fprintf(plst,"%02d\t",iL);
      if(nada!=1){
	 fprintf(plst,"%04X",codigoAll[iL].cLoc);
	 fprintf(plst,"\t%s",codigoAll[iL].etiq);
	 fprintf(plst,"\t%s",codigoAll[iL].cod);
	 fprintf(plst,"\t%s",codigoAll[iL].oper);
	 if(strlen(codigoAll[iL].oper)<8){
	    fprintf(plst,"\t");
	 }
	 if(direct<1&&codigoAll[iL].pcm0!=210&&errBan==errAux){
	    if(firstS1==0){//Es la primera instrucci¢n con codigo objeto
	       firstS1=1;
	       strcpy(arrS19[s19c].tipo,"s1");
	       sprintf(arrS19[s19c].dirIni,"%04x",codigoAll[iL].cLoc);
	       arrS19[s19c].codigo[0]='\0';
	    }
	    if(posCodMq[1]>6){
	       fprintf(plst,"\t%s",mnems[posCodMq[0]].codMaq[7]);
	       //a continuacion escribe en el arreglo s19
	       appendS1(mnems[posCodMq[0]].codMaq[7],1);
	       printCodMaq(plst,7,0);
	    }else{
	       fprintf(plst,"\t%s",mnems[posCodMq[0]].codMaq[posCodMq[1]]);
	       //a continuacion escribe en el arreglo s19
	       appendS1(mnems[posCodMq[0]].codMaq[posCodMq[1]],1);
	       printCodMaq(plst,posCodMq[1],codigoAll[iL+1].cLoc);
	    }
	 }else
	    if(direct>0){
	       fprintf(plst,"\t");
	       if(direct>3&&direct<11)
		  if(firstS1==0){//Es la primera instrucci¢n con codigo objeto
		     firstS1=1;
		     strcpy(arrS19[s19c].tipo,"s1");
		     sprintf(arrS19[s19c].dirIni,"%04x",codigoAll[iL].cLoc);
		     arrS19[s19c].codigo[0]='\0';
		  }
	       drvaCodMaq(plst,codigoAll[iL].oper,direct);
	    }
	 if(errBan!=errAux){
	    if(strlen(codigoAll[iL].oper)<8)
	       fprintf(plst,"\t");
	       fprintf(plst,"\t*** ERROR ***\n");
	 }else
	    fprintf(plst,"\n");

      }else
	 fprintf(plst,"\n");
   }
}
/*--------------------------------M-A-I-N---------------------------------*/
void main(void){
 FILE *fPoint,*fLST,*fTBS,*fS19;
 char linea[60],ruta[50],*ruta1,*ruta2,*ruta3,*ruta5,c;
 char etiqueta[24],codOp[24],operando[24];
 unsigned int contloc=0,codLong=0;
 int i,j,codPos,etC=0;
 int ban=1,/*check,*/direct,comillas,endBan=0,nada;//banderas
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
    printf("\n\t%s,",mnems[a].codMaq[0]);
    printf("%s,",mnems[a].codMaq[1]);
    printf("%s,",mnems[a].codMaq[2]);
    printf("%s,",mnems[a].codMaq[3]);
    printf("%s,",mnems[a].codMaq[4]);
    printf("%s,",mnems[a].codMaq[5]);
    printf("%s,",mnems[a].codMaq[6]);
    printf("%s,\n",mnems[a].codMaq[7]);
    delay(500);
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
 strcpy(ruta5,ruta);
 strcat(ruta5,".s19");

 strcpy(ruta1,ruta);
 strcat(ruta1,".asm");
 if((fPoint=fopen(ruta1,"rt"))==NULL){
    printf("\n\n\tError al abrir el archivo .ASM\n\t");
 }else{
    if((fLST=fopen(ruta2,"wt"))==0)
       printf("\n\tError al crear el archivo .LST\n\t");
    else{
       fprintf(fLST,"ENSAMBLADOR Beta 0.9.5\n");
       fprintf(fLST,"Creado por: Carlos Fco. Camacho Uribe\n");
       fprintf(fLST,"Codigo: 398251049\n");
       fprintf(fLST,"Ingenieria en Computacion, CUCEI UdeG\n\n\n");
       fprintf(fLST,"\t\tCODIGO FUENTE:\t\t\tCODIGO MAQUINA:\n");
       while(fgets(linea,60,fPoint)!=NULL){
	  etiqueta[0]='\0';
	  codOp[0]='\0';
	  operando[0]='\0';
	  i=0;
	  ban=1;j=0;
	  c=linea[i];
	  codPos=-1;
	  //check=0;
	  direct=-1;
	  comillas=0;
	  errAux=errBan;
	  codLong=0;
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
		if((direct=esDirectiva(etiqueta))>0||(codPos=busquedaBin(etiqueta,0,207))!=-1){
		   //check=1;
		   strcpy(operando,codOp);
		   strcpy(codOp,etiqueta);
		   etiqueta[0]='\0';
		}
	     }
	  }
	  if(codPos==-1&&nada!=1)
	     codPos=tipoCodOp(codOp);

	  if(comillas==1){
	     fRRR=fopen(ruta4,"a+t");
	     fprintf(fRRR,"%02d\tFalto cierre de comillas en el operando\n",cLinea);
	     fclose(fRRR);
	     errBan++;
	  }

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
		errBan++;
	     }else
		contloc=num;
	  }

	  if(etiqueta[0]!='\0'){
	     if(endBan==1){
		fRRR=fopen(ruta4,"a+t");
		fprintf(fRRR,"%02d\tNo debe haber ninguna etiqueta definida para la directiva END\n",cLinea);
		fclose(fRRR);
		errBan++;
	     }else
		etiquetas(etiqueta,codOp,operando,contloc,etC);
	  }

	  if(direct>0)
	     codLong=directivas(codOp,operando);

	  if(direct<1)
	     if(codPos==-1&&nada!=1){
		fRRR=fopen(ruta4,"a+t");
		fprintf(fRRR,"%02d\tCodigo desconocido\n",cLinea);
		fclose(fRRR);
		errBan++;
	     }

	  if(codPos!=210&&direct<1&&codPos!=-1)
	     codLong=operandoMain(operando,codPos);


	  //***Como es el primer paso, solo se guarda en el arreglo:***
	  if(strcmpi(codOp,"equ")==0)
	     codigoAll[cLinea].cLoc=tabSim[etC-1].valor;
	  else
	     codigoAll[cLinea].cLoc=contloc;
	  strcpy(codigoAll[cLinea].etiq,etiqueta);
	  strcpy(codigoAll[cLinea].cod,codOp);
	  strcpy(codigoAll[cLinea].oper,operando);
	  codigoAll[cLinea].errors=errBan;
	  codigoAll[cLinea].pcm0=codPos;//posCodMq[0];
	  codigoAll[cLinea].pcm1=posCodMq[1];
	  contloc+=codLong;

	  cLinea++;
       }

       //****** Aqui se calcula el registro s0: ******
       strcpy(arrS19[0].tipo,"s0");
       sprintf(arrS19[0].dirIni,"%04X",0);
       strcpy(arrS19[0].codigo,ruta1);
       calculaCHKSM(0);
       s19c++;
       //****** Aqui se hace el segundo paso: ******
       pasos++;
       paso2(fLST);

       fclose(fLST);
    }
    fclose(fPoint);
    printf("\n\n\t­­­Archivo leido con exito!!!\n\n\t");

    if(errBan!=0)
       printf("Se encontraron %d errores en el archivo\n\n\t",errBan);
    else{
       if((fS19=fopen(ruta5,"wt"))==0)
	  printf("\n\tError al crear el archivo .s19\n\t");
       else{
	  calculaCHKSM(s19c);
	  s19c++;
	  strcpy(arrS19[s19c].tipo,"s9");
	  sprintf(arrS19[s19c].dirIni,"%04X",0);
	  arrS19[s19c].codigo[0]='\0';
	  calculaCHKSM(s19c);
	  s19c++;
	  imprimeS19(fS19);
	  fclose(fS19);
       }
    }

    if(etC>0){
       if((fTBS=fopen(ruta3,"wt"))==0)
	  printf("\n\tError al crear el archivo .TBS\n\t");
       else{
	  fprintf(fTBS,"SIMBOLO/VALOR");
	  for(int i=0;i<etC;i++){
	     fprintf(fTBS,"\n %s",tabSim[i].etiqueta);
	     fprintf(fTBS,"\t %04X",tabSim[i].valor);
	  }
	  fclose(fTBS);
       }
    }
 }
 printf("\n\tPresiona cualquier tecla para salir del programa");
 getch();
}