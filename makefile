RM = rm -rf

CC=g++

SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin

CFLAGS = -Wall -pedantic -ansi -std=c++17

all: dir auxiliar sequencial threads processos

debug: CFLAGS += -g -O0 -pg
debug: auxiliar sequencial threads processos

sequencial: $(OBJ_DIR)/sequencial.o $(OBJ_DIR)/matrix.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

threads: $(OBJ_DIR)/threads.o $(OBJ_DIR)/matrix.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^ -pthread

processos: $(OBJ_DIR)/processos.o $(OBJ_DIR)/matrix.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

auxiliar: $(OBJ_DIR)/auxiliar.o $(OBJ_DIR)/matrix.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/sequencial.o: $(SRC_DIR)/sequencial.cpp
	$(CC) -c $(CFLAGS) -o $@ $<	

$(OBJ_DIR)/threads.o: $(SRC_DIR)/threads.cpp 
	$(CC) -c $(CFLAGS) -o $@ $<	-pthread

$(OBJ_DIR)/processos.o: $(SRC_DIR)/processos.cpp
	$(CC) -c $(CFLAGS) -o $@ $<	

$(OBJ_DIR)/auxiliar.o: $(SRC_DIR)/auxiliar.cpp
	$(CC) -c $(CFLAGS) -o $@ $<	

$(OBJ_DIR)/matrix.o: $(SRC_DIR)/matrix.cpp
	$(CC) -c $(CFLAGS) -o $@ $<	

dir:
	mkdir -p bin build
	
clean: dir
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*