OUTPUT = main
DES_SRC_DIR = src
MAKE_COMMAND = make

CURRENT_DIR = $(shell pwd)

OBJ_DIR = obj
BIN_DIR = bin

SRCS := main.c
OBJS = $(SRCS:%.c=%.o)
TARGET_OBJ = $(OBJ_DIR)/$(OBJS)

INCLUDE_DIR = $(DES_SRC_DIR)/include

INCLUDE_FLAGS = -I$(INCLUDE_DIR)
LIB_DIR = $(CURRENT_DIR)/lib

DES_LIB_NAME = des.so
DES_LIB = $(LIB_DIR)/$(DES_LIB_NAME)

CC = /usr/bin/gcc

LINKER_FLAGS = -L$(LIB_DIR)

all: prepare des_lib $(OUTPUT) 

$(OUTPUT): $(SRCS)
	gcc -o $(BIN_DIR)/$@ $< $(DES_LIB) $(INCLUDE_FLAGS) $(LINKER_FLAGS)

des_lib:
	cd src && make all

prepare:
	mkdir -p $(LIB_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir $(BIN_DIR)

clean:
	rm -rf lib
	rm -rf obj
	rm -rf bin
	cd src && make clean