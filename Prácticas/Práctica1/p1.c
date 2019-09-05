#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void PedirDatos(float *Y0, float *T0, float *H, float *tf);
float Funcion(float T0,float Y0);
void Diff_Solver(float Y_Array[],float T_Array[], float Y0, float T0,float H ,float Tf,int *i);
void ImprimirArch(float Y_Array[],float T_Array[],int Limite);
void Graficar();

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

int main (void)
{
  float Y0,T0,H,Tf, Y_Array[100000], T_Array[100000];
  int Limite;
  PedirDatos(&Y0,&T0,&H,&Tf);
  Cargando("Resolviendo ecuación");
  Diff_Solver(Y_Array,T_Array,Y0,T0,H,Tf,&Limite);
  Cargando("Imprimiendo datos en archivo");
  ImprimirArch(Y_Array,T_Array,Limite);
  Cargando("Graficando con GNUPlot");
  Graficar();
  return 0;
}

void PedirDatos(float *Y0, float *T0, float *H, float *Tf)
{
  printf("Introduzca los siguientes datos:\n");
  printf("T0: ");
  scanf(" %f",T0);
  printf("Y0 (y(T0)): ");
  scanf(" %f",Y0);
  printf("Avance (h):");
  scanf(" %f",H);
  printf("Tf: ");
  scanf(" %f",Tf);  
}

float Funcion(float T0,float Y0)
{
  return 1+(T0*sin(T0*Y0));
}
void Diff_Solver(float Y_Array[],float T_Array[], float Y0, float T0,float H,float Tf,int *Limite)
{
  int i;
  for(i=0; T0<=Tf; i++)
    {
      Y_Array[i] = Y0;
      T_Array[i] = T0;
      Y0 = Y0+H*(Funcion(T0,Y0));      
      T0=H+T0;
    }
  *Limite=i;  
}
void ImprimirArch(float Y_Array[],float T_Array[],int Limite)
{
  FILE *Archivo;
  //printf("Limite: %d\n",Limite);
  Archivo = fopen("LTI.txt","wt");
  for(int i=0; i<Limite; i++)
      fprintf(Archivo,"%f %f\n",T_Array[i], Y_Array[i]);
  fclose(Archivo);
}
void Graficar()
{
  int i;
  char *AbrirGnuPlot[] = {"set title \"Método de Predición / Euler\"", 
			    "set ylabel \"----Y--->\"",
			    "set xlabel \"----T--->\"",
			    "plot \"LTI.txt\" with lines"
  };
  FILE *VentanaGnuPlot = popen ("gnuplot -persist", "w");
  for (i=0; i<4; i++)
    fprintf(VentanaGnuPlot, "%s \n", AbrirGnuPlot[i]);
}
