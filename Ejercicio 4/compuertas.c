#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Neuron
{
  double *W,Bw,Threshold,Resultado;
  int *X;
}TipoNeurona;

void AND(TipoNeurona *PrimerNeurona);
void OR(TipoNeurona *PrimerNeurona);
void NOT(TipoNeurona *PrimerNeurona);
void XOR(TipoNeurona *PrimerNeurona);

int main (void)
{
  TipoNeurona PrimerNeurona;
  PrimerNeurona.Threshold = 0.5;
  int Opcion,Pesos;
  printf("¿Cuantas entradas requieres? (Recomendación: 2)\n");
  scanf(" %d", &Pesos);
  if(Pesos == 2)
    {
      PrimerNeurona.W = (double *) malloc (sizeof (TipoNeurona)*Pesos);
      PrimerNeurona.X = (int *) malloc (sizeof (TipoNeurona)*Pesos);
    }
  else
    {
      printf("Error, saliendo del programa...\n");
      exit(0);
    }
  do
    {
      system("clear");
      printf("Menú Implementacion de generador de gráfos\n");
      printf("1.- AND\n");
      printf("2.- OR\n");
      printf("3.- NOT\n");
      printf("4.- XOR\n");
      printf("5.- Salir\n");
      printf("Escoge una opción\n");
      scanf(" %d",&Opcion);
      system("clear");
      switch(Opcion)
	{
	case 1:
	  AND(&PrimerNeurona);
	  break;
	case 2:
	  OR(&PrimerNeurona);
	  break;
	case 3:
	  NOT(&PrimerNeurona);
	  break;
	case 4:
	  XOR(&PrimerNeurona);
	  break;
	case 5:
	  printf("Saliendo del programa...\n");
	  exit(0);
	  break;
	default:
	  printf("Opción incorrecta, intente de nuevo.\n");
	  break;
	}
      printf("\nPresione Enter para continuar.");
      __fpurge(stdin);
      getchar();
    }while(Opcion!=5);
}

void AND(TipoNeurona *PrimerNeurona)
{
  printf("Ingrese A\n");
  scanf(" %d",&PrimerNeurona->X[0]);
  printf("Ingrese B\n");
  scanf(" %d",&PrimerNeurona->X[1]);
  PrimerNeurona->W[0] = 1;
  PrimerNeurona->W[1] = 1;
  PrimerNeurona->Bw = -1;
  PrimerNeurona->Resultado = PrimerNeurona->W[0]*PrimerNeurona->X[0] + PrimerNeurona->W[1]*PrimerNeurona->X[1]+PrimerNeurona->Bw;
  if(PrimerNeurona->Resultado < PrimerNeurona->Threshold)
    printf("El resultado es: 0\n");
  else
    printf("El Resultado es: 1\n");

}
void OR(TipoNeurona *PrimerNeurona)
{
  printf("Ingrese A\n");
  scanf(" %d",&PrimerNeurona->X[0]);
  printf("Ingrese B\n");
  scanf(" %d",&PrimerNeurona->X[1]);
  PrimerNeurona->W[0] = 1;
  PrimerNeurona->W[1] = 1;
  PrimerNeurona->Bw = 0;
  PrimerNeurona->Resultado = PrimerNeurona->W[0]*PrimerNeurona->X[0] + PrimerNeurona->W[1]*PrimerNeurona->X[1]+PrimerNeurona->Bw;
  if(PrimerNeurona->Resultado < PrimerNeurona->Threshold)
    printf("El resultado es: 0\n");
  else
    printf("El Resultado es: 1\n");

}
void NOT(TipoNeurona *PrimerNeurona)
{
  printf("Ingrese A\n");
  scanf(" %d",&PrimerNeurona->X[0]);
  PrimerNeurona->W[0] = -1;
  PrimerNeurona->Bw = 0.75;
  PrimerNeurona->Resultado = PrimerNeurona->W[0]*PrimerNeurona->X[0] + PrimerNeurona->Bw;
  if(PrimerNeurona->Resultado < PrimerNeurona->Threshold)
    printf("El resultado es: 0\n");
  else
    printf("El Resultado es: 1\n");

}
void XOR(TipoNeurona *PrimerNeurona)
{
  printf("No se puede xddd\n");
}
