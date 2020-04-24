#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

#include "Buzon.h"

#define S_IRUSR 00400 /* read permission: owner */
#define S_IWUSR 00200 /* write permission: owner */

Buzon::Buzon()
{
    pid = getpid();
    //key_t llave = ftok("/bin/ls", 123456);
    id = msgget(123456, IPC_CREAT | S_IRUSR | S_IWUSR);
	if(id == -1) {
		printf("Error al crear buzon");
    }
}

Buzon::~Buzon()
{
    //if (getpid() == pid)
    //    msgctl(id, IPC_RMID, 0);
}

int Buzon::Enviar(void * mensaje, int len)
{
    return msgsnd(id, mensaje, len, 0);
}

int Buzon::Enviar(const char * mensaje, int veces, long tipo)
{
    struct { long type; char mensaje[32]; int veces; } msg;
    msg.type = tipo;
    //msg.mensaje[0] = *mensaje;
    strcpy(msg.mensaje, mensaje);
    msg.veces = veces;
    return msgsnd(id, &msg, sizeof(msg) - sizeof(long), 0);
}

int Buzon::Recibir(void * mensaje, int len, long tipo)
{
    return msgrcv(id, mensaje, len, tipo, 0);
}

int Buzon::Recibir(char * mensaje, int * veces, long tipo) 
{
    struct { long type; char mensaje[32]; int veces; } msg;
    int size = sizeof(msg) - sizeof(long);
    int result = msgrcv(id, &msg, size, tipo, IPC_NOWAIT);
    if (result != -1) 
    {
        strcpy(mensaje, msg.mensaje);
        *veces = msg.veces;
        return result;
    }
    return -1;
}