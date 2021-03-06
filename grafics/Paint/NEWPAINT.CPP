//Carlos Francisco Camacho Uribe
//Taller de Graficas por Computadora
//Trabajo final: PAINT
#include<string.h>
#include<D:\install\TC\Prog\grafics\Paint\fbasicas.h>

int colorG=15,sel=6,tmpSel=6,sides=3;
char colorID[15]="Blanco",toolID[15]="Manos libres",IDtmp[15]="   ";

void botonPuntos(int x,int y,int col){
   pixel2(x,y,col);
   pixel2(x+1,y,col);
   pixel2(x,y+1,col);
   pixel2(x+1,y+1,col);
}
void botonLados(int numLados){
   cursor(2);
   for(int i=29;i<48;i++)
      for(int j=172;j<191;j++)
	 pixel2(i,j,15);
   switch(numLados){
      case 3:{botonPuntos(33,176,0);
	      botonPuntos(37,180,0);
	      botonPuntos(41,184,0);
	     }break;
      case 4:{botonPuntos(33,176,0);
	      botonPuntos(33,185,0);
	      botonPuntos(42,176,0);
	      botonPuntos(42,185,0);
	     }break;
      case 5:{botonPuntos(33,176,0);
	      botonPuntos(33,185,0);
	      botonPuntos(42,176,0);
	      botonPuntos(42,185,0);
	      botonPuntos(37,180,0);
	     }break;
      case 6:{botonPuntos(33,175,0);
	      botonPuntos(33,185,0);
	      botonPuntos(42,175,0);
	      botonPuntos(42,185,0);
	      botonPuntos(33,180,0);
	      botonPuntos(42,180,0);
	     }break;
      case 7:{botonPuntos(32,175,0);
	      botonPuntos(32,185,0);
	      botonPuntos(42,175,0);
	      botonPuntos(42,185,0);
	      botonPuntos(32,180,0);
	      botonPuntos(42,180,0);
	      botonPuntos(37,180,0);
	     }break;
      case 8:{botonPuntos(32,175,0);
	      botonPuntos(32,185,0);
	      botonPuntos(42,175,0);
	      botonPuntos(42,185,0);
	      botonPuntos(32,180,0);
	      botonPuntos(42,180,0);
	      botonPuntos(37,178,0);
	      botonPuntos(37,182,0);
	     }break;
      case 9:{botonPuntos(32,175,0);
	      botonPuntos(32,180,0);
	      botonPuntos(32,185,0);
	      botonPuntos(37,175,0);
	      botonPuntos(37,180,0);
	      botonPuntos(37,185,0);
	      botonPuntos(42,175,0);
	      botonPuntos(42,180,0);
	      botonPuntos(42,185,0);
	     }break;
   }
   cursor(1);
}
void layout(){
   int i,j,color=0;
   //Area de trabajo
   lineaB(56,20,56,424,15,1,0);
   lineaB(639,20,639,424,15,1,0);
   lineaB(56,424,639,424,15,1,0);
   lineaB(56,20,639,20,15,1,0);
   //rellenos
   for(i=29;i<48;i++)
      for(j=38;j<57;j++)
	 pixel2(i,j,7);//nuevo
   for(i=9;i<48;i++)
      for(j=58;j<77;j++)
	 pixel2(i,j,7);//abrir-guardar
   for(i=9;i<48;i++)
      for(j=92;j<191;j++)
	 pixel2(i,j,7);//herramientas
   //relleno barra de colores
   for(int a=74;a<233;a+=20)
      for(j=433;j<472;j++){
	 for(i=a;i<a+19;i++)
	    pixel2(i,j,color);
	 if(j==452||j==471)
	    color++;
      }
   //Lineas verticales de la barra de herramientas
   for(i=8;i<50;i+=20)
      lineaB(i,37,i,77,15,1,0);
   for(i=8;i<50;i+=20)
      lineaB(i,91,i,191,15,1,0);
   //lineas horizontales de la barra de herramientas
   for(i=37;i<80;i+=20)
      lineaB(8,i,48,i,15,1,0);
   for(i=91;i<195;i+=20)
      lineaB(8,i,48,i,15,1,0);
   //lineas horizontales de la barra de colores
   for(i=432;i<475;i+=20)
      lineaB(73,i,233,i,15,1,0);
   //lineas verticales de la barra de colores
   for(i=73;i<235;i+=20)
      lineaB(i,432,i,472,15,1,0);
   //letra X
   lineaB(15,42,21,52,4,1,0);
   lineaB(15,52,21,42,4,1,0);

   //-----Boton Nuevo-----
   //relleno
   for(i=34;i<42;i++)
      for(j=42;j<52;j++)
	 pixel2(i,j,15);
   //lineas horizontales
   lineaB(33,41,40,41,0,1,0);
   lineaB(33,53,43,53,0,1,0);
   //lineas verticales
   lineaB(33,41,33,53,0,1,0);
   lineaB(43,44,43,53,0,1,0);
   //detalles
   pixel2(40,42,0);
   pixel2(40,43,0);
   pixel2(40,44,0);
   pixel2(41,44,0);
   pixel2(42,44,0);
   pixel2(41,42,0);
   pixel2(42,43,0);
   //-----Boton Abrir-----
   lineaB(11,65,11,72,0,1,0);
   //lineas horizontales
   lineaB(12,73,20,73,0,1,0);
   lineaB(17,68,25,68,0,1,0);
   lineaB(15,65,21,65,0,1,0);
   //lineas diagonales
   lineaB(11,73,16,68,0,1,0);
   lineaB(21,73,26,68,0,1,0);
   //detalles
   pixel2(12,64,0);
   pixel2(13,64,0);
   pixel2(14,64,0);
   pixel2(21,66,0);
   pixel2(21,67,0);
   //flecha
   pixel2(19,62,0);
   pixel2(20,61,0);
   pixel2(21,61,0);
   pixel2(22,61,0);
   pixel2(23,62,0);
   pixel2(24,63,0);
   pixel2(25,64,0);
   pixel2(24,64,0);
   pixel2(23,64,0);
   pixel2(25,63,0);
   pixel2(25,62,0);
   //relleno1
   lineaB(12,65,12,71,14,1,0);
   lineaB(13,65,13,70,14,1,0);
   lineaB(14,65,14,69,14,1,0);
   lineaB(15,66,20,66,14,1,0);
   lineaB(15,67,20,67,14,1,0);
   pixel2(15,68,14);
   //relleno2
   lineaB(16,69,24,69,6,1,0);
   lineaB(15,70,23,70,6,1,0);
   lineaB(14,71,22,71,6,1,0);
   lineaB(13,72,21,72,6,1,0);
   //-----Boton Guardar-----
   //lineas horizontales
   lineaB(31,61,44,61,0,1,0);
   lineaB(32,74,44,74,0,1,0);
   lineaB(34,68,41,68,0,1,0);
   lineaB(35,70,41,70,0,1,0);
   //lineas verticales
   lineaB(31,62,31,73,0,1,0);
   lineaB(44,62,44,73,0,1,0);
   lineaB(33,62,33,67,0,1,0);
   lineaB(42,62,42,67,0,1,0);
   lineaB(34,70,34,73,0,1,0);
   lineaB(42,70,42,73,0,1,0);
   pixel2(43,63,0);
   //rellenos
   lineaB(35,71,39,71,0,1,0);
   lineaB(35,72,39,72,0,1,0);
   lineaB(35,73,39,73,0,1,0);
   lineaB(32,62,32,73,2,1,0);
   lineaB(33,68,33,73,2,1,0);
   lineaB(43,64,43,73,2,1,0);
   lineaB(34,69,42,69,2,1,0);
   pixel2(42,68,8);
   //-----Boton linea-----
   lineaB(13,96,23,106,0,1,0);
   //----Boton circulo----
   lineaB(16,116,20,116,0,1,0);
   lineaB(16,126,20,126,0,1,0);
   lineaB(13,119,13,123,0,1,0);
   lineaB(23,119,23,123,0,1,0);
   i=18;j=121;
   pixel2(i+4,j+3,0);
   pixel2(i-4,j+3,0);
   pixel2(i+4,j-3,0);
   pixel2(i-4,j-3,0);
   pixel2(i+3,j+4,0);
   pixel2(i-3,j+4,0);
   pixel2(i+3,j-4,0);
   pixel2(i-3,j-4,0);
   //-----Boton elipse----
   lineaB(16,137,20,137,0,1,0);
   lineaB(16,145,20,145,0,1,0);
   lineaB(12,140,12,142,0,1,0);
   lineaB(24,140,24,142,0,1,0);
   i=18;j=141;
   pixel2(i+3,j+3,0);
   pixel2(i-3,j+3,0);
   pixel2(i+3,j-3,0);
   pixel2(i-3,j-3,0);

   pixel2(i+4,j+3,0);
   pixel2(i-4,j+3,0);
   pixel2(i+4,j-3,0);
   pixel2(i-4,j-3,0);

   pixel2(i+5,j+2,0);
   pixel2(i-5,j+2,0);
   pixel2(i+5,j-2,0);
   pixel2(i-5,j-2,0);
   //----Boton spline-----
   pixel2(11,161,0);
   pixel2(18,161,0);
   pixel2(25,161,0);
   lineaB(12,162,13,162,0,1,0);
   lineaB(16,162,17,162,0,1,0);
   lineaB(14,163,15,163,0,1,0);
   lineaB(19,160,20,160,0,1,0);
   lineaB(23,160,24,160,0,1,0);
   lineaB(21,159,22,159,0,1,0);
   //-----Boton polis-----
   lineaB(18,176,12,185,0,1,0);
   lineaB(18,176,24,185,0,1,0);
   lineaB(12,186,24,186,0,1,0);
   botonLados(3);
   //-----Boton lapiz-----
   lineaB(37,97,35,102,0,1,0);
   lineaB(42,95,38,104,0,1,0);
   lineaB(34,103,34,108,0,1,0);
   lineaB(37,104,35,107,0,1,0);
   lineaB(35,104,35,106,0,1,0);
   lineaB(38,95,38,97,0,1,0);
   lineaB(39,94,41,94,0,1,0);
   pixel2(37,105,0);
   pixel2(39,98,0);
   pixel2(40,98,0);
   //relleno
   lineaB(38,98,35,103,14,1,0);
   lineaB(38,99,36,104,14,1,0);
   lineaB(39,95,41,95,4,1,0);
   lineaB(39,96,41,96,4,1,0);
   lineaB(39,97,40,97,4,1,0);
   //----Boton borrador---
   lineaB(37,117,32,122,0,1,0);
   lineaB(44,117,39,122,0,1,0);
   lineaB(44,120,39,125,0,1,0);
   lineaB(38,116,43,116,0,1,0);
   lineaB(32,126,37,126,0,1,0);
   lineaB(31,123,31,125,0,1,0);
   lineaB(38,123,38,126,0,1,0);
   lineaB(44,118,44,119,0,1,0);
   //relleno
   lineaB(32,123,37,123,6,1,0);
   lineaB(32,124,37,124,6,1,0);
   lineaB(32,125,37,125,6,1,0);
   lineaB(39,123,43,119,14,1,0);
   lineaB(39,124,43,120,14,1,0);
   for(i=33;i<39;i++)
      lineaB(i,122,i+5,117,14,1,0);
   //-----Boton spray-----
   lineaB(36,138,36,141,0,1,0);
   lineaB(38,137,40,137,0,1,0);
   lineaB(37,141,40,138,0,1,0);
   lineaB(37,142,41,138,0,1,0);
   lineaB(42,146,45,143,0,1,0);
   lineaB(38,143,41,146,0,1,0);
   lineaB(38,142,41,145,0,1,0);
   lineaB(39,142,42,145,0,1,0);
   lineaB(40,141,43,144,0,1,0);
   lineaB(42,139,45,142,0,1,0);
   lineaB(39,141,42,144,3,1,0);
   lineaB(40,140,43,143,3,1,0);
   lineaB(41,140,44,143,3,1,0);
   lineaB(41,139,44,142,3,1,0);
   lineaB(37,139,38,138,15,1,0);
   lineaB(37,140,39,138,15,1,0);
   pixel2(37,138,0);
   //spray
   pixel2(37,136,1);
   pixel2(34,136,1);
   pixel2(34,138,1);
   lineaB(35,137,37,137,1,1,0);
   for(j=138;j<149;j++){
      i=j%2;
      if(i==0)
	 pixel2(30,j,1);
   }
   for(j=137;j<148;j++){
      i=j%2;
      if(i!=0)
	 pixel2(31,j,1);
   }
   for(j=136;j<145;j++){
      i=j%2;
      if(i==0)
	 pixel2(32,j,1);
   }
   for(j=137;j<142;j++){
      i=j%2;
      if(i!=0)
	 pixel2(33,j,1);
   }
   //----Boton relleno----
   //liquido
   lineaB(30,160,30,165,0,1,0);
   lineaB(31,160,31,167,0,1,0);
   lineaB(32,162,32,168,0,1,0);
   lineaB(30,159,32,159,0,1,0);
   lineaB(31,158,33,158,0,1,0);
   lineaB(32,157,34,157,0,1,0);
   //bote
   lineaB(33,160,38,155,0,1,0);
   lineaB(36,164,42,158,0,1,0);
   lineaB(37,164,42,159,0,1,0);
   lineaB(37,165,43,159,0,1,0);
   lineaB(38,165,43,160,0,1,0);
   lineaB(38,166,44,160,0,1,0);
   lineaB(40,167,45,162,0,1,0);
   //detalles
   lineaB(33,161,34,161,0,1,0);
   lineaB(35,162,35,163,0,1,0);
   lineaB(39,155,39,156,0,1,0);
   lineaB(40,157,39,158,0,1,0);
   pixel2(36,161,0);
   pixel2(41,157,0);
   pixel2(39,167,0);
   pixel2(45,161,0);
   //relleno
   lineaB(39,166,44,161,3,1,0);
   lineaB(40,166,44,162,3,1,0);
   lineaB(35,159,40,159,3,1,0);
   lineaB(34,160,39,160,3,1,0);
   lineaB(37,161,38,161,3,1,0);
   lineaB(36,162,37,162,3,1,0);
   pixel2(35,161,3);
   pixel2(36,163,3);
}
void clicBoton(int px,int py){
   if((px>8&&py>37)&&(px<27&&py<57)){
      char dec='n';
      gotoxy(1,1);
      printf("�Salir del programa? (s/n)                                    ");
      dec=getch();
      fflush(stdin);
      if(dec=='s')
	 sel=1;
   }
   if((px>28&&py>37)&&(px<47&&py<57)){
      strcpy(IDtmp,toolID);
      strcpy(toolID,"Nuevo");
      tmpSel=sel;
      sel=2;
   }
   if((px>8&&py>57)&&(px<27&&py<77)){
      strcpy(IDtmp,toolID);
      strcpy(toolID,"Abrir");
      tmpSel=sel;
      sel=3;
   }
   if((px>28&&py>57)&&(px<47&&py<77)){
      strcpy(IDtmp,toolID);
      strcpy(toolID,"Guardar");
      tmpSel=sel;
      sel=4;
   }
   if((px>8&&py>78)&&(px<27&&py<91)){
      strcpy(toolID,"Pincel loco");
      sel=32;
   }
   if((px>8&&py>91)&&(px<27&&py<111)){
      strcpy(toolID,"Linea");
      sel=5;
   }
   if((px>28&&py>91)&&(px<47&&py<111)){
      strcpy(toolID,"Manos libres");
      sel=6;
   }
   if((px>8&&py>111)&&(px<27&&py<131)){
      strcpy(toolID,"Circulo");
      sel=7;
   }
   if((px>28&&py>111)&&(px<47&&py<131)){
      strcpy(toolID,"Borrador");
      /*strcpy(colorID,"Negro");
      colorG=0;*/
      sel=8;
   }
   if((px>8&&py>131)&&(px<27&&py<151)){
      strcpy(toolID,"Elipse");
      sel=9;
   }
   if((px>28&&py>131)&&(px<47&&py<151)){
      strcpy(toolID,"Spray");
      sel=10;
   }
   if((px>8&&py>151)&&(px<27&&py<171)){
      strcpy(toolID,"Spline");
      sel=11;
   }
   if((px>28&&py>151)&&(px<47&&py<171)){
      strcpy(toolID,"Relleno");
      sel=12;
   }
   if((px>8&&py>171)&&(px<27&&py<191)){
      strcpy(toolID,"Poligono");
      sel=13;
   }
   if((px>28&&py>171)&&(px<47&&py<191)){
      sides++;
      if(sides>9)
	 sides=3;
      botonLados(sides);
      delay(300);
   }
   //Seleccion de colores fila superior
   if((px>73&&py>432)&&(px<93&&py<452)){
      colorG=0;
      strcpy(colorID,"Negro");
   }
   if((px>93&&py>432)&&(px<113&&py<452)){
      colorG=2;
      strcpy(colorID,"Verde");
   }
   if((px>113&&py>432)&&(px<133&&py<452)){
      colorG=4;
      strcpy(colorID,"Rojo");
   }
   if((px>133&&py>432)&&(px<153&&py<452)){
      colorG=6;
      strcpy(colorID,"Cafe");
   }
   if((px>153&&py>432)&&(px<173&&py<452)){
      colorG=8;
      strcpy(colorID,"Gris oscuro");
   }
   if((px>173&&py>432)&&(px<193&&py<452)){
      colorG=10;
      strcpy(colorID,"Verde claro");
   }
   if((px>193&&py>432)&&(px<213&&py<452)){
      colorG=12;
      strcpy(colorID,"Naranja");
   }
   if((px>213&&py>432)&&(px<233&&py<452)){
      colorG=14;
      strcpy(colorID,"Amarillo");
   }
   //Seleccion de colores fila inferior
   if((px>73&&py>452)&&(px<93&&py<472)){
      colorG=1;
      strcpy(colorID,"Azul marino");
   }
   if((px>93&&py>452)&&(px<113&&py<472)){
      colorG=3;
      strcpy(colorID,"Azul");
   }
   if((px>113&&py>452)&&(px<133&&py<472)){
      colorG=5;
      strcpy(colorID,"Violeta");
   }
   if((px>133&&py>452)&&(px<153&&py<472)){
      colorG=7;
      strcpy(colorID,"Gris claro");
   }
   if((px>153&&py>452)&&(px<173&&py<472)){
      colorG=9;
      strcpy(colorID,"Morado");
   }
   if((px>173&&py>452)&&(px<193&&py<472)){
      colorG=11;
      strcpy(colorID,"Azul claro");
   }
   if((px>193&&py>452)&&(px<213&&py<472)){
      colorG=13;
      strcpy(colorID,"Rosa");
   }
   if((px>213&&py>452)&&(px<233&&py<472)){
      colorG=15;
      strcpy(colorID,"Blanco");
   }
}
char ruta[50]="         ";
void archivos(int uso){
   unsigned char temp;
   FILE *fd;
   if(uso==0){
      if((fd=fopen(ruta,"rb"))==NULL){
	 gotoxy(1,1);
	 printf("                                                              ");
	 gotoxy(1,1);
	 printf("Error al abrir el archivo");
	 getch();
      }else{
	 for(int a=57;a<639;a++)
	    for(int b=21;b<424;b++){
	       fread(&temp,sizeof(temp),1,fd);
	       pixel(a,b,temp);
	    }
	 fclose(fd);
      }
   }else{
      fd=fopen(ruta,"wb");
      if(fd==NULL){
	 gotoxy(1,1);
	 printf("                                                              ");
	 gotoxy(1,1);
	 printf("Error al crear el archivo");
	 getch();
      }else{
	 gotoxy(1,1);
	 printf("Guardando......                                               ");
	 for(int a=57;a<639;a++)
	    for(int b=21;b<424;b++){
	       temp=lee_pixel(a,b);
	       fwrite(&temp,sizeof(temp),1,fd);
	    }
	 fclose(fd);
      }
   }
}
void archivosMain(){
   char dec='s';
   cursor(2);
   switch(sel){
      //Abrir
      case 3:{if(strcmp(ruta,"         ")==0){
		  gotoxy(1,1);
		  printf("                                                              ");
		  gotoxy(1,1);
		  printf("Ruta y nombre: ");
		  scanf("%s",&ruta);
		  fflush(stdin);
	       }else{
		  gotoxy(1,1);
		  printf("                                                              ");
		  gotoxy(1,1);
		  printf("     �Abrir %s? (s/n)",ruta);
		  dec=getch();
		  fflush(stdin);
		  if(dec!='s'){
		     gotoxy(1,1);
		     printf("                                                              ");
		     gotoxy(1,1);
		     printf("Ruta y nombre: ");
		     scanf("%s",&ruta);
		     fflush(stdin);
		  }
	       }
	       gotoxy(1,1);
	       printf("Abriendo......                                                ");
	       archivos(0);
	      }break;
      //Guardar
      case 4:{gotoxy(1,1);
	       printf("                                                              ");
	       gotoxy(1,1);
	       printf("Ruta y nombre: ");
	       scanf("%s",&ruta);
	       fflush(stdin);
	       archivos(1);
	      }break;
      //Nuevo
      case 2:{for(int a=57;a<639;a++)
		  for(int b=21;b<424;b++)
		     pixel(a,b,0);
	      }break;
   }
   cursor(1);
}
void herramientas(){
   int xAct,yAct;
   int xAnt,yAnt;
   int xIni,yIni;
   switch(sel){
      case 5:{//Linea
	      xIni=x;
	      yIni=y;
	      xAct=xAnt=x;
	      yAct=yAnt=y;
	      lineaB(xIni,yIni,xAct,yAct,colorG,0,1);
	      while(lee_cursor(&x,&y,0x12)==1){
		 xAct=x;
		 yAct=y;
		 lineaB(xIni,yIni,xAnt,yAnt,colorG,2,1);
		 lineaB(xIni,yIni,xAct,yAct,colorG,0,1);
		 lineaB(xIni,yIni,xAct,yAct,colorG,1,1);
		 while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
		 xAnt=xAct;
		 yAnt=yAct;
	      }
	     }break;
      case 6:{//Manos libres
	      xAct=x;
	      yAct=y;
	      xAnt=x;
	      yAnt=y;
	      while(lee_cursor(&x,&y,0x12)==1){
		 xAct=x;
		 yAct=y;
		 lineaB(xAnt,yAnt,xAct,yAct,colorG,1,1);
		 while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
		 xAnt=xAct;
		 yAnt=yAct;
	      }
	     }break;
      case 7:{//Circulo
	      int rAnt,rAct;
	      xIni=x;yIni=y;
	      xAct=x;
	      yAct=y;
	      xAnt=x;
	      yAnt=y;
	      rAnt=sqrt(pow((xAnt-xIni),2)+pow((yAnt-yIni),2));
	      circulo(xIni,yIni,rAnt,colorG,0);
	      while(lee_cursor(&x,&y,0x12)==1){
		 xAct=x;
		 yAct=y;
		 rAct=sqrt(pow((xAct-xIni),2)+pow((yAct-yIni),2));
		 circulo(xIni,yIni,rAnt,colorG,2);//ant
		 circulo(xIni,yIni,rAct,colorG,0);//act
		 circulo(xIni,yIni,rAct,colorG,1);//act
		 while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
		 xAnt=xAct;
		 yAnt=yAct;
		 rAnt=sqrt(pow((xAnt-xIni),2)+pow((yAnt-yIni),2));
	      }
	     }break;
      case 8:{//Borrador
	      xAct=x;
	      yAct=y;
	      xAnt=x;
	      yAnt=y;
	      while(lee_cursor(&x,&y,0x12)==1){
		 xAct=x;
		 yAct=y;
		 lineaB(xAnt,yAnt,xAct,yAct,colorG,1,2);
		 while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
		 xAnt=xAct;
		 yAnt=yAct;
	      }
	     }break;
      case 9:{//Elipse
	      long rxAnt,rxAct,ryAnt,ryAct;
	      xIni=x;yIni=y;
	      xAct=x;
	      yAct=y;
	      xAnt=x;
	      yAnt=y;
	      rxAnt=abs(xIni-x);
	      ryAnt=abs(yIni-y);
	      elipse(xIni,yIni,rxAnt,ryAnt,colorG,0);
	      while(lee_cursor(&x,&y,0x12)==1){
		 xAct=x;
		 yAct=y;
		 rxAct=abs(xIni-xAct);
		 ryAct=abs(yIni-yAct);
		 elipse(xIni,yIni,rxAnt,ryAnt,colorG,2);//ant,2
		 elipse(xIni,yIni,rxAct,ryAct,colorG,0);//act,0
		 elipse(xIni,yIni,rxAct,ryAct,colorG,1);//act,1
		 while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
		 xAnt=xAct;
		 yAnt=yAct;
		 rxAnt=abs(xIni-xAnt);
		 ryAnt=abs(yIni-yAnt);
	      }
	     }break;
      case 10:{//Spray
	       xAct=x;
	       yAct=y;
	       xAnt=x;
	       yAnt=y;
	       while(lee_cursor(&x,&y,0x12)==1){
		  xAct=x;
		  yAct=y;
		  lineaB(xAnt,yAnt,xAct,yAct,colorG,1,3);
		  if(xAnt==xAct&&yAnt==yAct)
		     delay(50);
		  xAnt=xAct;
		  yAnt=yAct;
	       }
	      }break;
      case 11:{//Spline
	       int p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y;
	       int p1xn,p1yn,p2xn,p2yn,p3xn,p3yn;
	       int clicBan=0;
	       /*if(clicBan==-1)
		  clicBan=0;*/
	       while(clicBan!=-1){
		  if(lee_cursor(&x,&y,0x12)==1){
		     if(clicBan==2){
			clicBan=-1;
			curva(p0x,p0y,p1xn,p1yn,p3x,p3y,p3x,p3y,colorG,2);
			p2x=x,p2y=y;
			p2xn=x,p2yn=y;
			curva(p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y,colorG,0);
			while(lee_cursor(&x,&y,0x12)==1){
			   p2x=x;
			   p2y=y;
			   curva(p0x,p0y,p1x,p1y,p2xn,p2yn,p3x,p3y,colorG,2);
			   curva(p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y,colorG,0);
			   curva(p0x,p0y,p1x,p1y,p2x,p2y,p3x,p3y,colorG,1);
			   while(lee_cursor(&x,&y,0x12)==1&&p2x==x&&p2y==y);
			   p2xn=p2x;
			   p2yn=p2y;
			}
		     }
		     if(clicBan==1){
			clicBan=2;
			lineaB(p0x,p0y,p3xn,p3yn,colorG,2,1);
			p1x=x,p1y=y;
			p1xn=x,p1yn=y;
			curva(p0x,p0y,p1x,p1y,p3x,p3y,p3x,p3y,colorG,0);
			while(lee_cursor(&x,&y,0x12)==1){
			   p1x=x;
			   p1y=y;
			   curva(p0x,p0y,p1xn,p1yn,p3x,p3y,p3x,p3y,colorG,2);
			   curva(p0x,p0y,p1x,p1y,p3x,p3y,p3x,p3y,colorG,0);
			   curva(p0x,p0y,p1x,p1y,p3x,p3y,p3x,p3y,colorG,1);
			   while(lee_cursor(&x,&y,0x12)==1&&p1x==x&&p1y==y);
			   p1xn=p1x;
			   p1yn=p1y;
			}
		     }
		     if(clicBan==0){
			clicBan=1;
			p0x=x;p0y=y;
			p3x=x;p3y=y;
			p3xn=x;p3yn=y;
			lineaB(p0x,p0y,p3x,p3y,colorG,0,1);
			while(lee_cursor(&x,&y,0x12)==1){
			   p3x=x;
			   p3y=y;
			   lineaB(p0x,p0y,p3xn,p3yn,colorG,2,1);
			   lineaB(p0x,p0y,p3x,p3y,colorG,0,1);
			   lineaB(p0x,p0y,p3x,p3y,colorG,1,1);
			   while(lee_cursor(&x,&y,0x12)==1&&p3x==x&&p3y==y);
			   p3xn=p3x;
			   p3yn=p3y;
			}
		     }
		  }
	       }
	      }break;
      case 13:{//Poligono
	       int radio;
	       float radianes;
	       double dx,dy,angulo;
	       contG=0;
	       xIni=x;yIni=y;
	       radio=0;
	       while(lee_cursor(&x,&y,0X12)==1){
		  xAct=x;
		  yAct=y;
		  dx=xAct-xIni;
		  dy=yAct-yIni;
		  if(dx!=0||dy!=0){
		     radio=sqrt((dx*dx)+(dy*dy));
		     radianes=180/M_PI;
		     angulo=radianes*(atan2(dy,dx));
		     cursor(0x2);
		     for(int i=0;i<contG;i++)
			pixel(arrPoint[i].x,arrPoint[i].y,arrPoint[i].color);
		     contG=0;
		     cursor(0x1);
		     polys(xIni,yIni,radio,angulo,sides,colorG,0);//act
		     polys(xIni,yIni,radio,angulo,sides,colorG,1);//act
		     while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
		  }
	       }
	      }break;
      case 32:{//Pincel loco
	      xAct=x;
	      yAct=y;
	      xAnt=x;
	      yAnt=y;
	      while(lee_cursor(&x,&y,0x12)==1){
		 xAct=x;
		 yAct=y;
		 lineaB(xAnt,yAnt,xAct,yAct,colorG,1,32);
		 while(lee_cursor(&x,&y,0x12)==1&&xAct==x&&yAct==y);
		 xAnt=xAct;
		 yAnt=yAct;
	      }
	     }break;
   }
}
/******************************-M-A-I-N-******************************/
void main(){
 int xx,yy;
 clrscr();
 modo(0x4);
 modo(0x12);
 cursor(0);
 cursor(1);
 layout();
 do{
    gotoxy(1,1);
    printf("Herramienta: %s          Color: %s               ",toolID,colorID);
    if(sel>1&&sel<5){
       archivosMain();
       sel=tmpSel;
       strcpy(toolID,IDtmp);
    }
    if(lee_cursor(&x,&y,0x12)==1){
       xx=x;yy=y;
       if((xx>56&&yy>20)&&(xx<640&&yy<424)){
	  herramientas();
       }else{
	  clicBoton(xx,yy);
       }
    }
 }while(sel!=1&&!kbhit());
 modo(0x3);
}