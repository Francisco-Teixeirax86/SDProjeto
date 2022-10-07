CC = gcc
INC_DIR = include
OBJ_DIR = object
BIN_DIR = binary
SRC_DIR = source

OBJETOS = data.o entry.o tree.o

data.o = data.h
entry.o = data.h entry.h
tree.o = entry.h data.h tree.h tree-private.h
serialization.o = data.h serialization.h entry.h
test_data.o = data.h
test_entry.o = entry.h data.h
test_tree.o = tree-private.h tree.h entry.h data.h serialization.h

CFLAGS = -Wall -g -I
LIBS = -lrt -lpthread

all: data.o entry.o tree.o serialization.o test_data.o test_entry.o test_tree.o test_data test_entry test_tree

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIR) -o $(OBJ_DIR)/$@ -c $<

test_data: data.o test_data.o
	$(CC) $(addprefix $(OBJ_DIR)/,$^) -o $(BIN_DIR)/$@

test_entry: data.o entry.o test_entry.o
	$(CC) $(addprefix $(OBJ_DIR)/,$^) -o $(BIN_DIR)/$@

test_tree: data.o entry.o tree.o test_tree.o serialization.o
	$(CC) $(addprefix $(OBJ_DIR)/,$^) -o $(BIN_DIR)/$@

clean:
	rm –f $(OBJ_DIR)/.o
	rm –f $(BIN_DIR)/
