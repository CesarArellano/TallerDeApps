#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct def_Coordenada
{
  double Y[10],Alfa[10],T;
  struct def_Coordenada *Sig;
} TipoCoordenada;

typedef enum defErrores
  {
   NoHayError, Lectura, Argumento
  } Errores;

void PedirDatos(double T0[], double Y0[], double *Alfa, double *H, double *Tf, int Orden, Errores Error[],int *Cant);
void VerificarErrores(Errores Error[],int Cant);
double Funcion(double T0, double Y0);
void DiffSolver(TipoCoordenada **Inicio, double T0, double Y0[], double Alfa[], double H , double Tf, int Orden);
void AgregarNodo(TipoCoordenada **Inicio, double T0, double Y0[],int Orden);
void ImprimirArch(TipoCoordenada *Inicio, int Orden);
void Graficar();
void Cargando(char Mensaje[]);
void BorrarLista(TipoCoordenada *Inicio);

int main (int argc, char *argv[])
{
  int Orden,Cant;
  double Y0[100],Alfa[100],T0,H,Tf;
  Errores Error[100];
  Error [0] = argc + 1;
  VerificarErrores(Error, 0);
  sscanf (argv[1], "%d", &Orden);
  TipoCoordenada *Inicio = NULL;
  PedirDatos(&T0,Y0,Alfa,&H,&Tf,Orden,Error,&Cant);
  VerificarErrores(Error,Cant);
  Cargando("Resolviendo ecuación");
  DiffSolver(&Inicio,T0,Y0,Alfa,H,Tf,Orden);
  Cargando("Imprimiendo datos en archivo");
  ImprimirArch(Inicio,Orden);
  Cargando("Graficando con GNUPlot");
  Graficar();
  BorrarLista (Inicio);
  return 0;
}

void PedirDatos(double T0[], double Y0[], double *Alfa, double *H, double *Tf, int Orden, Errores Error[],int *Cant)
{
  int i, j = 3;
  printf("Introduzca los siguientes datos:\n\n");
  printf("T0: \n");
  Error[0] = scanf(" %lf",T0);
  printf("Avance (h): \n");
  Error[1] = scanf(" %lf",H);
  printf("Tf: \n");
  Error[2] = scanf(" %lf",Tf);
  for (i = 0; i < Orden; i++)
    {
      printf("y^[%d](T0) = Y^[%d]0: \n", i, i);
      Error[j] = scanf(" %lf", &Y0[i]);
      j++;
      printf("α[%d]:\n", i);
      Error[j] = scanf(" %lf", &Alfa[i]);
      j++;
    }
  *Cant = j-1;
}

void VerificarErrores(Errores Error[],int Cant)
{
  for(int i=0; i<=Cant;i++)
    {
      if(Error[i] ==0)
	{
	  printf("Error en uno o más datos ingresados\n");
	  exit(1);
	}
      if(Error[i] == 2 || Error[i] >= 4)
	{
	  printf ("Ingresó una cantidad de argumentos incorrecta\n");
	  exit (2);
	}
    }
}

double Funcion(double T0, double Y0)
{
  //return cos(2*(3.1416)*T0);
  //return 0;
  //return T0 + 2*Y0;
  //return -Y0*cos(T0);
  return T0 - (3*Y0);
}

void DiffSolver(TipoCoordenada **Inicio, double T0, double Y0[], double Alfa[], double H , double Tf, int Orden)
{
  double U[100],Acum;
  int i,j;
  AgregarNodo(Inicio,T0,Y0,Orden);
  for(T0 += H; T0 <= Tf; T0 += H)
    {
      Acum=0;
      j = Orden - 1;
      for(i = 0; i < Orden; i++)
    	{
	  Acum += -Y0[i]*Alfa[j];
	  if(Orden != i+1)
	    U[i] = Y0[i+1] * H;
	  else
	    {
	      U[i] = Acum + H*(Funcion(T0-H, Y0[i - 1]));
	      AgregarNodo(Inicio,T0,U,Orden);
	    }
	  Y0[i] = U[i];
	  j--;
    	}
    }
}

void AgregarNodo(TipoCoordenada **Inicio, double T0, double Y0[],int Orden)
{
  TipoCoordenada *Temp, *Temp2;
  Temp = (TipoCoordenada *) malloc (sizeof (TipoCoordenada));
  for (int i=0;i<Orden;i++)
    Temp -> Y[i] = Y0[i];
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

void ImprimirArch(TipoCoordenada *Inicio, int Orden)
{
  int i;
  FILE *Archivo;
  Archivo = fopen("LTI.txt","wt");
  TipoCoordenada *Temp;
  Temp = Inicio;
  while (Temp != NULL)
    {
      fprintf(Archivo,"%f ",Temp -> T);
      for(i=0;i<(Orden-1);i++)
	fprintf(Archivo,"%f ", Temp -> Y[i]);
      fprintf(Archivo,"%f\n",Temp -> Y[i]);
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
