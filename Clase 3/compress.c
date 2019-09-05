#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ComprimirDatos(char *argv[],int ContNum,int *Num);
void ExtraerDatos(int ContNum,int Num,int Extract[]);
void ImprimirDatos(int ContNum, int Extract[]);
void Operaciones(int ContNum,int Extract[]);
int main (int argc, char *argv[])
{
  int Num=0,ContNum,Opcion=0,Extract[4];
  ContNum = argc-1;
  if(argc > 5 || argc == 1)
    {
      printf("Los parámetros no son los adecuados\n");
      exit(0);
    }
  else
    {
      ComprimirDatos(argv,ContNum,&Num);
      ExtraerDatos(ContNum,Num,Extract);
      do
	{
	  system("clear");
	  printf("Compresor de datos:\n");
	  printf("¿Qué desea hacer?\n");
	  printf("1.- Imprimir Numeros.\n");
	  printf("2.- Realizar Operaciones.\n");
	  printf("3.- Salir del programa.\n");
	  printf("Opción: ");
	  scanf(" %d",&Opcion);
	  switch(Opcion)
	    {
	    case 1:
	      ImprimirDatos(ContNum,Extract);
	      break;
	    case 2:
	      if(ContNum>1)
		Operaciones(ContNum,Extract);
	      else
		printf("No es posible realizar operaciones, sólo existe un número\n");
	      break;
	    case 3:
	      system("clear");
	      printf("Saliendo del programa...\n");
	      exit(0);
	      break;
	    default:
	      printf("Opción invalida, intente de nuevo\n");
	      break;
	      
	    }
	  printf("Presione Enter para continuar...\n");
	  __fpurge(stdin);
	  getchar();
	}
      while(Opcion!=3);
    }
}  

void ComprimirDatos(char *argv[],int ContNum,int *Num)
{
  int Temp, Res=12; 
  for (int i=0; i<ContNum; i++)
    {
      sscanf(argv[i+1]," %d",&Temp);
      if(Temp>=0 && Temp<=15)
	{
	  //printf("%d, ",Temp);
	  Temp <<= Res;
	  *(Num)|=Temp;
	  Res-=4;
	  //printf("%d\n",*Num); 
	}
      else
	{
	  printf("Error, exceso de rango [Números aceptados: 0-15]\n");
	  exit(0);
	}
    }
}
void ExtraerDatos(int ContNum,int Num,int Extract[])
{
  int Temp, Res=12;
  for (int i=0; i<ContNum; i++)
    {
      if(i==0)
	{
	  Temp=Num;
	  Extract[i] = Temp >> Res;
	}
      else
	{
	  Temp = Extract[i-1] << Res;
	  Num = Num ^ Temp;
	  Temp = Num;
	  Res-=4;
	  Extract[i]=Temp>>Res;
	}
    }
}
void ImprimirDatos(int ContNum, int Extract[])
{
  char Letra='A';
  for(int i=0; i<ContNum;i++)
    {
      printf("Número en %c es: %d\n",Letra,Extract[i]);
      Letra+=1;
    }
}
void Operaciones(int ContNum,int Extract[])
{
  float Resultado=Extract[0];
  char Operacion;
  system("clear");
  printf("¿Qué operación desea hacer?\n");
  printf("Suma (+)\n");
  printf("Resta (-)\n");
  printf("Multiplicación (x)\n");
  printf("División (/)\n");
  printf("Opción: ");
  scanf(" %c",&Operacion);
  switch(Operacion)
    {
    case '+':
      for(int i= 1; i<ContNum;i++)
	Resultado+=Extract[i];
      printf("El resultado es: %.1f\n",Resultado);
      break;
    case '-':
      for(int i= 1; i<ContNum;i++)
	Resultado-=Extract[i];
      printf("El resultado es: %.1f\n",Resultado);
      break;
    case 'x':
      for(int i= 1; i<ContNum;i++)
	Resultado*=Extract[i];
      printf("El resultado es: %.1f\n",Resultado);
      break;
    case '/':
      for(int i= 1; i<ContNum;i++)
	Resultado/=Extract[i];
      printf("El resultado es: %f\n",Resultado);
      break;
    default:
      printf("Opción inválida...\n");
      break;
    }
}
