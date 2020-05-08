#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#include "Socket.h"

/* 
   char tipo: el tipo de socket que quiere definir
      's' para "stream"
      'd' para "datagram"
   bool ipv6: si queremos un socket para IPv6
 */
Socket::Socket(char tipo, bool ipv6)
{
    this->ipv6 = ipv6;
    
    int domain = AF_INET;
    if (ipv6) domain = AF_INET6;
    
    int type = SOCK_STREAM;
    if (tipo == 'd') type = SOCK_DGRAM;
    
    idSocket = socket(domain, type, 0);
    
    if(idSocket == -1)
        perror("socket");
}

int Socket::Bind(int port) 
{
    if (ipv6 == true)
    {
        printf("IPV6 Bind not supported.\n");
        return -1;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    
    int result = bind(idSocket, (struct sockaddr *) &addr, sizeof(addr));
    
    if (result == -1)
        perror("bind");
    
    return result;
}

int Socket::Listen(int backlog)
{
    int result = listen(idSocket, backlog);
    
    if (result == -1)
        perror("listen");
    
    return result;
}

Socket* Socket::Accept() 
{
    Socket* s = (Socket*)malloc(sizeof(Socket)); 
    
    socklen_t size = sizeof(s->addr);
    int fd_s = accept(idSocket, (struct sockaddr *) &s->addr, &size);
    
    if (fd_s == -1) 
    {
        perror("Connection failed....\n");
        return NULL;
    }
    
    s->SetIDSocket(fd_s);
    printf("Got client connection...\n");
    
    return s;
}

int Socket::Read(char* buf, int count)
{
    memset(buf, 0, count);
    int result = read(idSocket, buf, count - 1);
    if (result == -1) 
        perror("read");
    
    return result;
}

int Socket::Write(char* buf, int count)
{
    int result = write(idSocket, buf, count);
    if (result == -1) 
        perror("write");
        
    return result;
}


/*
   char * hostip: direccion del servidor, por ejemplo "www.ecci.ucr.ac.cr"
   int port: ubicacion del proceso, por ejemplo 80
 */
int Socket::Connect(const char * hostip, int port) 
{
    if (inet_pton(AF_INET, hostip, &addr.sin_addr) <= 0)
    {
        printf("Direccion Invalida. Direccion no soportada.\n");
        return -1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    int result = connect(idSocket, (struct sockaddr *) &addr, sizeof(addr));
    
    if (result == -1)
        perror("connect");
    
    return result;

}


void Socket::SetIDSocket(int id){
    idSocket = id;
}

Socket::~Socket()
{
    Close();
}


void Socket::Close()
{
    int result = close(idSocket);
    if (result == -1)
        perror("close");
}
