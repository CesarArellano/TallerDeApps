#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Neuron
{
  double W[2],Bias,Error;
  int X[2];
}TipoNeurona;

void InicializarNeuronasAND_OR(TipoNeurona *Neurona);
void InicializarNeuronasNOT(TipoNeurona *Neurona);
void EntrenamientoAND_OR(TipoNeurona* Neurona, double Datos[4][3], char NombreArchivo[]);
void EntrenamientoNOT(TipoNeurona* Neurona, double Datos[2][2], char NombreArchivo[]);
double ObtenerForwardPass(TipoNeurona *Neurona, double EntradasX[], int Tipo);
void Resultados(TipoNeurona *AND, int Tipo);
int Verificacion(double Resultado);

int main (void)
{
  TipoNeurona NeuronaAND,NeuronaOR,NeuronaNOT;
  int Opcion;
  double DatosAND[4][3] = {{-1, -1, -1}, {-1, 1, -1}, {1, -1, -1}, {1, 1, 1}};
  double DatosOR[4][3] = {{-1, -1, -1}, {-1, 1, 1}, {1, -1, 1}, {1, 1, 1}};
  double DatosNOT[2][2] = {{-1, 1}, {1, -1}};
  InicializarNeuronasAND_OR(&NeuronaAND);
  InicializarNeuronasAND_OR(&NeuronaOR);
  InicializarNeuronasNOT(&NeuronaNOT);
  EntrenamientoAND_OR(&NeuronaAND,DatosAND,"NeuronaAND.txt");
  EntrenamientoAND_OR(&NeuronaOR,DatosOR,"NeuronaOR.txt");
  EntrenamientoNOT(&NeuronaNOT,DatosNOT,"NeuronaNOT.txt");
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
    	  Resultados(&NeuronaAND,2);
    	  break;
    	case 2:
    	  Resultados(&NeuronaOR,2);
    	  break;
    	case 3:
    	  Resultados(&NeuronaNOT,1);
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

void InicializarNeuronasAND_OR(TipoNeurona *Neurona)
{
  srand48(time(NULL));
  Neurona->W[0] = drand48();
  Neurona->W[1] = drand48();
  Neurona->Bias = drand48();
}
void InicializarNeuronasNOT(TipoNeurona *Neurona)
{
  srand48(time(NULL));
  Neurona->W[0] = drand48();
  Neurona->Bias = drand48();
}
void EntrenamientoAND_OR(TipoNeurona* Neurona, double Datos[4][3], char NombreArchivo[])
{
  FILE *Archivo;
  Archivo = fopen(NombreArchivo, "wt");
  double N = 0.01;
  int Posicion = 0;

  for(int i = 0; i < 1000; i++)
    {
      if(Posicion == 4)
        Posicion = 0; 

      Neurona->Error = Datos[Posicion][2] - ObtenerForwardPass(Neurona,Datos[Posicion],2);
      
      for(int j = 0 ; j < 2;j++)
        Neurona->W[j] += N * Neurona->Error; 

      Neurona->Bias += Neurona->Error * N;
      fprintf(Archivo, "%lf, %lf\n", Neurona->W[0],Neurona->Error);
      Posicion++;
    }   

  fclose(Archivo);
}

void EntrenamientoNOT(TipoNeurona* Neurona, double Datos[2][2], char NombreArchivo[])
{
  FILE *Archivo;
  Archivo = fopen(NombreArchivo, "wt");
  double N = 0.01;
  int Posicion = 0;

  for(int i = 0; i < 1000; i++)
    {
      if(Posicion == 2)
        Posicion = 0; 
      Neurona->Error = Datos[Posicion][1] - ObtenerForwardPass(Neurona,Datos[Posicion],1);
      Neurona->W[0] += N * Neurona->Error; 
      Neurona->Bias += Neurona->Error * N;
      fprintf(Archivo, "%lf, %lf\n", Neurona->W[0],Neurona->Error);
      Posicion++;
    }   

  fclose(Archivo);
}

void Resultados(TipoNeurona *Neurona, int Tipo)
{
  double EntradasX[2];
  if(Tipo == 2)
  {
    printf("Ingrese A\n");
    scanf(" %lf",&EntradasX[0]);
    printf("Ingrese B\n");
    scanf(" %lf",&EntradasX[1]);
    printf("El resultado es: %d", Verificacion(ObtenerForwardPass(Neurona,EntradasX,Tipo)));    
  }
  else
  {
    printf("Ingrese A\n");
    scanf(" %lf",&EntradasX[0]);
    printf("El resultado es: %d", Verificacion(ObtenerForwardPass(Neurona,EntradasX,Tipo)));
  }
  
}

double ObtenerForwardPass(TipoNeurona *Neurona, double EntradasX[], int Tipo)
{
  double Suma = 0;
  for(int i = 0; i < Tipo; i++)
    Suma += EntradasX[i] * Neurona->W[i];
  Suma += Neurona->Bias;
  return Suma; 
}

int Verificacion(double Resultado)
{
  if(Resultado < 0)
    return -1;
  else
    return 1;
}

/*
  Sin decimales;
  srand(time(NULL));
  num_random = rand() * (2 + 0);
*/
