SRC_DIR = ../src
OBJ_DIR = ../bin/debug
RELEASE_DIR = ../bin/release
INCLUDE_DIR = ../include
CC = gcc

SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LDFLAGS = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
INCLUDE = -I$(INCLUDE_DIR)

TARGET = game

$(TARGET): $(OBJ)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -g -c -o $@ $< $(INCLUDE)

.PHONY: clean run
clean:
	rm -rf *.o $(OBJ_DIR)/*.o $(RELEASE_DIR)/$(TARGET)
	
run:
	(cd ./$(RELEASE_DIR) && ./$(TARGET))
