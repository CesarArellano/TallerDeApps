#include <stdio.h>

void print();
void print2(int x);
int suma(int x, int y);

int main(int argc, char const *argv[])
{
	void (*funcion)();
	void (*funcion2)(int);
	int (*funcion3)(int,int);
	int Resultado;
	funcion = &print;
	funcion2 = &print2;
	funcion3 = &suma;
	funcion();
	Resultado = funcion3(10,10);
	funcion2(Resultado);
	return 0;
}

void print()
{
	printf("Hola Mundo\n");
}
void print2(int x)
{
	printf("El resultado: %d\n",x);
}
int suma(int x, int y)
{
	return x+y;
}
