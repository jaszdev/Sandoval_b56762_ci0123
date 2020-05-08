output: server client

server: MirrorServerTest.o Socket.o
	g++ MirrorServerTest.o Socket.o -o server

MirrorServerTest.o: MirrorServerTest.cc
	g++ -c MirrorServerTest.cc

client: MirrorClientTest.o Socket.o
	g++ MirrorClientTest.o Socket.o -o client

MirrorClientTest.o: MirrorClientTest.cc
	g++ -c MirrorClientTest.cc

Socket.o: Socket.cc Socket.h
	g++ -c Socket.cc

clean:
	rm *.o server client
