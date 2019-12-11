#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//Declaración Estructura de Valores de la Señal;
typedef struct def_Senial
{
  double Amplitud, Frecuencia, TFinal,*MusterTiempo,*Evaluacion;
  double TamMuestra,NumHarmonicos;
} TipoSenial;

void PedirDatos(TipoSenial *Valores); // Pedimos datos iniciales de la señal;
void Decode(TipoSenial *Valores); // Decodifica la señal a partir de los valores iniciales de la señal
void ImprimirArch(TipoSenial Valores); // Imprimir el muestreo del tiempo y de todos los valores de la funcion evaluada en determinada t;
void Graficar(); // Grafica en gnuplot el archivo de texto que tiene los valores de la señal decodificada;
void Cargando(char Mensaje[]); // Menú de carga -> estado en el cual se encuentra el programa;

int main (void)
{
  TipoSenial Senal;  // Instanciamos la estructura;
  PedirDatos(&Senal);
  Senal.MusterTiempo = (double *) malloc (sizeof (TipoSenial)*Senal.TamMuestra); // Generamos el arreglo dinámico de muestreo de tiempo de la estructura;
  Senal.Evaluacion = (double *) malloc (sizeof (TipoSenial)*Senal.TamMuestra); // Generamos el arreglo dinámico donde se van a almacenar la funcion evaluada en determinada t de la estructura;
  Cargando("Decodificando señal\n"); // Estado: Decodificando señal;
  Decode(&Senal);
  Cargando("Imprimiendo datos en archivo"); // Estado: Imprimir datos en archivo;
  ImprimirArch(Senal);
  Cargando("Graficando con GNUPlot"); // Estado: Graficando con GNUPlot;
  Graficar();
  return 0;
}

void PedirDatos(TipoSenial *Valores)
{
  printf("Introduzca los siguientes datos:\n\n");
  printf("Amplitud (A): \n");
  scanf(" %lf",&Valores -> Amplitud);
  printf("Frecuencia (f): \n");
  scanf(" %lf",&Valores -> Frecuencia);
  printf("Harmónicos (n): \n");
  scanf(" %lf",&Valores -> NumHarmonicos);
  printf("Tiempo Final (tf): \n");
  scanf(" %lf",&Valores -> TFinal);
  printf("Tamaño de muestra (ARR): \n");
  scanf(" %lf",&Valores -> TamMuestra);
}

void Decode(TipoSenial *Valores)
{
  double Incremento = Valores->TFinal / Valores->TamMuestra;
  double Res, T, PI=3.14159;
  int i=0;
  for(T = 0; T <= Valores->TFinal; T += Incremento)
    {
      Res = 0;
      Valores->MusterTiempo[i]= T;
      for(int j = 1; j<Valores->NumHarmonicos; j++)
      {
         Res += ((Valores->Amplitud / (PI * j)) * (cos (PI * j) - 1) * (sin (2 * PI * j * Valores->Frecuencia * T))); // Evaluacion en la señal;
      }
      Valores->Evaluacion[i] = (Valores->Amplitud / 2) - Res;
      i++;
    }
}

void ImprimirArch(TipoSenial Valores)
{
  int i;
  char NombreArchivo[100];
  FILE *Archivo;
  Archivo = fopen("senial.txt","wt");
  for(i = 0; i<Valores.TamMuestra;i++)
    {
      fprintf(Archivo,"%lf %lf\n",Valores.MusterTiempo[i],Valores.Evaluacion[i]);
    }

  fclose(Archivo);
}

void Graficar()
{
  int i;
  char *AbrirGnuPlot[] = {"set title \"f(t) con n harmonicos\"",
			  "set ylabel \"----Señal Muestreada--->\"",
			  "set xlabel \"----Muster Tiempo--->\"",
			  "plot \"senial.txt\" with lines"
  };
  FILE *VentanaGnuPlot = popen ("gnuplot -persist", "w");
  for (i=0; i<4; i++)
    fprintf(VentanaGnuPlot, "%s \n", AbrirGnuPlot[i]);
}

void Cargando (char Mensaje[])
{
  system ("clear");
  puts (Mensaje);
  printf ("\n");
  system ("sleep 0.15");
  system ("clear");
  puts (Mensaje);
  printf (".\n");
  system ("sleep 0.15");
  system ("clear");
  puts (Mensaje);
  printf ("..\n");
  system ("sleep 0.15");
  system ("clear");
  puts (Mensaje);
  printf ("...\n");
  system ("sleep 0.15");
}
