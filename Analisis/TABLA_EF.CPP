//Carlos Francisco Camacho Uribe
//Metodos de Ordenamiento
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void BubbleSort(int a[],int n,long &com,long &m){
   int i,z,c;
   com=0;m=0;
   for(c=1;c<n;c++)
      for(i=0;i<(n-1);i++){
	 com++;
	 if(a[i]>a[i+1]){
	    z=a[i];
	    a[i]=a[i+1];
	    a[i+1]=z;
	    m++;
	    }
      }
}
void BurbujaMejorada(int arr[],int n,long &c,long &m){
   int ban=0,i,j,z;
   c=0;m=0;
   for(i=1;(i<n)&&(ban==0);i++){
      ban=1;
      for(j=0;j<(n-1);j++){
	 c++;
	 if(arr[j]>arr[j+1]){
	    z=arr[j];
	    arr[j]=arr[j+1];
	    arr[j+1]=z;
	    m++;
	    ban=0;
	 }
      }
   }
}
void seleccionDirecta(int arr[],int n,long &c,long &m){
   int i,j,min,z;
   c=0;m=0;
   for(i=0;i<=n;i++){
      min=i;
      for(j=i+1;j<n;j++){
	 c++;
	 if(arr[j]<arr[min])
	    min=j;
      }
   z=arr[min];
   arr[min]=arr[i];
   arr[i]=z;
   m++;
   }
}
void shell(int arr[],int n,long &c,long &m){
   int salto,i,j,k,z;
   c=0;m=0;
   salto=n/2;
   while(salto>0){
      for(i=salto;i<n;i++){
	 for(j=i-salto;j>=0;j-=salto){
	    k=j+salto;
	    c++;
	    if(arr[j]>arr[k]){
	       z=arr[j];
	       m++;
	       arr[j]=arr[k];
	       arr[k]=z;
	    }
	    else
	       j=-1;
	 }
      }
      salto=salto/2;
   }
}
void generaDatos(int arr[],int n){
   int i;
   randomize();
   for(i=0; i<n; ++i)
      arr[i]=random(30000)+1;
}
void copia(int arr[],int copy[],int n){
   int i;
   for(i=0;i<n;i++)
      copy[i]=arr[i];
}
void main(){
 int select,ar[200],car[200],b[1000],cb[1000],na=200,nb=1000;
 long c1a=0,m1a=0,c2a=0,m2a=0,c3a=0,m3a=0,c4a=0,m4a=0,c1b=0,m1b=0,c2b=0,m2b=0,c3b=0,m3b=0,c4b=0,m4b=0;
 clrscr();
 generaDatos(ar,na);
 generaDatos(b,nb);
 copia(ar,car,na);
 BubbleSort(car,na,c1a,m1a);
 copia(b,cb,nb);
 BubbleSort(cb,nb,c1b,m1b);
 copia(ar,car,na);
 BurbujaMejorada(car,na,c2a,m2a);
 copia(b,cb,nb);
 BurbujaMejorada(cb,nb,c2b,m2b);
 copia(ar,car,na);
 seleccionDirecta(car,na,c3a,m3a);
 copia(b,cb,nb);
 seleccionDirecta(cb,nb,c3b,m3b);
 copia(ar,car,na);
 shell(car,na,c4a,m4a);
 copia(b,cb,nb);
 shell(cb,nb,c4b,m4b);
 cout<<"                 arr de 200      arr de 1000"<<endl;
 cout<<"Burbuja     comp     "<<c1a<<"           "<<c1b<<endl;
 cout<<"             mov     "<<m1a<<"            "<<m1b<<endl;
 cout<<endl;
 cout<<"Bmejorada   comp     "<<c2a<<"           "<<c2b<<endl;
 cout<<"             mov     "<<m2a<<"            "<<m2b<<endl;
 cout<<endl;
 cout<<"selDirecta  comp     "<<c3a<<"           "<<c3b<<endl;
 cout<<"             mov     "<<m3a<<"            "<<m3b<<endl;
 cout<<endl;
 cout<<"Shell       comp     "<<c4a<<"           "<<c4b<<endl;
 cout<<"             mov     "<<m4a<<"            "<<m4b<<endl;
 getch();
}