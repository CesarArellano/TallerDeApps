#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int Tam, *Stock,i;
	printf("Ingrese el tamaño del arreglo: ");
  	scanf("%d",&Tam);
  	Stock=(int *)malloc(sizeof(int)*Tam);
  	for(i=0; i<Tam; i++)
    	Stock[i]= i+1;
  	for(i=0; i<Tam; i++)
    	printf("Stock [%d]: %d\n",i+1, Stock[i]);
  	free(Stock);
}
