#include<stdio.h>
#include<conio.h>

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
   textcolor(7);
   for(int i=16;i<=25;i++)
      gotoxy(5,i);cprintf("�");
   for(int j=1;j<81;j++)
      gotoxy(j,23);cprintf("�");
}
void main(){
  clrscr();
  tabla();
  ejes();
  getch();
}