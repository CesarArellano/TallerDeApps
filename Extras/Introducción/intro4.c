#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct def_Complejo
{
	float Real;
	float Imaginario;
}TipoComplejo;

int main(void)
{
	int Tam,i;
	TipoComplejo *Array;
	printf("Ingrese el tamaño del arreglo de números complejos\n");
  	scanf("%d",&Tam);
  	Array=(TipoComplejo *)malloc(sizeof(TipoComplejo)*Tam);
  	free(Array);
  	printf("Se creón el arreglo.\n");
}
