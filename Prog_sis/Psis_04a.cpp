//Carlos Fco. Camacho Uribe
//Taller de Programacion de Sistemas
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<io.h>
#include<stdlib.h>
#include<CTYPE.H>
#include<math.h>

typedef struct{
   char *nombre;
   int id;
}Mnemo;

FILE *fPoint;

int mnemonico(char *mne){
   int c,finded=-1;
   Mnemo Ms[11];
   //Agregar el mnemonico IBNE para el modo de direccionamiento relativo
   Ms[0].nombre="LDAA";
   Ms[0].id=0;
   Ms[1].nombre="LDAB";
   Ms[1].id=1;
   Ms[2].nombre="ADDA";
   Ms[2].id=2;
   Ms[3].nombre="ADDB";
   Ms[3].id=3;
   Ms[4].nombre="ASLA";
   Ms[4].id=4;
   Ms[5].nombre="ASLB";
   Ms[5].id=5;
   Ms[6].nombre="ORG";
   Ms[6].id=30;
   Ms[7].nombre="END";
   Ms[7].id=31;
   Ms[8].nombre="EQU";
   Ms[8].id=32;
   Ms[9].nombre="DC.B";
   Ms[9].id=33;
   Ms[10].nombre="DC.W";
   Ms[10].id=34;

   for(c=0;c<11;c++){
      if(strcmp(mne,Ms[c].nombre)==0)
	 finded=Ms[c].id;
   }

   return(finded);
}

long operando(int tipo,char *opr){
   char /**result=0,*/*endptr;
   long temp;
   switch(tipo){
       case 0:{opr=opr+1;
	       temp=strtol(opr,&endptr,16);
	       //ltoa(temp,result,16);
	      }break;//inmediato
       case 1:{if(strchr(opr,'$')){
		  opr=opr+1;
		  temp=strtol(opr,&endptr,16);
		  //result=opr;
	       }else{
		  temp=strtol(opr,&endptr,10);
		  //ltoa(temp,result,16);
		}
	      }break;//directo
       case 2:{if(strchr(opr,'$')){
		  opr=opr+1;
		  temp=strtol(opr,&endptr,16);
		  //strcpy(result,opr);
	       }else{
		  temp=strtol(opr,&endptr,10);
		  //ltoa(temp,result,16);
		}
	      }break;//extendido
       case 3:{
	      }break;//indexado
       case 4:{
	      }break;//indexado2
   }
   //strupr(result);
   return(/*result*/temp);
}

char *coops(int tipoMne,int tipoDir,int &longRef,char *op,long &opr){
   char *codigo=0/*,*cod2=0*/;
   //0=inmediato,1=directo,2=extendido,3=indexado1,4=indexado2,9=inherente
   if(tipoMne!=-1){
      switch(tipoMne){
	  case 0:{switch(tipoDir){//LDAA
		      case 0:{codigo="86";
			      longRef=2;
			      opr=operando(0,op);
			     }break;
		      case 1:{codigo="96";
			      longRef=2;
			      opr=operando(1,op);
			     }break;
		      case 2:{codigo="B6";
			      longRef=3;
			      opr=operando(2,op);
			     }break;
		      case 3:{codigo="A6";
			      longRef=2;
			      opr=operando(3,op);
			     }break;
		      case 4:{codigo="A6";
			      longRef=3;
			      opr=operando(4,op);
			     }break;
		  }
		 }break;
	  case 1:{switch(tipoDir){//LDAB
		      case 0:{codigo="C6";
			      longRef=2;
			      opr=operando(0,op);
			     }break;
		      case 1:{codigo="D6";
			      longRef=2;
			      opr=operando(1,op);
			     }break;
		      case 2:{codigo="F6";
			      longRef=3;
			      opr=operando(2,op);
			     }break;
		      case 3:{codigo="E6";
			      longRef=2;
			      opr=operando(3,op);
			     }break;
		      case 4:{codigo="E6";
			      longRef=3;
			      opr=operando(4,op);
			     }break;
		  }
		 }break;
	  case 2:{switch(tipoDir){//ADDA
		      case 0:{codigo="8B";
			      longRef=2;
			      opr=operando(0,op);
			     }break;
		      case 1:{codigo="9B";
			      longRef=2;
			      opr=operando(1,op);
			     }break;
		      case 2:{codigo="BB";
			      longRef=3;
			      opr=operando(2,op);
			     }break;
		      case 3:{codigo="AB";
			      longRef=2;
			      opr=operando(3,op);
			     }break;
		      case 4:{codigo="AB";
			      longRef=3;
			      opr=operando(4,op);
			     }break;
		  }
		 }break;
	  case 3:{switch(tipoDir){//ADDB
		      case 0:{codigo="CB";
			      longRef=2;
			      opr=operando(0,op);
			     }break;
		      case 1:{codigo="DB";
			      longRef=2;
			      opr=operando(1,op);
			     }break;
		      case 2:{codigo="FB";
			      longRef=3;
			      opr=operando(2,op);
			     }break;
		      case 3:{codigo="EB";
			      longRef=2;
			      opr=operando(3,op);
			     }break;
		      case 4:{codigo="EB";
			      longRef=3;
			      opr=operando(4,op);
			     }break;
		  }
		 }break;
	  case 4:{codigo="48";//ASLA
		  longRef=1;
		 }break;
	  case 5:{codigo="58";//ASLB
		  longRef=1;
		 }break;
	  default:{codigo="Directiva";
		   longRef=0;
		  }
      }
   }else{
      codigo="Mnemonico desconocido";
      longRef=0;
    }
   /*if(longRef>1)
      strcat(codigo,cod2);*/
   return(codigo);
}

void prints(int tipoDir){
   switch(tipoDir){
	case 0:printf("   **Es un modo de direccionamiento inmediato**");
	       break;
	case 1:printf("   **Es un modo de direccionamiento directo**");
	       break;
	case 2:printf("   **Es un modo de direccionamiento extendido**");
	       break;
	case 3:printf("   **Es un modo de direccionamiento indexado1**");
	       break;
	case 4:printf("   **Es un modo de direccionamiento indexado2**");
	       break;
	case 9:printf("   **Es un modo de direccionamiento inherente**");
	       break;
	default:printf(" ");
   }
}

void ensambla(char cadena[],/*Code cods[50],*/int mneCont,long &lCont){
   char temp[30],*et=0,*mnem=0,*op=0,*com=0,*coop=0,*endptr;
   int longitud,Mne,dir,ban=0/*,cop2=0*/;
   long operando=0;
   char *opTmp=0,*check=0;//char *temp2="000000";

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
   printf("\n* Etiqueta: %s",et);
   printf("\n* Mnemonico: %s",mnem);
   printf("\n* Operandos: %s",op);
   printf("\n* Comentarios: %s",com);

   fprintf(fPoint,"%s\t%s\t%s\t\n",et,mnem,op);
   //FILE *fopen(const char *filename, const char *mode); mode=w -> crea
   //fprintf
   //Revision de mnemonico
   mnem=strupr(mnem);
   if(strcmp(mnem,"ORG")==0)
      ban=1;
   Mne=mnemonico(mnem);
   if(Mne==-1){
      dir=-1;
      coop=coops(Mne,0,longitud,op,operando);
   }else{
      //Inicia revision de tipo de direccionamiento
      if(op==0){//Inherente
	 coop=coops(Mne,9,longitud,op,operando);
	 dir=9;
      }else{
	 check=strchr(op,'#');
	 if(check!=0){//Inmediato
	    coop=coops(Mne,0,longitud,op,operando);
	    dir=0;
	 }else{
	    check=strchr(op,',');
	    if(check!=0){
	       coop=coops(Mne,3,longitud,op,operando);
	       dir=3;//indexado1
	    }else{
	       check=strchr(op,'[');
	       if(check!=0){
		  coop=coops(Mne,4,longitud,op,operando);
		  dir=4;//indexado2
	       }else{
		  check=strchr(op,'$');
		  if(check!=0){
		     strcpy(opTmp,op);
		     opTmp=opTmp+1;
		     operando=strtol(opTmp,&endptr,16);
		     if(ban==1)
			lCont=operando;//Guarda el parametro de Org
		     if(operando>255){//extendido en hexadecinal
			coop=coops(Mne,2,longitud,op,operando);
			dir=2;
		     }else{//directo en hexadecimal
			coop=coops(Mne,1,longitud,op,operando);
			dir=1;
		      }
		  }else{
		     operando=atoi(op);
		     if(operando>255){//extendido
			coop=coops(Mne,2,longitud,op,operando);
			dir=2;
		     }else{//direxto
			coop=coops(Mne,1,longitud,op,operando);
			dir=1;
		      }
		   }
		}
	     }
	  }
       }
    }
   /*strcpy(cods[mneCont].cod_ob,coop);
   cods[mneCont].lenght=longitud;*/
   /*coop=strtok(coop," ");
   cop2=strtok(NULL," ");
   if(ban==1)
      cop2=" ";
   if(cop2!=0){
      strcat(temp2,cop2);
      cop2=temp2;
   }*/

   lCont=lCont+longitud;
   if(longitud==3)
      printf("\n* Codigo Objeto: %s %04X",coop,operando);
   else
      if(longitud==4)
	 printf("\n* Codigo Objeto: %s %06X",coop,operando);
      else
	 if(longitud==2)
	    printf("\n* Codigo Objeto: %s %02X",coop,operando);
	 else
	    printf("\n* Codigo Objeto: %s",coop);
   prints(dir);
   printf("\n* Longitud: %d",longitud);
   printf("\n* Contador del programa: %04d",mneCont);
   printf("\n* Contador de localidades: %X",lCont);
}
//----------------------------------MAIN-----------------------------------
void main(){
 char linea[30];
 char *path=0,*name=0,*dir=0,tmp;
 int cont=0,file,posnull,endFile;
 long contloc;
 //Code codOps[50];
 clrscr();
 /*printf("\n*Escribe el nombre del archivo .asm a abrir (no incluir la extension):\n\t");
 gets(name);
 printf("\n\tEscribe la ruta:\n\t");
 gets(path);*/
 path="C:/Tc/Prog/Prog_sis/";
 name="test2";
 strcat(path,name);
 strcpy(dir,path);
 strcat(dir,".asm");
 if((file=open(dir,0))<0){
    printf("\n\tError al abrir el archivo\n\t");
    getch();
 }else{
    strcat(path,".lst");
    if((fPoint=fopen(/*"F:/CFCU/test2.lst"*/path,"w"))==0){
       printf("\n\tError al crear el archivo LST\n\t");
       getch();
    }else{
       fprintf(fPoint,"CODIGO FUENTE                     CODIGO OBJETO\n");
       for(int j=0;(endFile=read(file,&tmp,1))!=0;j++){
	  for(int i=0;i<30&&tmp!='\n'&&endFile!=0;i++){
	     linea[i]=tmp;
	     endFile=read(file,&tmp,1);
	     posnull=i;
	  }
	  linea[posnull+1]='\0';
	  cont++;
	  ensambla(linea,/*codOps,*/cont,contloc);
	  printf("\n\tPresiona cualquier tecla para continuar\n\t");
	  getch();
       }
       fclose(fPoint);
    }
    close(file);
 }
}
