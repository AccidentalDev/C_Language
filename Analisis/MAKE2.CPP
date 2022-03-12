//Carlos Fco. Camacho Uribe
//Analisis y dise¤o de algoritmos

/*Creacion de las diferentes listas para
guardarlas en archivos*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void generaDatos(int arr[],int n,int s){
   int i,rand,temp=1;
   if(s==2)
      for(i=n-1;i>=0;i--){
	 arr[i]=temp;
	 temp++;
      }
   else
      for(i=0;i<n;i++)
	 arr[i]=i+1;

   if(s==3){
      //randomize();
      for(i=0;i<n;i++){
	 rand=random(n);
	 temp=arr[rand];
	 arr[rand]=arr[i];
	 arr[i]=temp;
      }
   }
}
void guardaLista(int lst[],int lenght,char *name){
   FILE *archivo;
   char path[60];
   strcpy(path,"C:/TC/Prog/Analisis/lists/\0");
   strcat(path,name);
   //strcat(path,".txt");
   if((archivo=fopen(path,"w"))==0){
      fflush(archivo);
      cprintf("\n\r\tError al crear el archivo\n\r\t");
      getch();
   }else{
      for(int i=0;i<lenght;i+=5){
	 fprintf(archivo,"%d,%d,%d,%d,%d\n",lst[i],lst[i+1],lst[i+2],lst[i+3],lst[i+4]);
      }
      fclose(archivo);
      printf("\n\tArchivo %s creado con exito",name);
   }
}
void listas(){
   int a1[5],t=5;
   generaDatos(a1,t,1);
   guardaLista(a1,t,"5_up.txt\0");
   generaDatos(a1,t,2);
   guardaLista(a1,t,"5_down.txt");
   generaDatos(a1,t,3);//1
   guardaLista(a1,t,"5_rand1.txt");
   generaDatos(a1,t,3);//2
   guardaLista(a1,t,"5_rand2.txt");
   generaDatos(a1,t,3);//3
   guardaLista(a1,t,"5_rand3.txt");
   generaDatos(a1,t,3);//4
   guardaLista(a1,t,"5_rand4.txt");
   generaDatos(a1,t,3);//5
   guardaLista(a1,t,"5_rand5.txt");
   generaDatos(a1,t,3);//6
   guardaLista(a1,t,"5_rand6.txt");
   generaDatos(a1,t,3);//7
   guardaLista(a1,t,"5_rand7.txt");
   generaDatos(a1,t,3);//8
   guardaLista(a1,t,"5_rand8.txt");
   generaDatos(a1,t,3);//9
   guardaLista(a1,t,"5_rand9.txt");
   generaDatos(a1,t,3);//10
   guardaLista(a1,t,"5_rand10.txt");
   /*
   int a2[10];
   generaDatos(a2,t,1);
   guardaLista(a2,t,"list10_up");
   generaDatos(a2,t,2);
   guardaLista(a2,t,"list10_down");
   generaDatos(a2,t,3);//1
   guardaLista(a2,t,"list10_rand1");
   generaDatos(a2,t,3);//2
   guardaLista(a2,t,"list10_rand2");
   generaDatos(a2,t,3);//3
   guardaLista(a2,t,"list10_rand3");
   generaDatos(a2,t,3);//4
   guardaLista(a2,t,"list10_rand4");
   generaDatos(a2,t,3);//5
   guardaLista(a2,t,"list10_rand5");
   generaDatos(a2,t,3);//6
   guardaLista(a2,t,"list10_rand6");
   generaDatos(a2,t,3);//7
   guardaLista(a2,t,"list10_rand7");
   generaDatos(a2,t,3);//8
   guardaLista(a2,t,"list10_rand8");
   generaDatos(a2,t,3);//9
   guardaLista(a2,t,"list10_rand9");
   generaDatos(a2,t,3);//10
   guardaLista(a2,t,"list10_rand10");

   int a3[100];
   generaDatos(a3,t,1);
   guardaLista(a3,t,"list100_up");
   generaDatos(a3,t,2);
   guardaLista(a3,t,"list100_down");
   generaDatos(a3,t,3);//1
   guardaLista(a3,t,"list100_rand1");
   generaDatos(a3,t,3);//2
   guardaLista(a3,t,"list100_rand2");
   generaDatos(a3,t,3);//3
   guardaLista(a3,t,"list100_rand3");
   generaDatos(a3,t,3);//4
   guardaLista(a3,t,"list100_rand4");
   generaDatos(a3,t,3);//5
   guardaLista(a3,t,"list100_rand5");
   generaDatos(a3,t,3);//6
   guardaLista(a3,t,"list100_rand6");
   generaDatos(a3,t,3);//7
   guardaLista(a3,t,"list100_rand7");
   generaDatos(a3,t,3);//8
   guardaLista(a3,t,"list100_rand8");
   generaDatos(a3,t,3);//9
   guardaLista(a3,t,"list100_rand9");
   generaDatos(a3,t,3);//10
   guardaLista(a3,t,"list100_rand10");

   int a4[1000];
   generaDatos(a4,t,1);
   guardaLista(a4,t,"list1000_up");
   generaDatos(a4,t,2);
   guardaLista(a4,t,"list1000_down");
   generaDatos(a4,t,3);//1
   guardaLista(a4,t,"list1000_rand1");
   generaDatos(a4,t,3);//2
   guardaLista(a4,t,"list1000_rand2");
   generaDatos(a4,t,3);//3
   guardaLista(a4,t,"list1000_rand3");
   generaDatos(a4,t,3);//4
   guardaLista(a4,t,"list1000_rand4");
   generaDatos(a4,t,3);//5
   guardaLista(a4,t,"list1000_rand5");
   generaDatos(a4,t,3);//6
   guardaLista(a4,t,"list1000_rand6");
   generaDatos(a4,t,3);//7
   guardaLista(a4,t,"list1000_rand7");
   generaDatos(a4,t,3);//8
   guardaLista(a4,t,"list1000_rand8");
   generaDatos(a4,t,3);//9
   guardaLista(a4,t,"list1000_rand9");
   generaDatos(a4,t,3);//10
   guardaLista(a4,t,"list1000_rand10");

   int a5[10000];
   generaDatos(a5,t,1);
   guardaLista(a5,t,"list10000_up");
   generaDatos(a5,t,2);
   guardaLista(a5,t,"list10000_down");
   generaDatos(a5,t,3);//1
   guardaLista(a5,t,"list10000_rand1");
   generaDatos(a5,t,3);//2
   guardaLista(a5,t,"list10000_rand2");
   generaDatos(a5,t,3);//3
   guardaLista(a5,t,"list10000_rand3");
   generaDatos(a5,t,3);//4
   guardaLista(a5,t,"list10000_rand4");
   generaDatos(a5,t,3);//5
   guardaLista(a5,t,"list10000_rand5");
   generaDatos(a5,t,3);//6
   guardaLista(a5,t,"list10000_rand6");
   generaDatos(a5,t,3);//7
   guardaLista(a5,t,"list10000_rand7");
   generaDatos(a5,t,3);//8
   guardaLista(a5,t,"list10000_rand8");
   generaDatos(a5,t,3);//9
   guardaLista(a5,t,"list10000_rand9");
   generaDatos(a5,t,3);//10
   guardaLista(a5,t,"list10000_rand10");
   */
}
/*-----------------------------M-A-I-N----------------------------*/
void main(){
 //long tamanyo=5;
 char op;
 do{
   clrscr();
   printf("\n\tCreacion de listas de diferente orden y tama¤o\n\t");
   printf("\n\tSe generaran 12 listas del mismo tama¤o y de las formas siguientes:");
   printf("\n\t1 lista ascendentemente ordenada");
   printf("\n\t1 lista descendentemente ordenada");
   printf("\n\t10 listas desordenadas\n\t");
   /*printf("\n\n\tEscribe el tama¤o de las listas: ");
   scanf("%d",&tamanyo);*/
   randomize();
   listas();
   printf("\n\t¨Generar otras listas? (s/n): ");
   op=getch();
   fflush(stdin);
 }while(op!='n');
}