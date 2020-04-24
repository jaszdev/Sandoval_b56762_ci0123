/*
  Calcula el numero PI utilizando una serie "infinita"
  Debe recibir la cantidad de iteraciones como parametro
  pi = (-1)^i x 4/(2xi + 1)

  viernes 24 de abril, 2020
  Javier Sandoval Zamora  
  B56762	

  PiPorSeries usando Buzon
   
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include "Buzon.h"

struct msg 
{
    long type;
    double result;
};

/*
   Realiza la acumulacion de terminos desde una posicion inicial hasta un termino final
*/
double calcularSumaParcialPi(Buzon b, int proceso, long inicial, long terminos ) {
    double casiPi = 0;
    double alterna = 4;
    long divisor = 0;
    long termino;

    for ( termino = inicial; termino < terminos; termino++ ) {
        divisor = termino + termino + 1;		// 2 x termino + 1
        casiPi += alterna/divisor;		// 4 / (2xi + 1)
        alterna *= -1;				// Pasa de 4 a -4 y viceversa, para realizar la aproximacion de los terminos
    }
    // casi pi 
    
    struct msg message;
    message.type = 1;
    message.result = casiPi;
    b.Enviar(&message, sizeof(struct msg) - sizeof(long));
    
    exit( 0 );
}


int main( int argc, char ** argv ) {
    Buzon b;    
    
    long terminos, inicio, fin;
    int proceso;
    int pid;

    terminos = 1000000;
    if ( argc > 1 ) {
        terminos = atol( argv[ 1 ] );
    }

    for ( proceso = 0; proceso < 10; proceso++ ) {
        inicio = proceso * terminos/10;
        fin = (proceso + 1) * terminos/10;
        pid = fork();
        if ( ! pid ) {
            calcularSumaParcialPi(b, proceso, inicio, fin );
        } else {
            printf("Creating process %d: starting value %ld, finish at %ld\n", pid, inicio, fin );
        }
    }

    for (proceso = 0; proceso < 10; proceso++) {
        int status;
        pid_t pid = wait( &status );
    }

    int msgsize = sizeof(struct msg) - sizeof(long);
    struct msg message;
    int results = 0;
    double casiPi = 0;
    while (results < 10) 
    {
        if (b.Recibir(&message, msgsize, 1) != -1) {
            casiPi += message.result;
            results++;
        }
    }

    printf( "Valor calculado de Pi es \033[91m %g \033[0m con %ld terminos\n", casiPi, terminos );

}
