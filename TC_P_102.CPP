//Carlos Francisco Camacho Uribe
//Teoria de la Computacion
//Proyecto 1.02
#include<stdio.h>
#include<conio.h>
#include<dos.h>
void imp_stats(int stat,int sal){
   char *txt;
   switch(sal){
	 case 0: txt="inicio";
		 break;
	 case 1: txt="pasillo";
		 break;
	 case 2: txt="pared";
		 break;
	 case 3: txt="peligro!";
		 break;
	 case 4: txt="SALIDA";
		 break;
	 case 5: txt="PELIGRO!!!";
		 break;
	 default:printf("\tError al revisar simbolo de salida");
   }
   gotoxy(45,8);printf("Simbolo de salida: %s",txt);
   gotoxy(45,11);printf("Estado actual: %d",stat);
}
void imprime(int x,int y,int estado,int salida){
  int i;
  clrscr();
  for(i=0;i<80;i++)
     printf("=");
  printf("         SIMULADOR DE UN LABERINTO\n");
  for(i=0;i<80;i++)
     printf("=");
  printf("\n");
  printf("\n\tÍÍÍÍËÍÍÍËÍÍÍ»   ÉÍÍÍÍÍÍÍËÍÍÍÍ");
  printf("\n\t    º   º   º   º       º    ");
  printf("\n\tÉÍÍÍ¼   ÌÍÍÍÊÍÍÍ¼   ÍÍÍÍ¹   [");
  printf("\n\tº       º               º   º");
  printf("\n\tº   ÉÍÍÍÎÍÍÍ»   ÉÍÍÍ»   ÈÍÍÍ¼");
  printf("\n\t    º   º   º   º   º        ");
  printf("\n\tÍÍÍÍ¼   º   ÈÍÍÍ¼   ÌÍÍÍÍÍÍÍÍ");
  printf("\n\t        º           º        ");
  printf("\n\tÉÍÍÍÍÍÍÍ¼   ÉÍÍÍËÍÍÍ¼   ÉÍÍÍ[");
  printf("\n\tº           º   º       º    ");
  printf("\n\tÈÍÍÍÍÍÍÍËÍÍÍ¼   ÈÍÍÍÍÍÍÍ¼   º");
  printf("\n\t        º                   º");
  printf("\n\tÍÍÍÍ»   º   ÉÍÍÍËÍÍÍ»   ÉÍÍÍ¹");
  printf("\n\t    º   º   º   º   º   º   º");  //³ alt+179
  printf("\n\tÍÍÍÍÊÍÍÍÊÍÍÍ¼   º   ÈÍÍÍ¼   [");
  gotoxy(x,y); printf(""); // alt+02
  imp_stats(estado,salida);
  delay(200);
}
int entrada_int(char direccion){
   switch(direccion){
	 case 'w':return(0);
	 case 's':return(1);
	 case 'a':return(2);
	 case 'd':return(3);
	 case 'n':return(-1);
	 default:return(-2);
   }
}

/*----------------------------------MAIN--------------------------------*/
void main(){
  //-------------------01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64
  int edo_sig[4][64]={{ 1, 2, 5, 2, 5, 6, 7, 8, 9, 9,11,11,13,14,15,15,17,17,18,19,20,22,22,23,25,25,27,27,29,29,31,31,33,33,35,35,37,37,39,39,41,42,43,43,44,46,47,47,49,49,50,52,53,53,55,55,57,58,58,60,61,62,62,63},
		      { 1, 4, 3, 4, 3, 6, 7, 8,10,10,12,12,13,14,16,16,18,19,20,21,21,23,24,24,26,26,28,28,30,30,32,32,34,34,36,36,38,38,40,40,41,42,44,45,45,46,48,48,50,51,51,52,54,54,56,56,57,59,59,60,61,63,64,64},
		      { 1, 2, 3, 4, 5, 6, 7, 8, 7, 5,11, 1, 2, 4, 6, 8, 9,18,11,20,13,14,23,16,17,18,19,28,29,22,31,24,33,26,35,28,29,38,31,40,33,42,35,44,37,38,39,48,41,42,51,44,53,46,55,48,49,58,51,52,53,62,55,64},
		      {12,13, 3,14,10,15, 9,16,17,10,19,12,21,22,15,24,25,26,27,20,21,30,23,32,25,34,27,36,37,30,39,32,41,34,43,36,45,46,47,40,49,50,43,52,45,54,47,56,57,50,59,60,61,54,63,56,57,58,59,60,61,62,63,64}};
		      //                1                   2                   3                   4                   5                   6
  //------------------1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4
  int salida[4][64]={{2,2,1,1,2,2,2,2,2,1,2,1,2,2,2,1,2,1,1,1,1,2,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,2,2,1,1,2,2,1,2,1,1,2,2,1,2,1,2,2,1,2,2,3,1,1},
		     {2,1,3,2,1,2,2,2,1,2,1,2,2,2,1,2,1,1,1,1,2,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,2,2,1,1,2,2,1,2,1,1,2,2,1,2,1,2,2,1,2,2,2,1,1,2},
		     {3,2,2,2,2,3,3,3,1,1,2,1,1,1,1,1,1,2,1,2,1,1,2,1,1,1,1,2,2,1,2,1,2,1,2,1,1,2,1,2,1,3,1,2,1,1,1,2,1,1,2,1,2,1,2,1,1,2,1,1,1,2,1,2},
		     {1,1,2,1,1,1,1,1,1,2,1,2,1,1,2,1,1,1,1,2,2,1,2,1,2,1,2,1,1,2,1,2,1,2,1,2,1,1,1,2,1,1,2,1,2,1,2,1,1,2,1,1,1,2,1,2,3,4,2,3,4,2,2,4}};

  int posx=9,posy=12,j,ban=0;
  int st=1,ext=0,ent;
  char dir;
  imprime(posx,posy,st,ext);
  do{
    gotoxy(7,22); printf("¨Direccion? (w=arriba,s=abajo,a=izquierda,d=derecha): ");
    if (kbhit()!=0)
    if (dir!=0){
    dir=getch();
    ent=entrada_int(dir);
    if(ent>-1){
       ext=salida[ent][st-1];
       st=edo_sig[ent][st-1];
    }else
       ext=1;
    if(ext==1){
       ban=0;
       switch(dir){
	   case 'w':{for(j=0;j<2;j++){
		       posy--;
		       imprime(posx,posy,st,ext);
		     }
		    }break;
	   case 's':{for(j=0;j<2;j++){
		       posy++;
		       imprime(posx,posy,st,ext);
		     }
		    }break;
	   case 'a':{for(j=0;j<4;j++){
		       posx--;
		       imprime(posx,posy,st,ext);
		     }
		    }break;
	   case 'd':{for(j=0;j<4;j++){
		       posx++;
		       imprime(posx,posy,st,ext);
		     }
		    }break;
	   case 'n':printf("\n\tFin del programa");
		    break;
	   default: printf("\n\tERROR, comando no permitido");
       }
    }else
       if(ext==2){
	  ban=0;
	  imprime(posx,posy,st,ext);
       }else
	  if(ext==3){
	     if(ban==1)
		imprime(posx,posy,st,5);
	     else
		if(ban==2){
		   gotoxy(posx,posy);printf("*");
		   delay(2500);
		   gotoxy(6,11);printf("                                    ");
		   gotoxy(6,12);printf("­­­­­­HAS CAIDO EN UNA TRAMPA!!!!!! ");
		   gotoxy(6,13);printf("                                    ");
		   dir='n';
		}else
		   imprime(posx,posy,st,ext);
	     ban++;
	  }else
	     if(ext==4){
		imprime(posx+1,posy,st,ext);
		delay(1000);
		gotoxy(6,11);printf("                                     ");
		gotoxy(6,12);printf("­­­­­­HAS SALIDO DEL LABERINTO!!!!!! ");
		gotoxy(6,13);printf("                                     ");
		dir='n';
	     }
    }
  }while(dir!='n');
  getch();
}