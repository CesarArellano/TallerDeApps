#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct def_Lista
{
	int numero;
	struct def_Lista *sig;

}TipoLista;

void Modificar(double *v1,double *v2);
void CopiarArray(char Arreglo[], char Arreglo2[]);
void AgregarNodo(TipoLista **Inicio); 
void ImprimirLista(TipoLista *Inicio);
void BorrarLista(TipoLista *Inicio);

int main(void)
{
	TipoLista *Lista=NULL; 
	int op;
	double n1=0,n2=0;
	char Array[100],Array2[100],letra;
	do{
		system("clear");
		printf("Menú\n");
		printf("1.- Modificar 2 variables.\n");
		printf("2.- Copiar Array a otro.\n");
		printf("3.- Generar un nodo en una lista dinámica.\n");
		printf("4.- Salir\n");
		printf("¿Qué desea hacer?\n");
		scanf(" %d",&op);
		switch(op)
		{
			case 1:
			Modificar(&n1,&n2);
			printf("Valor 1: %f\nValor 2: %f\n",n1,n2);
			break;
			case 2:
			CopiarArray(Array,Array2);
			break;
			case 3:
			AgregarNodo(&Lista);
			ImprimirLista(Lista);
			break;
			case 4:
			BorrarLista(Lista);
			system("clear");
			printf("Saliendo del programa\n");
			break;
			default:
			printf("Opción invalida,intente de nuevo");
			break;
		}
		printf("Presione una letra para continuar\n");
		scanf(" %c",&letra);
			}while(op!=4);
}

void Modificar(double *v1,double *v2)
{
	*v1 = 3;
	*v2 = 5;
}
void CopiarArray(char Arreglo[], char Arreglo2[])
{
	int i;
	printf("Escriba la frase\n");
	scanf(" %[^\n]",Arreglo);
	for(i=0;i<strlen(Arreglo);i++)
		Arreglo2[i]=Arreglo[i];
	Arreglo2[i]='\0';
	printf("Se ha copiado con éxito\nFrase:%s\n",Arreglo2);
}
void AgregarNodo(TipoLista **Inicio)
{
	TipoLista *temp,*temp2;
	int numero;
	printf("Escribe un numero para agregar un nuevo nodo\n");
	scanf(" %d",&numero);
	temp=(TipoLista *)malloc(sizeof(TipoLista));
	temp->numero=numero;
	temp->sig=NULL;
	if(*Inicio!=NULL)
    {
      temp2=*Inicio;
      while(temp2->sig!=NULL)
		temp2=temp2->sig;
      temp2->sig=temp;
    }
  	else
    	*Inicio=temp;
	printf("El elemento se añadió con éxito\n");
}
void ImprimirLista(TipoLista *Inicio)
{
	TipoLista *temp;
	temp= Inicio;
	while(temp!=NULL)
	{
		printf("%d\n",temp->numero);
		temp=temp->sig;
	}
}
void BorrarLista(TipoLista *Inicio)
{
  TipoLista *temp;
  temp=Inicio;
  while(temp!=NULL)
    {
      Inicio=Inicio->sig;
      free(temp);
      temp=Inicio;
    }
}