
OBJS = SRC/*.c SHODAN/SRC/*.c

CC = gcc

COMPILER_FLAGS = -Wall -pedantic

LINKER_FLAGS = -lSDL2 -lSDL2main -lm

OBJ_NAME = bin

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)