CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-O3 -pedantic -Wall

LDFLAGS=-Iinclude
LDLIBS=-lglfw 

SRCS=main.cpp
OBJS=main.o

all: main

main: main.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o main main.o

main.o: main.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c main.cpp glad.c

clean:
	$(RM) $(OBJS)

