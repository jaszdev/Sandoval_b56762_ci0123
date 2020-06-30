#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <time.h>  

sem_t mutex; // semaforo global
int MAX_MONKEYS = 2; // maximo de monos en la cuerda
int J = 4; // maximo de monos que puede cruzar de un lado a otro sin cambiar de direccion
int j = 0; // contador de monos cruzando en una sola direccion
int monkeys_on_rope = 0; // monos en la cuerda
int monkes_left; // monos que quedan por cruzar

// direccion del movimiento de los monos
// -1: derecha a izquiera
// 1: izquiera a derecha
int movement_direction = 0;

struct monkey_info_t 
{
    int id;
    // lado del barranco 
    // -1: izquierda
    // 1: derecha
    int side;
};

void* monkey(void* arg) 
{ 
    monkey_info_t * info = (monkey_info_t *) arg;

    int tId = info->id;
    int side = info->side;
    int myDirection = side * -1; // la direccion es el contrario del lado del mono

    time_t t;
    srand((unsigned) time(&t));

    bool couldCross = false;

    while (!couldCross) 
    {
        sleep(1 + rand() % 5); // tiempo de espera, de 1 a 6 segundos
        sem_wait(&mutex);
        if (monkeys_on_rope < MAX_MONKEYS)
        {   
            if (monkeys_on_rope == 0 && movement_direction == 0) // primer mono en cruzar
            {
                movement_direction = myDirection;
                couldCross = true;
            }
            else 
            {
                if (monkeys_on_rope == 0 && myDirection != movement_direction) // se va a cambiar la direccion del movimiento
                {
                    j = 0; // resetear contador
                    couldCross = true;
                    movement_direction = myDirection;
                }
                else 
                {
                    if (movement_direction == myDirection) 
                    {
                        if (j < J)
                        {
                            couldCross = true;
                        }
                        else
                        {
                            if (monkes_left < J) // si los monos que quedan son menor a J, j no se toma en cuenta para cruzar
                            {
                                couldCross = true;
                            }
                            else {
                                printf("Mono #%d: Ya no pueden pasar mas monos en mi direccion :(.\n", tId);
                            }
                        }
                    }
                    else 
                    {
                        printf("Mono #%d: La cuerda no esta llena, pero no va en mi direccion.\n", tId);
                    }
                }
            }
            
            if (couldCross) 
            {
                monkeys_on_rope++;
                j++;
            }
        }
        else 
        {
            printf("Mono #%d: La cuerda esta llena :(.\n", tId);
        }
        
        sem_post(&mutex);
    }

    char * sDir = myDirection == -1 ? (char *)"derecha a izquierda" : (char *)"izquiera a derecha";
    printf("Mono #%d: Cruzando la cuerda de %s :). Monos en la cuerda: %d.\n", tId, sDir, monkeys_on_rope);
    sleep(1 + rand() % 4); // tiempo para cruzar la cuerda
    printf("Mono #%d: Cruze la cuerda :).\n", tId);

    sem_wait(&mutex);
    monkes_left--;
    monkeys_on_rope--;
    sem_post(&mutex);
} 
  
  
int main(int argc, char *argv[]) 
{ 
    time_t t;
    srand((unsigned) time(&t));

    sem_init(&mutex, 0, 1);
    int numThreads = 10;

    // tomar parametros
    if (argc == 4)
    {
        //printf("Args 1: %s, 2: %s, 3: %s\n", argv[1], argv[2], argv[3]);
        numThreads = atoi(argv[1]);  
        MAX_MONKEYS = atoi(argv[2]);
        J = atoi(argv[3]);  
    }
    pthread_t threads[numThreads];
    monkes_left = numThreads;

    printf("Numero de monos: %d\n", numThreads);
    printf("Numero maximo de monos en la cuerda: %d\n", MAX_MONKEYS);
    printf("Numero maximo de monos que pueden cruzar en una direccion: %d\n", J);
    printf("\n");
    printf("\n");

    printf("Simulacion:\n");

    printf("\n");
    printf("\n");

    for(int i = 1; i <= numThreads; i++)
    {
        pthread_t t;
        struct monkey_info_t * monkey_info = (monkey_info_t *)calloc(1, sizeof(struct monkey_info_t));
        monkey_info->id = i;
        //int random = rand() % 2; 
        // int side = random == 0 ? -1 : 1;
        int side = i % 2 == 0 ? -1 : 1;
        monkey_info->side = side;
        pthread_create(&t, NULL, monkey, monkey_info);
        char * sSide = side == -1 ? (char *) "Izquierda" : (char *) "Derecha";
        printf("Creado Mono #%d Lado: %s\n", i, sSide);
        threads[i - 1] = t;
    }
    printf("\n");
    printf("\n");

    for(int i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex);
    return 0; 
} 