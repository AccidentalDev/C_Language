#include<stdio.h>
#include<conio.h>
void main(){
  int posx=1,i,j=10;
  clrscr();
  for(i=1;i<81;i++){
     cprintf("%d",posx);
     if(posx==0)
	posx=1;
     else
	if(posx==9)
	   posx=0;
	else
	   posx++;
  }
  posx=1;
  for(i=1;i<81;i++){
     if(i==j){
	cprintf("%d",posx);
	posx++;
	j=j+10;
     }else
	cprintf(" ");
  }
  for(i=2;i<26;i++){
     gotoxy(1,i);
     printf("%d",i);
  }
  getch();
}