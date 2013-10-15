CC = gcc
INCLUDE = include
SRC = src
CFLAGS = -Wall -I$(INCLUDE) -c 
LFLAGS = -lstdc++
OBJ = obj
OBJS = $(OBJ)/node.o $(OBJ)/slpa.o $(OBJ)/main.o $(OBJ)/graph.o
BIN = bin

all: release

release: CFLAGS += -O3
release: LFLAGS += -s -O3
release: proj1

debug: CFLAGS += -g
debug: proj1

proj1: $(OBJS) | $(BIN)
	$(CC) $(LFLAGS) $(OBJ)/*.o -o $(BIN)/proj1
	ln -sf $(BIN)/proj1 proj1

$(OBJ)/node.o: $(INCLUDE)/error.h $(INCLUDE)/Node.h $(INCLUDE)/Graph.h $(SRC)/Node.cpp | $(OBJ)
	$(CC) $(CFLAGS) $(SRC)/Node.cpp -o $(OBJ)/node.o

$(OBJ)/slpa.o: $(INCLUDE)/error.h $(INCLUDE)/Node.h $(INCLUDE)/Graph.h $(INCLUDE)/SLPA.h $(SRC)/SLPA.cpp
	$(CC) $(CFLAGS) $(SRC)/SLPA.cpp -o $(OBJ)/slpa.o

$(OBJ)/main.o: $(INCLUDE)/error.h $(INCLUDE)/Node.h $(INCLUDE)/Graph.h $(INCLUDE)/SLPA.h
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/graph.o: $(INCLUDE)/error.h $(INCLUDE)/Node.h $(INCLUDE)/Graph.h $(SRC)/Graph.cpp
	$(CC) $(CFLAGS) $(SRC)/Graph.cpp -o $(OBJ)/graph.o

$(BIN):
	mkdir bin

$(OBJ):
	mkdir obj

clean:
	rm -Rf $(OBJ) $(BIN)
	rm -f proj1
