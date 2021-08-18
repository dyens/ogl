CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-O3 -pedantic -Wall -Wextra -std=c++2b -g

LDFLAGS=-Iinclude -Iglm -lglfw -ldl

SRCS=main.cpp
OBJS=main.o

all: main

main: main.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o main main.o glad.c

main.o: main.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -c main.cpp

clean:
	$(RM) $(OBJS)

