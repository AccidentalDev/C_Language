#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<a:arbol.h>


void main(){

  char *arch="a:/disco.txt", *ind="a:/indice.txt";
  reg cd, aux;
  idx ndc;
  FILE *pf, *pif;
  int nreg, opc;
  Nodo arbol, ar_aux;
  inicializa(arbol);
  inicializa(ar_aux);

  if((pf = fopen(arch,"r+"))==0)     //ABRE ARCHIVO DE DATOS
    printf("ERROR");

  fread(&cd, sizeof(cd), 1, pf);
  nreg = cd.cod;                     //GUARDA EL NUMERO DE REGISTROS
  //printf("%d", nreg);
  getch();
    if(nreg != 0){
      if((pif = fopen(ind,"r"))==0)  //ABRE ARCHIVO INDICE
	printf("ERROR");
      while(!feof(pif)){
	fread(&ndc, sizeof(ndc), 1, pif);    //CARGA ARBOL
	insertar(ndc.nrr, ndc.llave, arbol);
      }
      //enorden1(arbol);
      getch();
      fclose(pif);
   }

  do{
    clrscr();
    printf("\n\t\t REGISTROS DE LONGITUD FIJA \n\n");
    printf("\n\t 1. AGREGAR \n\t 2. CONSULTAR \n\t 3. MODIFICAR \n\t 4. ELIMINAR \n\t 5. LISTAR \n\t 6. SALIR \n");
    printf("\n\t OPCION - ");
    scanf("%d", &opc);
    fflush(stdin);

    switch(opc){
      case 1:clrscr();
	     printf("\n\t\t AGREGAR REGISTRO \n");

	     printf("\n\t CODIGO - ");
	     scanf("%d", &cd.cod);
	     fflush(stdin);

	     printf("\n\t AUTOR - ");
	     gets(cd.autor);
	     fflush(stdin);

	     printf("\n\t DISCO - ");
	     gets(cd.disco);
	     fflush(stdin);

	     printf("\n\t PRECIO - ");
	     scanf("%f", &cd.precio);
	     fflush(stdin);

	     fseek(pf, 0L, SEEK_END);
	     fwrite(&cd, sizeof(cd), 1, pf);
	     nreg++;
	     insertar(nreg, cd.cod, arbol);
	     enorden1(arbol);

	     getch();


	     break;

      case 2:clrscr();
	     printf("\n\t\t CONSULTAR REGISTRO \n");

	     printf("\n\t CODIGO - ");
			 scanf("%d", &cd.cod);
			 fflush(stdin);
			 ar_aux=busca(cd.cod, arbol);
			 if(ar_aux!=NULL){
				 fseek(pf, ar_aux->nrr*sizeof(cd), SEEK_SET);
				 fread(&cd, sizeof(cd), 1, pf);
				 printf("\n\t AUTOR - %s \n\t DISCO - %s \n\t PRECIO - %f", cd.autor, cd.disco, cd.precio);
			 } else
		 printf("\n\t REGISTRO NO EXISTE \n");
			 getch();

			 break;

			case 3:clrscr();
			 printf("\n\t\t MODIFICAR REGISTRO \n");

			 printf("\n\t CODIGO - ");
			 scanf("%d", &cd.cod);
			 fflush(stdin);
			 ar_aux=busca(cd.cod, arbol);
			 if(ar_aux!=NULL){
				 fseek(pf, ar_aux->nrr*sizeof(cd), SEEK_SET);

				 printf("\n\t AUTOR - ");
				 gets(cd.autor);
				 fflush(stdin);

				 printf("\n\t DISCO - ");
				 gets(cd.disco);
				 fflush(stdin);

				 printf("\n\t PRECIO - ");
				 scanf("%d", &cd.precio);
				 fflush(stdin);

				 fwrite(&cd, sizeof(cd), 1, pf);
			 } else
		 printf("\n\t REGISTRO NO EXISTE \n");
			 getch();

			 break;

			case 4:clrscr();
			 printf("\n\t\t ELIMINAR REGISTRO \n");

			 printf("\n\t CODIGO - ");
			 scanf("%d", &cd.cod);
			 fflush(stdin);
			 ar_aux=busca(cd.cod, arbol);
			 Elimina(ar_aux, arbol);
			 nreg--;

			 break;

			case 5:clrscr();
			 printf("\n\t\t LISTAR \n");
			 enorden(pf, arbol);
			 getch();

			 break;

		}
	}while(opc != 6);

	cd.cod=nreg;
	strcpy(cd.autor, "autor");
	strcpy(cd.disco, "disco");
	cd.precio=0.0;

	fseek(pf, 0L, SEEK_SET);
  fwrite(&cd, sizeof(cd), 1, pf);        //ACTUALIZA NUMERO DE REGISTROS

  if((pif = fopen(ind,"w"))==0)
    printf("ERROR");
  actualiza(pif,arbol);           //ACTUALIZA ARCHIVO DE INDICE
  fclose(pf);
  fclose(pif);

  getch();
}
