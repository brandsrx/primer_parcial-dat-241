//   Realice un programa que tenga los métodos suma, resta, multiplicación, división en lenguaje c. Programe los mismo sin el uso de punteros.
#include<stdio.h>

int suma(int a,int b){
    return a+b;
}
int resta(int a,int b){
    return a-b;
}
int multiplicacion(int a, int b){
    return a*b;
}
float division(int a,int b){
    if(b==0) return 0.0;
    return (float) a/b;
}

int main(){

    int a = 10,b=4;

    printf("resultado de la suma: %d",suma(a,b));
    printf("\nresultado de la multipliacion: %d",multiplicacion(a,b));
    printf("\nresultado de la division: %d",division(a,b));
    printf("\nresultado de la resta: %d",resta(a,b));


    return 0;
}