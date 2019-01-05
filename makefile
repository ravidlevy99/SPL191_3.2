CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -pthread -lboost_filesystem -lboost_thread

all: BGSclient
	g++ -o bin/BGSclient bin/connectionHandler.o bin/Main.o bin/SendToServerTask.o bin/ReadFromServerTask.o $(LDFLAGS)

BGSclient: bin/connectionHandler.o bin/Main.o bin/SendToServerTask.o bin/ReadFromServerTask.o
	
bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp
	
bin/Main.o: src/Main.cpp
	g++ $(CFLAGS) -o bin/Main.o src/Main.cpp
	
bin/SendToServerTask.o: src/SendToServerTask.cpp
	g++ $(CFLAGS) -o bin/SendToServerTask.o src/SendToServerTask.cpp	
	
bin/ReadFromServerTask.o: src/ReadFromServerTask.cpp
	g++ $(CFLAGS) -o bin/ReadFromServerTask.o src/ReadFromServerTask.cpp
	
.PHONY: clean
clean:
	rm -f bin/*
