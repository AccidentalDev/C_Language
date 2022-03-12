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
      for(int i=0;i<lenght;i+=20){
	 fprintf(archivo,"%d,%d,%d,%d,%d,",lst[i],lst[i+1],lst[i+2],lst[i+3],lst[i+4]);
	 fprintf(archivo,"%d,%d,%d,%d,%d,",lst[i+5],lst[i+6],lst[i+7],lst[i+8],lst[i+9]);
	 fprintf(archivo,"%d,%d,%d,%d,%d,",lst[i+10],lst[i+11],lst[i+12],lst[i+13],lst[i+14]);
	 fprintf(archivo,"%d,%d,%d,%d,%d\n",lst[i+15],lst[i+16],lst[i+17],lst[i+18],lst[i+19]);
      }
      fclose(archivo);
      printf("\n\tArchivo %s creado con exito",name);
   }
}
void listas(){
   int a1[1000],t=1000;
   generaDatos(a1,t,1);
   guardaLista(a1,t,"1000_up.txt\0");
   generaDatos(a1,t,2);
   guardaLista(a1,t,"1000_dwn.txt");
   generaDatos(a1,t,3);//1
   guardaLista(a1,t,"1000_rd1.txt");
   generaDatos(a1,t,3);//2
   guardaLista(a1,t,"1000_rd2.txt");
   generaDatos(a1,t,3);//3
   guardaLista(a1,t,"1000_rd3.txt");
   generaDatos(a1,t,3);//4
   guardaLista(a1,t,"1000_rd4.txt");
   generaDatos(a1,t,3);//5
   guardaLista(a1,t,"1000_rd5.txt");
   generaDatos(a1,t,3);//6
   guardaLista(a1,t,"1000_rd6.txt");
   generaDatos(a1,t,3);//7
   guardaLista(a1,t,"1000_rd7.txt");
   generaDatos(a1,t,3);//8
   guardaLista(a1,t,"1000_rd8.txt");
   generaDatos(a1,t,3);//9
   guardaLista(a1,t,"1000_rd9.txt");
   generaDatos(a1,t,3);//10
   guardaLista(a1,t,"1000_rd0.txt");
   /*
   int a3[100];
   int a4[1000];
   int a5[10000];
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