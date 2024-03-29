#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct def_Coordenada
{
  double Y,T;
  struct def_Coordenada *Sig;
} TipoCoordenada;

void PedirDatos(double *T0, double *Y0, double *H, double *Tf);
double Funcion(double T0, double Y0);
void DiffSolver(TipoCoordenada **Inicio, double T0, double Y0, double H , double Tf);
void AgregarNodo(TipoCoordenada **Inicio, double T0, double Y0);
void ImprimirArch(TipoCoordenada *Inicio);
void Graficar();
void Cargando(char Mensaje[]);
void BorrarLista(TipoCoordenada *Inicio);

int main (void)
{
  double Y0,T0,H,Tf;
  TipoCoordenada *Inicio = NULL;
  PedirDatos(&T0,&Y0,&H,&Tf);
  Cargando("Resolviendo ecuación");
  DiffSolver(&Inicio,T0,Y0,H,Tf);
  Cargando("Imprimiendo datos en archivo");
  ImprimirArch(Inicio);
  Cargando("Graficando con GNUPlot");
  Graficar();
  BorrarLista (Inicio);
  return 0;
}

void PedirDatos(double *T0, double *Y0, double *H, double *Tf)
{
  printf("Introduzca los siguientes datos:\n");
  printf("T0: ");
  scanf(" %lf",T0);
  printf("Y0 (y(T0)): ");
  scanf(" %lf",Y0);
  printf("Avance (h):");
  scanf(" %lf",H);
  printf("Tf: ");
  scanf(" %lf",Tf);
}

double Funcion(double T0, double Y0)
{
  return T0+Y0;
}

void DiffSolver(TipoCoordenada **Inicio, double T0, double Y0, double H , double Tf)
{
  for(; T0 <= Tf; T0 += H)
    {
      AgregarNodo(Inicio,T0,Y0);
      Y0 = Y0+H*(Funcion(T0,Y0));
    }
}

void AgregarNodo(TipoCoordenada **Inicio, double T0, double Y0)
{
  TipoCoordenada *Temp, *Temp2;
  Temp = (TipoCoordenada *) malloc (sizeof (TipoCoordenada));
  Temp -> Y = Y0;
  Temp -> T = T0;
  Temp -> Sig = NULL;
  if (*Inicio != NULL)
    {
      Temp2 = *Inicio;
      while (Temp2 -> Sig != NULL)
	Temp2 = Temp2 -> Sig;
      Temp2 -> Sig = Temp;
    }
  else
    *Inicio = Temp;

}

void ImprimirArch(TipoCoordenada *Inicio)
{
  FILE *Archivo;
  Archivo = fopen("LTI.txt","wt");
  TipoCoordenada *Temp;
  Temp = Inicio;
  while (Temp != NULL)
    {
      fprintf(Archivo,"%lf %lf\n",Temp -> T, Temp -> Y);
      Temp = Temp -> Sig;
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

void BorrarLista (TipoCoordenada *Inicio)
{
  TipoCoordenada *Temp;
  while (Inicio != NULL)
    {
      Temp = Inicio;
      Inicio = Inicio -> Sig;
      free (Temp);
    }
}
