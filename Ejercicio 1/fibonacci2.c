#include <stdio.h>
#include <time.h>

void Fibonacci(int penultimo, int ultimo, int n, clock_t Inicio, int i);

int main(void)
{
  clock_t Start = clock();   
  int numero;
  printf( "Introduce rango de numeros fibonacci a imprimir: " );
  scanf( "%d", &numero);
  Fibonacci(0,1, numero,Start,1); 
} 

void Fibonacci(int penultimo, int ultimo, int n, clock_t Inicio,int i)
{
  FILE *Archivo;
  Archivo = fopen("grafica2.txt","at");
  double Time = 0.0;
  int actual;
  printf("%d\n",ultimo);
  if(i>=10){
  fprintf(Archivo,"%d, ",i);
  clock_t Fin = clock();
  Time = (double) (Fin-Inicio) /CLOCKS_PER_SEC;
  fprintf(Archivo,"%f\n",Time);
  }
  if (n>1){
    actual = penultimo + ultimo;
    n--;
    Fibonacci(ultimo,actual,n,Inicio,i+1);
  }
}
