all: pi_shm pi_buzon enviarConClases recibirConClases

pi_shm: PiPorSeries.c
	g++ -o pi_shm PiPorSeries.c

pi_buzon: PiPorSeries2.o Buzon.o
	g++ PiPorSeries2.o Buzon.o -o pi_buzon

PiPorSeries2.o: PiPorSeries2.c
	g++ -c PiPorSeries2.c

enviarConClases: enviarConClases.o Buzon.o
	g++ enviarConClases.o Buzon.o -o enviarConClases

enviarConClases.o: enviarConClases.cc
	g++ -c enviarConClases.cc

recibirConClases: recibirConClases.o Buzon.o
	g++ recibirConClases.o Buzon.o -o recibirConClases

recibirConClases.o: recibirConClases.cc
	g++ -c recibirConClases.cc

Buzon.o: Buzon.h Buzon.cpp
	g++ -c Buzon.cpp

clean:
	rm *.o enviarConClases pi_buzon pi_shm recibirConClases
