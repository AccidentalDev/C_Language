#include<stdio.h>
#include<conio.h>
void main(){
  int i;
  clrscr();
  for(i=14;i<38;i++)
     cprintf("%d=%c\r\n",i,i);
  window(9,1,15,25);
  for(i=38;i<62;i++)
     cprintf("%d=%c\r\n",i,i);
  window(17,1,27,25);
  for(i=62;i<86;i++)
     cprintf("%d=%c\r\n",i,i);
  window(25,1,36,25);
  for(i=86;i<110;i++)
     cprintf("%d=%c\r\n",i,i);
  window(33,1,45,25);
  for(i=110;i<134;i++)
     cprintf("%d=%c\r\n",i,i);
  window(41,1,54,25);
  for(i=134;i<158;i++)
     cprintf("%d=%c\r\n",i,i);
  window(49,1,63,25);
  for(i=158;i<182;i++)
     cprintf("%d=%c\r\n",i,i);
  window(57,1,72,25);
  for(i=182;i<206;i++)
     cprintf("%d=%c\r\n",i,i);
  window(65,1,79,25);
  for(i=206;i<230;i++)
     cprintf("%d=%c\r\n",i,i);
  window(73,1,80,25);
  for(i=230;i<254;i++)
     cprintf("%d=%c\r\n",i,i);
  getch();
  clrscr();
  for(i=254;i<255;i++)
     cprintf("%d=%c\r\n",i,i);
  for(i=1;i<14;i++)
     cprintf("%d=%c\r\n",i,i);
  getch();
}