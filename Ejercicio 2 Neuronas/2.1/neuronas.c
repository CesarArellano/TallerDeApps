#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Neuron
{
  double W[2],Bias,Error;
  int X[2];
}TipoNeurona;

void InicializarNeuronas(TipoNeurona *AND);
void Entrenamiento(TipoNeurona* Neurona, double Entradas[4][2], double Salidas[], char NombreArchivo[]);
double ObtenerForwardPass(TipoNeurona *AND, double EntradasX[]);
void ResultadosAND(TipoNeurona *AND);
void ResultadosOR(TipoNeurona *OR);
void ResultadosNOT(TipoNeurona *NOT);
void ResultadosXOR(TipoNeurona *XOR);

int main (void)
{
  TipoNeurona NeuronaAND,NeuronaOR,NeuronaNOT,NeuronaXOR;
  int Opcion;
  double EntradasAND_OR_XOR[6][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1},{2,2},{3,3}};
  double SalidasAND[6] = {-1, -1, -1, 1, 1,1};
  double SalidasOR[4] = {-1, 1, 1, 1}; 
  double EntradasNOT[2] = {-1, 1};
  double SalidadNOT[2] = {1, -1};
    
  InicializarNeuronas(&NeuronaAND);
  Entrenamiento(&NeuronaAND,EntradasAND_OR_XOR,SalidasAND,"NeuronaAND.txt");
  printf("\nEntrenamiento Finalizado.\nPresione Enter para continuar...\n");
  __fpurge(stdin);
  getchar();
  do
  {
    system("clear");
    printf("Menú Implementacion de generador de gráfos\n");
    printf("1.- AND\n");
    printf("2.- OR\n");
    printf("3.- NOT\n");
    printf("4.- Salir\n");
    printf("Escoge una opción\n");
    scanf(" %d",&Opcion);
    system("clear");
    switch(Opcion)
  	{
    	case 1:
    	  ResultadosAND(&NeuronaAND);
    	  break;
    	case 2:
    	  ResultadosOR(&NeuronaOR);
    	  break;
    	case 3:
    	  ResultadosNOT(&NeuronaNOT);
    	  break;
    	case 4:
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
  }while(Opcion!=4);
}

void InicializarNeuronas(TipoNeurona *AND)
{
  srand48(time(NULL));
  AND->W[0] = drand48();
  AND->W[1] = drand48();
  AND->Bias = drand48();
}
void Entrenamiento(TipoNeurona* Neurona, double Entradas[4][2], double Salidas[], char NombreArchivo[])
{
  FILE *Archivo;
  Archivo = fopen(NombreArchivo, "wt");
  double N = 0.01;
  int Posicion = 0;

  for(int i = 0; i < 500; i++)
    {
      if(Posicion == 6)
        Posicion = 0; 

      Neurona->Error = Salidas[Posicion] - ObtenerForwardPass(Neurona,Entradas[Posicion]);
      
      for(int j = 0 ; j < 2;j++)
        Neurona->W[j] += N * Neurona->Error; 

      Neurona->Bias += Neurona->Error * N;
      fprintf(Archivo, "%lf, %lf\n", Neurona->W[0],Neurona->Error);
      Posicion++;
    }   

  fclose(Archivo);
}

void ResultadosAND(TipoNeurona *AND)
{
  double EntradasX[2];
  printf("Ingrese A\n");
  scanf(" %lf",&EntradasX[0]);
  printf("Ingrese B\n");
  scanf(" %lf",&EntradasX[1]);
  printf("El resultado es: %lf\n", ObtenerForwardPass(AND,EntradasX));
}
void ResultadosOR(TipoNeurona *OR)
{
  double EntradasX[2];
  printf("Ingrese A\n");
  scanf(" %lf",&EntradasX[0]);
  printf("Ingrese B\n");
  scanf(" %lf",&EntradasX[1]);

}
void ResultadosNOT(TipoNeurona *NOT)
{
  double EntradasX;
  printf("Ingrese A\n");
  scanf(" %lf",&EntradasX);
}
void ResultadosXOR(TipoNeurona *XOR)
{
  printf("No se puede xddd\n");
}

double ObtenerForwardPass(TipoNeurona *Neurona, double EntradasX[])
{
  double Suma = 0;
  for(int i = 0; i < 2; i++)
    Suma += EntradasX[i] * Neurona->W[i];
  Suma += Neurona->Bias;
  return Suma; 
}

/*
  Sin decimales;
  srand(time(NULL));
  num_random = rand() * (2 + 0);
*/
