#ifndef Socket_h
#define Socket_h

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

class Socket{

    public:
        Socket( char, bool = false );
        Socket( int );
        ~Socket();
        int Connect( char *, int );
        int Connect( char *, char * );
        void Close();
        int Read( char *, int );
        int Write( char *, int );
        int Write( char * );
        int Listen( int );
        int Bind( int );
        Socket * Accept();
        int Shutdown( int );
        void SetIDSocket( int );
        
    private:
        int idSocket;
        bool ipv6;
        struct sockaddr_un su;
        struct sockaddr_in si;
        struct sockaddr_in6 si6;
};

#endif
