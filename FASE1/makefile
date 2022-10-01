CC = gcc
BIN_dir = binary
INC_dir = include
OBJ_dir = object
SRC_dir = source
OBJECTOS = data.o entry.o tree.o

data.o = data.h
test_data.o = data.h
entry.o = entry.h
test_entry.o = entry.h
tree.o = tree.h tree-private.h
test_tree.o = tree.h tree-private.h



CFLAGS = -Wall -I $(INC_dir) -g
LIBS = -lrt -lpthread

vpath %.o $(OBJ_dir)

test_data: data.o test_data.o
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJECTOS)) -o $(BIN_dir)/$@

test_entry: entry.o test_entry.o
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJECTOS)) -o $(BIN_dir)/$@

test_tree: tree.o test_tree.o
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJECTOS)) -o $(BIN_dir)/$@

%.o: $(SRC_dir)/%.c $($@)
	$(CC) $(CFLAGS) -o $(OBJ_dir)/$@ -c $<

clean:
	rm –f $(OBJ_dir)/*.o
	rm –f $(BIN_dir)/*