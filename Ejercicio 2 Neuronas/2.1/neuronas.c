/*
 * @author: César Mauricio Arellano Velásquez
 * @date:   19/Noviembre/2019
 * @file:   neuronas.c
 * @brief:  Implementación de la ley de Hebb en una neurona para simular compuertas lógicas AND/OR/NOT.
 */

// INCLUYENDO LAS BIBLIOTECAS A UTILIZAR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// DEFINIENDO LA ESTRUCTURA DE CADA NEURONA
typedef struct Neuron
{
  double W[2],Bias,Error;
  int X[2];
}TipoNeurona;

// Estructuras de las funciones
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
    printf("Menú Compuertas Lógicas\n");
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
  }while(Opcion != 4);
}

/* * Funcion que inicializa los valores de los pesos y el bias de la neurona.
   * @param TipoNeurona* Neurona actualiza la estructura de la neurona AND y OR.
*/
void InicializarNeuronasAND_OR(TipoNeurona *Neurona)
{
  srand48(time(NULL));
  Neurona->W[0] = drand48();
  Neurona->W[1] = drand48();
  Neurona->Bias = drand48();
}
/* * Funcion que inicializa los valores del peso y el bias de la neurona.
   * @param TipoNeurona* Neurona actualiza la estructura de la neurona NOT.
*/
void InicializarNeuronasNOT(TipoNeurona *Neurona)
{
  srand48(time(NULL));
  Neurona->W[0] = drand48();
  Neurona->Bias = drand48();
}
/* * Funcion que realiza el entrenamiento de las neuronas AND y OR.
   * @param TipoNeurona* Neurona actualiza los pesos para interpretar las entradas y así arrojar la salida deseada.
   * @param double Datos[][] Arreglo bidimensional con las entradas y salidas deseadas
   * @param char NombreArchivo Cadena que indica el nombre del archivo a registrar los pesos y el error.
*/
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
        Neurona->W[j] += N * Neurona->Error * Datos[Posicion][j]; 

      Neurona->Bias += Neurona->Error * N;
      fprintf(Archivo, "%lf, %lf, %lf\n", Neurona->W[0],Neurona->W[1],Neurona->Error);
      Posicion++;
    }   

  fclose(Archivo);
}

/* * Funcion que realiza el entrenamiento de las neuronas NOT.
   * @param TipoNeurona* Neurona actualiza el peso para interpretar la entrada y así arrojar la salida deseada.
   * @param double Datos[][] Arreglo bidimensional con las entradas y salidas deseadas
   * @param char NombreArchivo Cadena que indica el nombre del archivo a registrar los pesos y el error.
*/
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
      Neurona->W[0] += N * Neurona->Error * Datos[Posicion][0]; 
      Neurona->Bias += Neurona->Error * N;
      fprintf(Archivo, "%lf, %lf\n", Neurona->W[0],Neurona->Error);
      Posicion++;
    }   

  fclose(Archivo);
}

/* * Funcion que da los resultados de la compuertas lógicas AND, OR y NOT.
   * @param TipoNeurona* Neurona al terminar el entrenamiento, esta se usa para desplegar la salida esperada dependiendo la combinación de la compuerta lógica.
   * @param int Tipo Indica que tipo de compuerta es: AND, OR o NOT.
*/
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

/* * Funcion que obtiene la salida estimada de las neuronas AND, OR. NOT
   * @param TipoNeurona* Neurona calcula los pesos para interpretar las entradas y así arrojar la salida deseada.
   * @param double EntradasX[] Arreglo bidimensional con las entradas.
   * @param int Tipo Indica que tipo de compuerta es: AND, OR o NOT.
*/
double ObtenerForwardPass(TipoNeurona *Neurona, double EntradasX[], int Tipo)
{
  double Suma = 0;
  for(int i = 0; i < Tipo; i++)
    Suma += EntradasX[i] * Neurona->W[i];
  Suma += Neurona->Bias;
  return Suma; 
}

/* * Funcion que verifica la salida estimada para obtener la salida real.
   * @param double Resultado es threshold que nos indica que salida arrojar dependiendo de la salida estimada.
*/
int Verificacion(double Resultado)
{
  if(Resultado < 0)
    return -1;
  else
    return 1;
}
