//Carlos Fco. Camacho Uribe
//Taller de Sistemas Operativos
//Practica 02
#include<stdio.h>
#include<conio.h>
#include<dos.h>
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
	 gotoxy(4,y);cprintf("�");
	 gotoxy(61,y);cprintf("�");
      }else{
	 gotoxy(4,y);cprintf("�");
	 gotoxy(12,y);cprintf("�");
	 gotoxy(20,y);cprintf("�");
	 gotoxy(29,y);cprintf("�");
	 gotoxy(38,y);cprintf("�");
	 gotoxy(47,y);cprintf("�");
	 gotoxy(54,y);cprintf("�");
	 gotoxy(61,y);cprintf("�");
       }
   }
   for(x=5;x<61;x++){
      if(x==12||x==20||x==29||x==38||x==47||x==54){
	 gotoxy(x,1);cprintf("�");
	 gotoxy(x,4);cprintf("�");
	 gotoxy(x,6);cprintf("�");
	 gotoxy(x,8);cprintf("�");
	 gotoxy(x,10);cprintf("�");
	 gotoxy(x,12);cprintf("�");
	 gotoxy(x,14);cprintf("�");
      }else{
	 gotoxy(x,1);cprintf("�");
	 gotoxy(x,4);cprintf("�");
	 gotoxy(x,6);cprintf("�");
	 gotoxy(x,8);cprintf("�");
	 gotoxy(x,10);cprintf("�");
	 gotoxy(x,12);cprintf("�");
	 gotoxy(x,14);cprintf("�");
      }
   }
   gotoxy(4,1);cprintf("�");
   gotoxy(61,1);cprintf("�");
   gotoxy(4,14);cprintf("�");
   gotoxy(61,14);cprintf("�");
}

void ejes(){
   int i,j;
   textcolor(6);
   for(i=16;i<=25;i++){
      gotoxy(5,i);cprintf("�");
   }
   for(j=1;j<81;j++){
      gotoxy(j,23);cprintf("�");
   }
   gotoxy(5,23);cprintf("�");
   textcolor(7);
   for(j=16;j<23;j++)
      for(i=6;i<81;i++){
	 gotoxy(i,j);
	 cprintf("�");
      }
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

   gotoxy(1,16);cprintf("S.O.");
   gotoxy(1,17);cprintf("NULO");
   gotoxy(4,18);cprintf("E");
   gotoxy(4,19);cprintf("D");
   gotoxy(4,20);cprintf("C");
   gotoxy(4,21);cprintf("B");
   gotoxy(4,22);cprintf("A");
}

/*--------------------------MAIN----------------------------*/
void main(){
   int org[5][2]={{0,0},{1,0},{2,0},{3,0},{4,0}};
   int duracion[5],t_llego[5],t_asign[5]={0,0,0,0,0};
   int t_rest[5],inicio[5],t_espera[5],proceso=0;
   int i,t;
   clrscr();
   tabla();
   ejes();
   texto();
   //----------Captura los datos-------------
   //Captura de llegadas
   textcolor(7);

   gotoxy(16,5);
   scanf("%d",&t_llego[0]);
   org[0][1]=t_llego[0];

   gotoxy(16,7);
   scanf("%d",&t_llego[1]);
   org[1][1]=t_llego[1];

   gotoxy(16,9);
   scanf("%d",&t_llego[2]);
   org[2][1]=t_llego[2];

   gotoxy(16,11);
   scanf("%d",&t_llego[3]);
   org[3][1]=t_llego[3];

   gotoxy(16,13);
   scanf("%d",&t_llego[4]);
   org[4][1]=t_llego[4];
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
   //---------Inicia representacion----------
   i=6;
   do{
     textcolor(3);
     gotoxy(i,16);cprintf("�");
     gotoxy(i,17);cprintf("�");
     gotoxy(i,18);cprintf("�");
     gotoxy(i,19);cprintf("�");
     gotoxy(i,20);cprintf("�");
     gotoxy(i,21);cprintf("�");
     gotoxy(i,22);cprintf("�");
     textcolor(4);
     gotoxy(i,24);
     gotoxy(i,25);
     i++;
     if(t_asign>duracion)
	proceso++;
     delay(500);
   }while(proceso<5&&i<75);

   /*//temporal
   clrscr();
   for(i=0;i<5;i++)
      printf("\n\t%d-%d",org[i][0]+1,org[i][1]);
   burbuja(org);
   printf("\n");
   for(int j=0;j<5;j++)
      printf("\n\t%d-%d",org[j][0]+1,org[j][1]);
   //fin temporal*/

   getch();
}
/*Al estar programando esto me di cuenta de algunos errores
que tienen internamente las funciones cprintf y cscanf por
lo que he aprendido a usarlas con mayor discreci�n*/