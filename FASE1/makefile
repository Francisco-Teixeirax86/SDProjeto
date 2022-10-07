BIN_DIR = binary
INC_DIR = include
OBJ_DIR = object
SRC_DIR = source
OBJECTOS = data.o entry.o tree.o serialization.o
data.o =
entry.o = data.h
tree.o = entry.h data.h tree-private.h
serialization.o = entry.h data.h
test_data.o = data.h
test_entry.o = entry.h data.h
test_tree.o = tree-private.h tree.h entry.h data.h
CC = gcc
CFLAGS = -Wall -g -I 
LIBS = -lrt -lpthread

all: data.o entry.o tree.o serialization.o test_data.o test_entry.o test_tree.o test_data test_entry test_tree

test_data: data.o test_data.o
	$(CC) $(addprefix $(OBJ_DIR)/,$^) -o $(BIN_DIR)/$@

test_entry: data.o entry.o test_entry.o
	$(CC) $(addprefix $(OBJ_DIR)/,$^) -o $(BIN_DIR)/$@

test_tree: data.o entry.o tree.o test_tree.o
	$(CC) $(addprefix $(OBJ_DIR)/,$^) -o $(BIN_DIR)/$@

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIR) -o $(OBJ_DIR)/$@ -c $<

clean:
	rm –f $(OBJ_DIR)/.o
	rm –f $(BIN_DIR)/
