#include <dos.h>
#include <stdio.h>
#include <conio.h>
void main(){
  clrscr();
  for(int i=400;i<501;i=i+10){
     printf("\n\n\tReproduciendo un sonido de %d Hz",i);
     sound(i);//500
     delay(800);
     clrscr();
  }
  nosound();
  printf("\n\tFin del programa");
  getch();
}