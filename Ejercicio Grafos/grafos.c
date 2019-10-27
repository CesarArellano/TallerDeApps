#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct def_Grafo
{
  char ID;
  int Conexiones;
  struct def_Grafo **Aristas;
}TipoGrafo;

typedef struct def_Conteo
{
	char Vertex,PreviousVertex;
	int SDF; 
}TipoConteo;

void AgregarNodo(TipoGrafo **PrimerGrafo, char *Letra, int Max);
void BuscarNodo(TipoGrafo *PrimerGrafo, int i, int Max, char BuscarID, TipoGrafo **UbicacionNodo);
void AgregarAristas(TipoGrafo **PrimerGrafo, int Max);
void DesplegarGrafo(TipoGrafo *PrimerGrafo, int i, int Max);
void BuscarDato(TipoGrafo *PrimerGrafo, int Max);
void BorrarLista(TipoGrafo *PrimerGrafo,int i, int Max);

int main (void)
{
  TipoGrafo *PrimerGrafo = NULL;
	TipoConteo Tabla[10];
  char Letra='a',ID;
  int ConexMax,Opcion;
  printf("Ingrese el máximo de conexiones\n");
  scanf(" %d",&ConexMax);
  do
    {
      system("clear");
      printf("Menú Implementacion de generador de gráfos\n");
      printf("1.- Añadir nodo\n");
      printf("2.- Añadir conexión\n");
      printf("3.- Desplegar gráfo\n");
      printf("4.- Buscar dato\n");
      printf("5.- Salir\n");
      printf("Escoge una opción\n");
      scanf(" %d",&Opcion);
      system("clear");
      switch(Opcion)
	{
	case 1:
	  AgregarNodo(&PrimerGrafo,&Letra,ConexMax);
	  break;
	case 2:
	  AgregarAristas(&PrimerGrafo,ConexMax);
	  break;
	case 3:
	  DesplegarGrafo(PrimerGrafo,0,ConexMax);
	  break;
	case 4:
	  BuscarDato(PrimerGrafo,ConexMax);
	  break;
	case 5:
	  BorrarLista(PrimerGrafo,0,ConexMax);
	  printf("Saliendo del programa...\n");
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

void AgregarNodo(TipoGrafo **PrimerGrafo, char *Letra, int Max)
{
  TipoGrafo *Nuevo,*Anterior;
  int i, Flag;
  char BuscarID;
  Nuevo = (TipoGrafo *) malloc (sizeof (TipoGrafo));
  Nuevo -> Aristas = (TipoGrafo **) malloc (sizeof (TipoGrafo *) * Max);
  Nuevo -> ID = *Letra;
  Nuevo -> Conexiones = 0;
  for(i=0; i<Max; i++)
    Nuevo -> Aristas[i] = NULL;
  if(*PrimerGrafo == NULL)
    {
      *PrimerGrafo = Nuevo;
      printf("Se añadió el nodo raíz -> %c\n",Nuevo->ID);
      (*Letra)++;
    }
  else
    {
      do
    	{
	  Anterior = NULL;
	  printf("¿A dónde deseas conectar el nodo?\n");
	  Flag = scanf(" %c",&BuscarID);
	  if(Flag)
	    {
	      BuscarNodo(*PrimerGrafo, 0, Max, BuscarID, &Anterior);
	      if (Anterior == NULL)
		printf ("No existe el nodo\n");
	    }	    
	  else
	    printf("Error de lectura, letras 'a' - 'z'\n");
	}while(Flag==0 || Anterior==NULL);
      if(Anterior->Conexiones < Max)
	{
	  Anterior->Aristas[Anterior->Conexiones]= Nuevo;
	  (Anterior->Conexiones)++;
	  (*Letra)++;
	  printf ("La conexión entre %c con %c fue éxitosa\n",Anterior->ID,Nuevo->ID); 
	}
      else
	printf("Error, conexiones llenas en %c\n",Anterior->ID);    	     	
    }
}
void AgregarAristas(TipoGrafo **PrimerGrafo, int Max)
{
  TipoGrafo *Origen, *Destino;
  char IDOrigen, IDDestino;
  int Flag=1;
  Origen = NULL;
  Destino = NULL;
  printf("Ingresa el ID origen\n");
  scanf(" %c",&IDOrigen);
  BuscarNodo(*PrimerGrafo, 0, Max,IDOrigen,&Origen);
  printf("Ingresa el ID destino\n");
  scanf(" %c",&IDDestino);
  BuscarNodo(*PrimerGrafo, 0, Max, IDDestino, &Destino);
  if(Origen == NULL || Destino == NULL)
    {
      printf("No existe alguno de los nodos proporcionados\n");
      return;
    }
  if(Origen->Conexiones >= Max)
    {
      printf("Error, conexiones llenas en %c\n",Origen->ID);
      return;
    }
  else
    {
      for(int i = 0; i<Max; i++)
	{
	  if(Origen->Aristas[i] == Destino)
	    {
	      printf("El nodo origen ya está conectado con el destino\n");
	      Flag = 0;
	    }					
	}
      if(Flag == 1)
	{
	  Origen->Aristas[Origen->Conexiones] = Destino;
	  (Origen->Conexiones)++;
	  printf ("La conexión entre %c con %c fue éxitosa\n",Origen->ID,Destino->ID);
	}
    }
}

void BuscarNodo (TipoGrafo *PrimerGrafo, int i, int Max, char BuscarID, TipoGrafo **UbicacionNodo)
{
  if (PrimerGrafo -> ID != BuscarID)
    {
      while (i < Max)
	{
	  if (PrimerGrafo -> Aristas [i] != NULL)
	    BuscarNodo(PrimerGrafo -> Aristas [i], i, Max, BuscarID, UbicacionNodo);		
	  i++;
	}
    }
  else
      *UbicacionNodo = PrimerGrafo;
}



void DesplegarGrafo(TipoGrafo *PrimerGrafo, int i, int Max)
{
  while (i < Max)
    {
      if (PrimerGrafo -> Aristas [i] != NULL)
	DesplegarGrafo(PrimerGrafo -> Aristas [i], i, Max);	
      if(i == Max-1)
	printf("%c->",PrimerGrafo->ID);	
      i++;
    }
}
void BuscarDato(TipoGrafo *PrimerGrafo, int Max)
{
  TipoGrafo *Destino;
  char BuscarID;
  int Flag=1;
  Destino = NULL;
  printf("Ingresa el ID a buscar\n");
  scanf(" %c",&BuscarID);
  BuscarNodo(PrimerGrafo, 0, Max, BuscarID, &Destino);
  if(Destino == NULL)
    {
      printf("No existe el nodo,intenta de nuevo\n");
      return;
    }
  else
    {
      printf("%c-> ", Destino->ID);
      for(int i = 0; i < Max; i++)
	if(Destino->Aristas[i] != NULL)
	  printf("%c-> ", Destino->Aristas[i]->ID);
    }
}
void BorrarLista(TipoGrafo *PrimerGrafo,int i, int Max)
{
  while (i < Max)
    {
      if (PrimerGrafo->Aristas[i] != NULL)
	BorrarLista(PrimerGrafo->Aristas[i], i, Max);
      if(i == Max - 1){
	free(PrimerGrafo);
	PrimerGrafo = NULL;
      }
      i++;
    }
}
