//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 03
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<C:\TC\Prog\tsop\cola_sop.h>

void burbuja(int a[5][2]){
   int b,i,y,z;
   do{
     b=0;
     for(i=0;i<4;i++)
	if(a[i][1]>a[i+1][1]){
	   z=a[i][0];
	   y=a[i][1];
	   a[i][0]=a[i+1][0];
	   a[i][1]=a[i+1][1];
	   a[i+1][0]=z;
	   a[i+1][1]=y;
	   b=1;
	}
   }while(b==1);
}

void tabla(){
   int x,y;
   textcolor(6);
   for(y=2;y<14;y++){
      if(y==4||y==6||y==8||y==10||y==12){
	 gotoxy(4,y);cprintf("Ã");
	 gotoxy(61,y);cprintf("´");
      }else{
	 gotoxy(4,y);cprintf("³");
	 gotoxy(12,y);cprintf("³");
	 gotoxy(20,y);cprintf("³");
	 gotoxy(29,y);cprintf("³");
	 gotoxy(38,y);cprintf("³");
	 gotoxy(47,y);cprintf("³");
	 gotoxy(54,y);cprintf("³");
	 gotoxy(61,y);cprintf("³");
       }
   }
   for(x=5;x<61;x++){
      if(x==12||x==20||x==29||x==38||x==47||x==54){
	 gotoxy(x,1);cprintf("Â");
	 gotoxy(x,4);cprintf("Å");
	 gotoxy(x,6);cprintf("Å");
	 gotoxy(x,8);cprintf("Å");
	 gotoxy(x,10);cprintf("Å");
	 gotoxy(x,12);cprintf("Å");
	 gotoxy(x,14);cprintf("Á");
      }else{
	 gotoxy(x,1);cprintf("Ä");
	 gotoxy(x,4);cprintf("Ä");
	 gotoxy(x,6);cprintf("Ä");
	 gotoxy(x,8);cprintf("Ä");
	 gotoxy(x,10);cprintf("Ä");
	 gotoxy(x,12);cprintf("Ä");
	 gotoxy(x,14);cprintf("Ä");
      }
   }
   gotoxy(4,1);cprintf("Ú");
   gotoxy(61,1);cprintf("Â");
   gotoxy(4,14);cprintf("À");
   gotoxy(61,14);cprintf("Ù");

   for(x=62;x<68;x++){
      gotoxy(x,1);cprintf("Ä");
      gotoxy(x,3);cprintf("Ä");
      gotoxy(x,5);cprintf("Ä");
   }
   gotoxy(61,3);cprintf("Ã");//Cuanto
   gotoxy(61,5);cprintf("Ã");
   gotoxy(68,1);cprintf("¿");
   gotoxy(68,2);cprintf("³");
   gotoxy(68,3);cprintf("´");
   gotoxy(68,4);cprintf("³");
   gotoxy(68,5);cprintf("Ù");
}

void ejes(){
   int i,j;
   textcolor(6);
   for(i=16;i<=25;i++){
      gotoxy(5,i);cprintf("³");
   }
   for(j=1;j<81;j++){
      gotoxy(j,23);cprintf("Ä");
   }
   gotoxy(5,23);cprintf("Å");
   textcolor(7);
   gotoxy(6,24);
   cprintf("1234567891111111111222222222233333333334444444444555555555566666666667");
   gotoxy(15,25);cprintf("0123456789012345678901234567890123456789012345678901234567890");
}

void texto(){
   textcolor(4);
   gotoxy(5,2);cprintf("NOMBRE");
   gotoxy(5,3);cprintf("PROCESO");
   gotoxy(13,2);cprintf("HORA DE");
   gotoxy(13,3);cprintf("LLEGADA");
   gotoxy(21,2);cprintf("DURACION");
   gotoxy(30,2);cprintf("TIEMPO");
   gotoxy(30,3);cprintf("ASIGNADO");
   gotoxy(39,2);cprintf("TIEMPO");
   gotoxy(39,3);cprintf("RESTANTE");
   gotoxy(48,2);cprintf("HORA");
   gotoxy(48,3);cprintf("INICIO");
   gotoxy(55,2);cprintf("TIEMPO");
   gotoxy(55,3);cprintf("ESPERA");
   textcolor(7);
   gotoxy(8,5);cprintf("A");
   gotoxy(8,7);cprintf("B");
   gotoxy(8,9);cprintf("C");
   gotoxy(8,11);cprintf("D");
   gotoxy(8,13);cprintf("E");

   gotoxy(50,5);cprintf("-");
   gotoxy(50,7);cprintf("-");
   gotoxy(50,9);cprintf("-");
   gotoxy(50,11);cprintf("-");
   gotoxy(50,13);cprintf("-");
   gotoxy(57,5);cprintf("-");
   gotoxy(57,7);cprintf("-");
   gotoxy(57,9);cprintf("-");
   gotoxy(57,11);cprintf("-");
   gotoxy(57,13);cprintf("-");

   gotoxy(64,7);cprintf("Promedio");
   gotoxy(64,8);cprintf("de Espera:");
   gotoxy(64,11);cprintf("Tiempo usado");
   gotoxy(64,12);cprintf("por el S.O.");

   textcolor(4);gotoxy(62,2);cprintf("CUANTO");

   textcolor(4);gotoxy(1,16);cprintf("S.O.");
   textcolor(4);gotoxy(1,17);cprintf("NULO");
   textcolor(3);gotoxy(4,18);cprintf("E");
   textcolor(6);gotoxy(4,19);cprintf("D");
   textcolor(5);gotoxy(4,20);cprintf("C");
   textcolor(2);gotoxy(4,21);cprintf("B");
   textcolor(1);gotoxy(4,22);cprintf("A");
}

void info(int sel,int tipo){
   int x;
   if(tipo==1)
      x=50;
   else
      x=57;
   switch(sel){
	 case 0:{textcolor(7);gotoxy(x,5);
		}break;
	 case 1:{textcolor(7);gotoxy(x,7);
		}break;
	 case 2:{textcolor(7);gotoxy(x,9);
		}break;
	 case 3:{textcolor(7);gotoxy(x,11);
		}break;
	 case 4:{textcolor(7);gotoxy(x,13);
		}break;
   }
}

float prom_espera(int espera[5]){
   float suma=0.0;
   for(int i=0;i<5;i++)
      suma=suma+espera[i];
   return(suma/5);
}
float tiempoSO(int tiempo,int d[5]){
   int suma=0;
   float temp;
   for(int i=0;i<5;i++)
      suma=suma+d[i];
   temp=tiempo*100;
   return(temp/suma);
}
/*--------------------------------MAIN----------------------------------*/
void main(){
   //org[numero de proceso][hora llegada]
   int process[5];
   int org[5][2]={{0,0},{1,0},{2,0},{3,0},{4,0}};
   int duracion[5],t_asign[5]={0,0,0,0,0};
   int t_SO=0,t_rest[5],inicio[5],t_espera[5],ejecutando,elapsed=1;
   int i,t,posx=0,px=1,cuanto,elapsed_cuanto=0,antiBug=0;
   Cola Procesos;

   Inicializa(Procesos);
   clrscr();
   textcolor(7);
   tabla();
   ejes();
   texto();
   //----------Captura los datos-------------
   //Captura de llegadas
   textcolor(7);

   gotoxy(16,5);
   scanf("%d",&org[0][1]);

   gotoxy(16,7);
   scanf("%d",&org[1][1]);

   gotoxy(16,9);
   scanf("%d",&org[2][1]);

   gotoxy(16,11);
   scanf("%d",&org[3][1]);

   gotoxy(16,13);
   scanf("%d",&org[4][1]);
   //Fin captura de llegadas
   //Captura de Duraciones
   gotoxy(24,5);
   scanf("%d",&duracion[0]);

   gotoxy(24,7);
   scanf("%d",&duracion[1]);

   gotoxy(24,9);
   scanf("%d",&duracion[2]);

   gotoxy(24,11);
   scanf("%d",&duracion[3]);

   gotoxy(24,13);
   scanf("%d",&duracion[4]);

   gotoxy(64,4);
   scanf("%d",&cuanto);
   //Fin captura de duraciones
   //---------Fin captura de datos-----------
   t=5;
   for(i=0;i<5;i++){
      gotoxy(33,t);
      printf("%d",t_asign[i]);
      t=t+2;
   }
   t=5;
   for(i=0;i<5;i++){
      gotoxy(42,t);
      t_rest[i]=duracion[i];
      printf("%d",t_rest[i]);
      t=t+2;
   }
   for(i=0;i<5;i++){
      process[i]=org[i][1];
   }
   burbuja(org);
   for(i=0;i<5;i++)
      PoneEnCola(org[i][0],Procesos);
   getch();
   //---------------Inicia representacion------------------
   i=6;
   ejecutando=ValorEnTope(Procesos);
   QuitaDeCola(Procesos);
   do{
     //---------------info_eje_x----------------
     textcolor(4);
     gotoxy(i,24);
     if(i<15){
	cprintf("%d",px);
	px++;
     }else{
	if(i<25)
	   cprintf("1");
	else
	   if(i<35)
	      cprintf("2");
	   else
	      if(i<45)
		 cprintf("3");
	      else
		 if(i<55)
		    cprintf("4");
		 else
		    if(i<65)
		       cprintf("5");
		    else
		       if(i<75)
			  cprintf("6");
		       else
			  cprintf("7");
      }
     //------------------------
     gotoxy(i,25);
     if(i>14){
	cprintf("%d",posx);
	if(posx==9)
	   posx=0;
	else
	   posx++;
     }
     //--------------fin_info_eje_x-------------

     textcolor(7);
     gotoxy(i,16);cprintf("Û");
     gotoxy(i,17);cprintf("Û");
     gotoxy(i,18);cprintf("Û");
     gotoxy(i,19);cprintf("Û");
     gotoxy(i,20);cprintf("Û");
     gotoxy(i,21);cprintf("Û");
     gotoxy(i,22);cprintf("Û");

     //þþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþ
     //-------Seccion de condiciones (nucleo del programa)--------
     if(process[ejecutando]<=elapsed){
	if(t_asign[ejecutando]==0){
	   t_SO++;
	   textcolor(4);gotoxy(i,16);cprintf("Û");
	   inicio[ejecutando]=elapsed+1;
	   info(ejecutando,1);
	   cprintf("%d",inicio[ejecutando]);
	   t_espera[ejecutando]=inicio[ejecutando]-process[ejecutando];
	   info(ejecutando,2);
	   cprintf("%d",t_espera[ejecutando]);
	}else{
	   if(t_rest[ejecutando]>0){
	      elapsed_cuanto++;
	      if(elapsed_cuanto>cuanto){
		 PoneEnCola(ejecutando,Procesos);
		 ejecutando=ValorEnTope(Procesos);
		 QuitaDeCola(Procesos);
		 elapsed_cuanto=0;
		 textcolor(4);gotoxy(i,16);cprintf("Û");
		 t_SO++;
		 antiBug=1;
	      }else{
		 t_rest[ejecutando]--;
		 switch(ejecutando){
		    case 0:{textcolor(1);gotoxy(i,22);cprintf("Û");
			    textcolor(7);gotoxy(33,5);cprintf("%d",t_asign[ejecutando]);
			    gotoxy(42,5);cprintf("%d ",t_rest[ejecutando]);
			   }break;
		    case 1:{textcolor(2);gotoxy(i,21);cprintf("Û");
			    textcolor(7);gotoxy(33,7);cprintf("%d",t_asign[ejecutando]);
			    gotoxy(42,7);cprintf("%d ",t_rest[ejecutando]);
			   }break;
		    case 2:{textcolor(5);gotoxy(i,20);cprintf("Û");
			    textcolor(7);gotoxy(33,9);cprintf("%d",t_asign[ejecutando]);
			    gotoxy(42,9);cprintf("%d ",t_rest[ejecutando]);
			   }break;
		    case 3:{textcolor(6);gotoxy(i,19);cprintf("Û");
			    textcolor(7);gotoxy(33,11);cprintf("%d",t_asign[ejecutando]);
			    gotoxy(42,11);cprintf("%d ",t_rest[ejecutando]);
			   }break;
		    case 4:{textcolor(3);gotoxy(i,18);cprintf("Û");
			    textcolor(7);gotoxy(33,13);cprintf("%d",t_asign[ejecutando]);
			    gotoxy(42,13);cprintf("%d ",t_rest[ejecutando]);
			   }break;
		    default:textcolor(7);
		 }
	      }
	   }
	 }
	if(antiBug==0)
	   t_asign[ejecutando]++;
     }else{
	textcolor(0);gotoxy(i,17);cprintf("Û");
      }
     //--------------------Fin de la seccion----------------------
     //þþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþþ

     if(t_asign[ejecutando]>duracion[ejecutando]){
	ejecutando=ValorEnTope(Procesos);
	QuitaDeCola(Procesos);
     }
     elapsed++;
     i++;
     antiBug=0;

     sound(100);
     delay(50);
     nosound();
     delay(450);
   }while(ejecutando!=valor_error&&i<80);

   if(i==80){
      textcolor(4);
      gotoxy(21,9);cprintf("                                          ");
      gotoxy(21,10);cprintf("   NO SE PUDO TERMINAR CON LA ANIMACION   ");
      gotoxy(21,11);cprintf("       FUERA DEL RANGO DEL MONITOR        ");
      gotoxy(21,12);cprintf("                                          ");
   }else{
       textcolor(6);
       gotoxy(64,9);cprintf("%.2f",prom_espera(t_espera));
       gotoxy(64,13);cprintf("%.2f%",tiempoSO(t_SO,duracion));
    }
   getch();
}