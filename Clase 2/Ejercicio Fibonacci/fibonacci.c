#include <stdio.h>
#include <time.h>

void Fibonacci(int rango);

int main(void)
{
  int rango;
  printf("Serie Fibonacci\n");
  printf("Escribe el rango de iteraciones:\n");
  scanf(" %d",&rango);
  Fibonacci(rango);
}
void Fibonacci(int rango)
{
  FILE *Archivo;
  Archivo = fopen("grafica.txt","wt");
  clock_t Start = clock();
  double Time = 0.0;
  long long int num=0,num2=1,res=1;
  for(int i=0;i<rango;i++){
    printf("%lld\n",res);
    res = num+num2;
    num = num2;
    num2 = res;
    if(i>=9){
    fprintf(Archivo,"%d, ",i+1);
    clock_t End = clock();
    Time = (double) (End-Start) /CLOCKS_PER_SEC;
    fprintf(Archivo,"%f\n",Time);
    }
  }
  fclose(Archivo);
}
