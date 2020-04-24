output: pruebaShM.o Semaforo.o
	g++ pruebaShM.o Semaforo.o -o prueba

pruebaShM: pruebaShM.cc
	g++ -c pruebaShM.cc

Semaforo.o: Semaforo.cpp Semaforo.h
	g++ -c Semaforo.cpp

clean:
	rm *.o prueba
