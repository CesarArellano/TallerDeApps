#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct def_Arbol{
  double Probabilidad;
  char Letra;
  struct def_Arbol *izq,*der;
}TipoNodo;

void ExtraerArchivo(TipoNodo **Raiz);
void InsertarArbol(TipoNodo **Raiz, double Probabilidad, char Letra);
void ImprimirArbol(TipoNodo *Raiz);
void BorrarArbol(TipoNodo *Raiz);

int main (void){
  TipoNodo *Raiz = NULL;
  ExtraerArchivo(&Raiz);
  printf("El árbol se ha creado éxitosamente.\n");
  printf("Presione Enter para continuar...");
  __fpurge(stdin);
  getchar();
	ImprimirArbol(Raiz); // Recorre Inorden
	printf("Saliendo del programa...\n");
	BorrarArbol(Raiz);
}

void ExtraerArchivo(TipoNodo **Raiz){
  FILE *Archivo;
  char Nombre_Arch[50],Renglon[200],Letra;
  double Probabilidad;
  printf("Escriba el nombre del archivo\n");
  gets(Nombre_Arch);
  Archivo = fopen(Nombre_Arch,"rt");
  if(Archivo == NULL){
      printf("El archivo no existe\n");
      printf("Saliendo del programa...");
      exit(0);
  }
  else{
    while(fgets(Renglon,100,Archivo) != NULL){
      Renglon[strlen(Renglon)] = '\0';
      sscanf(Renglon,"%c, %lf", &Letra, &Probabilidad);
      InsertarArbol(Raiz, Probabilidad, Letra);
    }
  }
}

void InsertarArbol(TipoNodo **Raiz, double Probabilidad, char Letra){
  TipoNodo *Avanza, *Nuevo;
  Avanza = *Raiz;
  if((Nuevo = (TipoNodo *)malloc(sizeof(TipoNodo))) == NULL){
    printf("No hay memoria\n");
    exit(0);
  }
  Nuevo->Probabilidad = Probabilidad;
  Nuevo->Letra = Letra;
  Nuevo->izq = NULL;
  Nuevo->der = NULL;

  while(Avanza != NULL){
    if(Probabilidad > Avanza->Probabilidad){ //muevete a la derecha
      if(Avanza->der != NULL)
	     Avanza = Avanza->der;
	    else{
	      Avanza->der=Nuevo;
	      return;
	    }
	  }
    if(Probabilidad <= Avanza->Probabilidad){ //muevete a la izquierda
      if(Avanza->izq != NULL)
        Avanza = Avanza->izq;
      else{
        Avanza->izq = Nuevo;
	      return;
	    }
	  }
  }
  Avanza = Nuevo;
  *Raiz = Avanza;
}

void ImprimirArbol(TipoNodo *Raiz){
  if(Raiz!=NULL){
    ImprimirArbol(Raiz->izq);
    printf("%c\n",Raiz->Letra);
    ImprimirArbol(Raiz->der);
  }
}

void BorrarArbol(TipoNodo *Raiz){
  if(Raiz!=NULL){
    BorrarArbol(Raiz->izq);
    BorrarArbol(Raiz->der);
    free(Raiz);
  }
}
