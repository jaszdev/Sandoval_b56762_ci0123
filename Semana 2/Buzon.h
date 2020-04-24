#include <sys/types.h>

class Buzon {

public:
    Buzon();
    ~Buzon();
      
    int Enviar(void * mensaje, int len);
    int Enviar(const char * mensaje, int veces, long tipo);  
    
    int Recibir(void * mensaje, int len, long tipo);
    int Recibir(char * mensaje, int * veces, long tipo);

private:
    int id;
    pid_t pid; // Id del proceso que crea el buzon
};
