output: pruebaSem.o Semaforo.o
	g++ pruebaSem.o Semaforo.o -o prueba

pruebaSem.o: pruebaSem.cc
	g++ -c pruebaSem.cc

Semaforo.o: Semaforo.cpp Semaforo.h
	g++ -c Semaforo.cpp

clean:
	rm *.o prueba
