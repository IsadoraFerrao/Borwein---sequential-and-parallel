// Algoritmo de Borwein Paralelo - Cálculo do número PI
//Universidade de Sao Paulo - Sistemas Operacionais (2019)

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>

#define PRECISAO 33219280 //precisao utilizada para o calculo

long long int NUM_PONTOS;
long int numThreads;

float pi_final=0.0;
pthread_mutex_t mutexSum; //variavel mutexsum do tipo pthread_mutex
int indice;
long long total_all=0;

void *pi(void *threadid){

	long long int chunk;
	double pi = 0;
	double j = 0;
	
	chunk = NUM_PONTOS/numThreads; //divide os pedacos de execucao entre as threads disponiveis

	for(j=0;j<chunk;j++){
	    //pi += 2+2;
	    pi += (1 / (pow(16, j)) * ((120*j*j + 151*j + 47)/(512*j*j*j*j + 1024*j*j*j + 712*j*j + 194*j + 15))); //calculo do pi
	}

    //para tratar a sincronizacao utilizamos o bloqueio mutex
    
	pthread_mutex_lock(&mutexSum);   //bloqueia um objeto mutex
	pi_final += pi;
	pthread_mutex_unlock(&mutexSum); //libera um objeto mutex

	return NULL;
}

int main(int argc, char **argv){

    FILE *saida;
    saida = fopen("tempo.txt", "a");

	if (argc < 2) {
		printf ("Errado! Utilize: programa <threads> <input-size>\n\n \tE.g. -> ./programa 2 400000\n\n");
		exit(1);
	}

    /* TRATANDO AS ENTRADAS */
    
	NUM_PONTOS = strtoul(argv[2], NULL, 10); //n de iteracoes
	long int i;
	numThreads = atol(argv[1]);
	pthread_t threads[numThreads]; //vetor de threads do tipo pthread

    //Coleta de tempo
    clock_t start_t, end_t;
    double total_t;
    start_t = clock(); //Coleta Inicio
    
    /* CRIA A THREAD */
	for(i=1;i<=numThreads;i++){
		pthread_create(&threads[i], NULL, pi, (void *)i); 
	}
	
	/* RECEBE A ESTRUTURA DE CONTROLE DA THREAD */
	
	for(i=1;i<=numThreads;i++){
		pthread_join(threads[i], NULL); 
	}
	
	pi_final = pi_final/numThreads;
    end_t = clock(); //Coleta Final
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    /*RESULTADO*/
	printf("Pi = %lf\n", pi_final);	
    fprintf(saida, "%f\n", total_t);
	return 0;

}
