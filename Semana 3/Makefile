all: ipv4-test ipv6-test server

ipv4-test: ipv4-test.o Socket.o
	g++ ipv4-test.o Socket.o -o ipv4-test

ipv4-test.o: ipv4-test.c
	g++ -c ipv4-test.c

ipv6-test: ipv6-test.o Socket.o
	g++ ipv6-test.o Socket.o -o ipv6-test

ipv6-test.o: ipv6-test.c
	g++ -c ipv6-test.c

Socket.o: Socket.h Socket.cc
	g++ -c Socket.cc

server: server.o
	g++ server.o -o server

clean:
	rm *.o ipv4-test ipv6-test server
