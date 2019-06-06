// Algoritmo de Borwein - Cálculo do número PI
//Universidade de Sao Paulo - Sistemas Operacionais (2019)

#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include<time.h>

#define PRECISAO 33219280 //precisao utilizada para o calculo

double pi(int precisao){
    int iter = 1000000000; //numero de iteracoes para computar a formula
    double pi = 0;
    double k = 0;
    
    
    for (k = 0; k < iter; k++){ 
        pi += (1 / (pow(16, k)) * ((120*k*k + 151*k + 47)/(512*k*k*k*k + 1024*k*k*k + 712*k*k + 194*k + 15))); //calculo do pi 
    }
    
    return pi;
}

int main() {
    double resp;
    FILE *saida;
    saida = fopen("tempo.txt", "a");
    
    //Coleta de tempo
    clock_t start_t, end_t;
    double total_t;
    start_t = clock(); //Coleta Inicio
    
    resp = pi(PRECISAO);
    
    printf("PI de Borwein = %f \n", resp);
    
	end_t = clock(); //Coleta Final
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    fprintf(saida, "%f\n", total_t);
    return 0;

}

