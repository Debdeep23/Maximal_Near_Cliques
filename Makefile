CC=gcc
CXX=g++
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)

all: convert-to-zero-base maximal-k-plex

convert-to-zero-base: convert-to-zero-base.cpp
	$(CXX) -o zero-base convert-to-zero-base.cpp

maximal-k-plex: maximal-k-plex.o bkplex.o graph.o
	$(CXX) -o maximal-k-plex maximal-k-plex.o bkplex.o graph.o

maximal-k-plex.o: maximal-k-plex.cpp
	$(CXX) -c maximal-k-plex.cpp

bkplex.o: bkplex.cpp bkplex.h
	$(CXX) -c bkplex.cpp bkplex.h

graph.o: graph.cpp graph.h
	$(CXX) -c graph.cpp graph.h

clean:
	rm -f *.o *.gch maximal-k-plex
