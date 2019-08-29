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
	TipoComplejo num;
	printf("Ingresa la parte Real\n");
	scanf(" %f", &num.Real);
	printf("Ingresa la parte Imaginaria\n");
	scanf(" %f", &num.Imaginario);
	printf("El número es: %.3f%+.3fi\n",num.Real,num.Imaginario);
}
