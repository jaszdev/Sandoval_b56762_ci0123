#ifndef Socket_h
#define Socket_h

#include <netinet/in.h>

class Socket {

public:
    Socket(char = 's', bool = false);
    //Socket(int);
    ~Socket();
    int Connect(const char *, int);
    //int Connect(const char *, char *);
    void Close();
    int Read(char*, int);
    int Write(char*, int);
    int Listen(int);
    int Bind(int);
    Socket * Accept();
    //int Shutdown(int);
    void SetIDSocket(int);
    
    struct sockaddr_in addr;
    
private:
    int idSocket;
    bool ipv6;
    
};

#endif