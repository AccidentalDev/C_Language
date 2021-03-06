//Carlos Fco. Camacho Uribe
//Taller de Programacion de Sistemas
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<io.h>
#include<stdlib.h>
#include<CTYPE.H>
#include<math.h>

/*typedef struct{
   char *cod_ob;
   int lenght;
}Code;*/

int mnemonico(char *mne){
   if(strcmp(mne,"LDAA")==0){
      return 0;
   }else{
      if(strcmp(mne,"LDAB")==0)
	 return 1;
      else
	 if(strcmp(mne,"ORG")==0)
	    return 30;
	 else
	    if(strcmp(mne,"END")==0)
	       return 31;
	    else
	       if(strcmp(mne,"EQU")==0)
		  return 32;
	       else
		  if(strcmp(mne,"DC.B")==0)
		     return 33;
		  else
		     return -1;
    }
}

char *coops(int tipoMne,int tipoDir,int &longRef){
   char *codigo;
   //0=inmediato,1=directo,2=extendido,3=indexado1,4=indexado2,9=inherente
   if(tipoMne!=-1){
      switch(tipoMne){
	  case 0:{switch(tipoDir){
		      case 0:{codigo="86";
			      longRef=2;
			     }break;
		      case 1:{codigo="96";
			      longRef=2;
			     }break;
		      case 2:{codigo="B6";
			      longRef=3;
			     }break;
		      case 3:{codigo="A6";
			      longRef=2;
			     }break;
		      case 4:{codigo="A6";
			      longRef=3;
			     }break;
		  }
		 }break;
	  case 1:{switch(tipoDir){
		      case 0:{codigo="C6";
			      longRef=2;
			     }break;
		      case 1:{codigo="D6";
			      longRef=2;
			     }break;
		      case 2:{codigo="F6";
			      longRef=3;
			     }break;
		      case 3:{codigo="E6";
			      longRef=2;
			     }break;
		      case 4:{codigo="E6";
			      longRef=3;
			     }break;
		  }
		 }break;
	  default:{codigo="Directiva";
		   longRef=0;
		  }
      }
   }else{
      codigo="Mnemonico desconocido";
      longRef=0;
    }
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
   char temp[30],*et=0,*mnem=0,*op=0,*com=0,*check=0,*coop,*endptr;
   int longitud,Mne,dir,ban=0;
   long operando;
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

   //Revision de mnemonico
   mnem=strupr(mnem);
   if(strcmp(mnem,"ORG")==0)
      ban=1;
   Mne=mnemonico(mnem);
   if(Mne==-1){
      dir=-1;
      coop=coops(Mne,0,longitud);
   }else{
      //Inicia revision de tipo de direccionamiento
      if(op==0){//Inherente
	 coop=coops(Mne,9,longitud);
	 dir=9;
      }else{
	 check=strchr(op,'#');
	 if(check!=0){
	    coop=coops(Mne,0,longitud);
	    dir=0;//Inmediato
	 }else{
	    check=strchr(op,',');
	    if(check!=0){
	       coop=coops(Mne,3,longitud);
	       dir=3;//indexado1
	    }else{
	       check=strchr(op,'[');
	       if(check!=0){
		  coop=coops(Mne,4,longitud);
		  dir=4;//indexado2
	       }else{
		  check=strchr(op,'$');
		  if(check!=0){
		     op=op+1;
		     operando=strtol(op,&endptr,16);
		     if(ban==1)
			lCont=operando;//Guarda el parametro de Org
		     if(operando>255){//extendido en hexadecinal
			coop=coops(Mne,2,longitud);
			dir=2;
		     }else{//directo en hexadecimal
			coop=coops(Mne,1,longitud);
			dir=1;
		      }
		  }else{
		     operando=atoi(op);
		     if(operando>255){//extendido
			coop=coops(Mne,2,longitud);
			dir=2;
		     }else{//direxto
			coop=coops(Mne,1,longitud);
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
   lCont=lCont+longitud;
   printf("\n* Codigo Objeto: %s",coop);prints(dir);
   printf("\n* Longitud: %d",longitud);
   printf("\n* Contador del programa: %04d",mneCont);
   printf("\n* Contador de localidades: %X",lCont);
}
//----------------------------------MAIN-----------------------------------
void main(){
 char linea[30];
 char *path=0,*name=0,tmp;
 int cont=0,file,posnull,endFile;
 long contloc;
 //Code codOps[50];
 clrscr();
 path="C:/Tc/Prog/";
 name="test2.asm";
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
       cont++;
       ensambla(linea,/*codOps,*/cont,contloc);
       printf("\n\tPresiona cualquier tecla para continuar\n\t");
       getch();
    }
    close(file);
 }
 //getch();
}
