#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct def_Nodo
{
  int Cantidad;
  char ID;
  struct def_Nodo **Aristas;
} TipoNodo;

void Enter ()
{
  printf ("Presiona Enter para continuar...\n\n");
  __fpurge (stdin);
  getchar ();
  __fpurge (stdin);
  printf ("\n");
}

void BuscarDireccionNodo (TipoNodo *Inicio, int Contador, int ConexionesMax, char IDBuscar, TipoNodo **NodoEncontrado)
{
  *NodoEncontrado = NULL;
  if (Inicio != NULL)
  {
    if (Inicio -> ID != IDBuscar)
    {
      while (Contador < ConexionesMax)
      {
        if (Inicio -> Aristas [Contador] != NULL)
        {
          BuscarDireccionNodo (Inicio -> Aristas [Contador], Contador, ConexionesMax, IDBuscar, NodoEncontrado);
        }
        Contador++;
      }
    }
    else
    {
      *NodoEncontrado = Inicio;
    }
  }
}

void AnadirNodo (char *ID, TipoNodo **Inicio, int ConexionesMax)
{
  int i, Error;
  char IDPrevio;
  TipoNodo *Nuevo, *Previo;
  Nuevo = (TipoNodo *) malloc (sizeof (TipoNodo));
  Nuevo -> Cantidad = 0;
  Nuevo -> ID = *ID;
  Nuevo -> Aristas = (TipoNodo **) malloc (sizeof (TipoNodo *) * 4);
  for (i = 0; i < ConexionesMax; i++)
    Nuevo -> Aristas [i] = NULL;
  if (*Inicio == NULL)
    *Inicio = Nuevo;
  else
  {
    do
    {
      printf ("¿A donde quieres conectar este nodo?\n\n");
      __fpurge (stdin);
      scanf ("%c", &IDPrevio);
      printf ("\n");
      BuscarDireccionNodo (*Inicio, 0, ConexionesMax, IDPrevio, &Previo);
      if (Previo != NULL)
      {
        printf ("INFO: Añadiendo al nodo con el ID: %c\n\n", Previo -> ID);
        if (Previo -> Cantidad == 4)
        {
          printf ("INFO: El nodo está lleno\n\n");
          Error = 1;
          Enter ();
        }
        else
        {
          i = 0;
          while (Previo -> Aristas [i] != NULL)
            i++;
          Previo -> Aristas [i] = Nuevo;
          (Previo -> Cantidad)++;
          Error = 0;
        }
      }
      else
      {
        printf ("INFO: No se encontró el nodo\n\n");
        Error = 1;
        Enter ();
      }
    }
    while (Error == 1);
  }
  printf ("INFO: Nodo añadido\n\n");
  Enter ();
  (*ID)++;
}

void ImprimirGrafo (TipoNodo *Inicio)
{
  printf ("Ahí te va el grafo:\n\n");
  /*while (Inicio != NULL)
  {
    printf ("Nodo %c, conecciones activas: %d\n", Inicio -> ID, Inicio -> Cantidad);
    Inicio = Inicio -> Sig;
  }
  printf ("\n");*/
}

void Buscar (TipoNodo *Inicio, int ConexionesMax)
{
  int i;
  char IDBuscador;
  TipoNodo *Buscador;
  printf ("Introduzca el ID del nodo a buscar\n\n");
  __fpurge (stdin);
  scanf ("%c", &IDBuscador);
  printf ("\n");
  BuscarDireccionNodo (Inicio, 0, ConexionesMax, IDBuscador, &Buscador);
  if (Buscador != NULL)
  {
    printf ("Se encontró el Nodo con el ID: %c\n\n", Buscador -> ID);
    printf ("Este nodo tiene %d conexiones:\n", Buscador -> Cantidad);
    for (i = 0; Buscador -> Aristas [i] != NULL; i++)
    {
      printf ("Arista %d: Conectada al nodo %c\n", i + 1, Buscador -> Aristas [i] -> ID);
    }
    printf ("\n");
    Enter ();
  }
  else
  {
    printf ("No se encontró el nodo...\n\n");
    Enter ();
  }
}

int main (void)
{
  int ConexionesMax, Seleccion;
  char IDActual = 97;
  TipoNodo *Inicio = NULL;
  printf ("Ingrese el número de conexiones máximas por Nodo:\n\n");
  scanf ("%d", &ConexionesMax);
  printf ("\n");
  do
  {
    printf ("Elija una opción:\n\n");
    printf ("1.- Añadir nodo\n");
    printf ("2.- Añadir arista\n");
    printf ("3.- Desplegar gráfo\n");
    printf ("4.- Buscar dato\n");
    printf ("5.- Salir\n\n");
    scanf ("%d", &Seleccion);
    printf ("\n");
    switch (Seleccion)
    {
      case 1:
      AnadirNodo (&IDActual, &Inicio, ConexionesMax);
      break;
      case 2:
      break;
      case 3:
      ImprimirGrafo (Inicio);
      break;
      case 4:
      Buscar (Inicio, ConexionesMax);
      break;
    }
  } while (Seleccion != 5);
}
