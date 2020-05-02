#include <stdio.h>
#include "Socket.h"

int main( int argc, char * argv[] ) {

   Socket s('s');
   char a[512];

   s.Connect((char *)"163.178.104.187", 80);
   s.Write((char *)"GET / HTTP/1.1\r\nhost: redes.ecci\r\n\r\n");
   s.Read(a, 512);
   printf("%s\n", a);
}