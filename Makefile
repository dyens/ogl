CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-O3 -pedantic -Wall -Wextra -std=c++2b -ggdb

LDFLAGS=-Iinclude -Iglm -lglfw -ldl

SRCS=main.cpp
OBJS=main.o shader.o utils.o

all: main

main: main.o shader.o utils.o texture.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o main main.o glad.c shader.o utils.o texture.o

main.o: main.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -c main.cpp

shader.o: src/shader.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -c src/shader.cpp

texture.o: src/texture.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -c src/texture.cpp

utils.o: src/utils.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -c src/utils.cpp

clean:
	$(RM) $(OBJS)

