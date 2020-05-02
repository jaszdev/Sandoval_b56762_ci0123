#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h> 
#include <netdb.h> // servent struct
#include <errno.h>

#include "Socket.h"

#define SERVER_PORT 7002

/* 
   char tipo: el tipo de socket que quiere definir
      's' para "stream
      'd' para "datagram"
   bool ipv6: si queremos un socket para IPv6
 */
Socket::Socket( char tipo, bool ipv6 ) 
{
    this->ipv6 = ipv6;
    int domain;
    if (ipv6) 
        domain = AF_INET6;
    /*else 
        domain = AF_UNIX;*/
    else 
        domain = AF_INET;
    
    int type;
    if (tipo == 's')
        type = SOCK_STREAM;
    else 
        type = SOCK_DGRAM;
    
    idSocket = socket(domain, type, 0);
    
    if (idSocket == -1) 
        printf("Error al crear socket.\n");
    
}


Socket::~Socket(){
    Close();
}


void Socket::Close(){
    int result = close(idSocket);
    if (result == -1)
        printf("Error al cerrar el socket.\n");
}

/*
   char * hostip: direccion del servidor, por ejemplo "www.ecci.ucr.ac.cr"
   int port: ubicacion del proceso, por ejemplo 80
 */
int Socket::Connect( char * hostip, int port ) 
{
    if (inet_pton(AF_INET, hostip, &si.sin_addr) <= 0)
    {
        printf("Direccion Invalida. Direccion no soportada.\n");
        return -1;
    }
    
    si.sin_family = AF_INET;
    si.sin_port = htons(port);
    
    int result = connect(idSocket, (struct sockaddr *) &si, sizeof(si));
    
    if (result == -1)
        printf("No se pudo realizar la conexion.\n");
    
    return result;

}


/*
   char * hostip: direccion del servidor, por ejemplo "www.ecci.ucr.ac.cr"
   char * service: nombre del servicio que queremos acceder, por ejemplo "http"
 */
int Socket::Connect(char *host, char *service) {
    if (ipv6) 
    {
        si6.sin6_family = AF_INET6;
        
        int ip_r = inet_pton(AF_INET6, host, &si6.sin6_addr);
        if (ip_r == -1)
        {
            perror("Direccion Invalida. Direccion no soportada \n");
            return -1;
        }
        else
        {
            si6.sin6_port = htons(SERVER_PORT);
            
            int result = connect(idSocket, (struct sockaddr *) &si6, sizeof(si6));
            
            if (result == -1) {
                perror("No se pudo realizar la conexion.\n");
            }
            
            return result;
            
        }
    }
    
    printf("No se pudo realizar la conexion (ipv6 != true).\n");
    
    return -1;
}


int Socket::Read( char *text, int len ) 
{
    int result = read(idSocket, text, len);
    
    if (result == -1)
        printf("Error al leer.\n");
    
    return result;
}


int Socket::Write(char *text) {
    int result = send(idSocket, text, strlen(text), 0);
    
    if (result == -1)
        printf("Error al escribir.\n");
    
    return result;

}


int Socket::Listen( int queue ) {
    int result = listen(idSocket, queue);
    
    if (result != 0)
        printf("Could not listen.\n");
    
    return result;

}


int Socket::Bind( int port ) {
    su.sun_family = AF_UNIX;
    strcpy(su.sun_path, "/tmp/misocketunix");
    int result = bind(idSocket, (struct sockaddr *) &su, sizeof(su));
    
    if(result != 0) 
        printf("Could not bind.\n");
    
    return result;
}


Socket * Socket::Accept(){
    int longaddr = sizeof(su);
    //int sc;    
    return NULL;

}


int Socket::Shutdown( int mode ) {

    return -1;

}


void Socket::SetIDSocket(int id){

    idSocket = id;

}