CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-O3 -pedantic -Wall -Wextra -std=c++2b -ggdb

LDFLAGS=-Iinclude -Iglm -lglfw -ldl

BUILD_DIR=build
SRC_DIR=src
OBJECTS = $(BUILD_DIR)/main.o \
	$(BUILD_DIR)/shader.o \
	$(BUILD_DIR)/texture.o \
	$(BUILD_DIR)/utils.o


all: $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(OBJECTS) $(SRC_DIR)/glad.c -o $(BUILD_DIR)/main

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ -c $< 

clean:
	$(RM) $(BUILD_DIR)/*

