#include<stdio.h>
#include<conio.h>

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
   gotoxy(61,1);cprintf("¿");
   gotoxy(4,14);cprintf("À");
   gotoxy(61,14);cprintf("Ù");
}
void ejes(){
   textcolor(7);
   for(int i=16;i<=25;i++)
      gotoxy(5,i);cprintf("³");
   for(int j=1;j<81;j++)
      gotoxy(j,23);cprintf("Ä");
}
void main(){
  clrscr();
  tabla();
  ejes();
  getch();
}