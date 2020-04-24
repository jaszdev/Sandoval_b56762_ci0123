#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "Semaforo.h"

#define S_IRUSR 00400
#define S_IWUSR 00200
#define PERMISOS S_IRUSR | S_IWUSR

Semaforo::Semaforo(int n) 
{

	key_t llave;
	llave = ftok("prueba", 1); // Crear la llave del grupo de semaforos con ftok
	if (llave != (key_t) -1) // Si la llave fue creada correctamente
	{
		id = semget(llave, 1, PERMISOS | IPC_CREAT); // Obtener id del grupo de semaforos
		if (id == -1)
		{
			printf("Error Semaforo::Semaforo()\n");
		}
	}
	//printf("Sem Id: %d\n", id);
	// Semaforo creado correctamente
}

Semaforo::~Semaforo()
{
	semctl(id, 0, IPC_RMID); // Destruir semaforo 0 del grupo id 
	// Se usa IPC_RMID para borrar todo el conjunto de semaforos
	// aunque solo haya uno en este caso
}

void Semaforo::Up(int semid, int nsem) 
{
	struct sembuf op_up = {0, 1, 0}; // Estructura de operacion 
	op_up.sem_num = nsem; // Asignar semaforo al cual se le quiere hacer la operacion
	int result = semop(semid, &op_up, 1);
	if (result != 0)
		printf("Error en Operacion Up");
}

void Semaforo::Down(int semid, int nsem) 
{
	struct sembuf op_down = {0, -1, 0}; // Estructura de operacion 
	op_down.sem_num = nsem; // Asignar semaforo al cual se le quiere hacer la operacion
	int result = semop(semid, &op_down, 1);
	if (result != 0)
		printf("Error en Operacion Down");
}

void Semaforo::Signal()
{
	Up(id, 0); // Pasar el semaforo a verde
}

void Semaforo::Wait()
{
	Down(id, 0);
}

