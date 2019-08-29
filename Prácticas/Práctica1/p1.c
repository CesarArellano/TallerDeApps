#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PedirDatos(float *Y0, float *T0, float *h, float *tf);
float Funcion(float T0,float Y0);
void Diff_Solver(float Y_Array[],float T_Array[], float Y0, float T0, float H, float Tf,int *i);
void ImprimirArch(float Y_Array[],float T_Array[],int Limite);
void Graficar();

int main (void)
{
  float Y0, T0, H, Tf, Y_Array[1000], T_Array[1000];
  int Limite;
  PedirDatos(&Y0,&T0,&H,&Tf);
  system("clear");
  printf("Resolviendo ecuación...\n");
  system("sleep 1");
  Diff_Solver(Y_Array,T_Array,Y0,T0,H,Tf,&Limite);
  system("clear");
  printf("Imprimiendo datos en Archivo...\n");
  system("sleep 1");
  ImprimirArch(Y_Array,T_Array,Limite);
  system("clear");
  printf("Graficando datos en GNUPlot...\n");
  system("sleep 1");
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
  printf("H: ");
  scanf(" %f",H);
  printf("Tf: ");
  scanf(" %f",Tf);  
}

float Funcion(float T0,float Y0)
{
  return T0+3*Y0;
}
void Diff_Solver(float Y_Array[],float T_Array[], float Y0, float T0, float H, float Tf,int *Limite)
{
  int i;
  for(i=0; T0<=Tf; i++)
    {
      Y_Array[i] = Y0;
      T_Array[i] = T0;
      Y0 = Y0+H*(Funcion(T0,Y0));
      T0 = H+T0;
    }
  *Limite=i;
}
void ImprimirArch(float Y_Array[],float T_Array[],int Limite)
{
  FILE *Archivo;
  //printf("Limite: %d\n",Limite);
  Archivo = fopen("LTI.txt","wt");
  for(int i=0; i<Limite; i++)
    {
      fprintf(Archivo,"%f, ",T_Array[i]);
      fprintf(Archivo,"%f\n",Y_Array[i]);
    }
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
