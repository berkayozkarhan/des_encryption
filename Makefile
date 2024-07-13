CURRENT_DIR = $(shell pwd)
BUILD_DIR = $(CURRENT_DIR)/build

MODULE_NAME = app

APP_OBJ_DIR = $(BUILD_DIR)/$(MODULE_NAME)/obj
APP_BIN_DIR = $(BUILD_DIR)/$(MODULE_NAME)/bin

APP_DIRECTORIES := $(APP_OBJ_DIR) $(APP_BIN_DIR)

MODULE_OUTPUT = $(APP_BIN_DIR)/main

DES_MODULE_NAME = des

DES_SRC_DIR = src/$(DES_MODULE_NAME)
DES_INCLUDE_DIR = $(DES_SRC_DIR)/include

DES_MODULE_DIR = $(BUILD_DIR)/$(DES_MODULE_NAME)
DES_LIB_DIR = $(DES_MODULE_DIR)/lib


DES_LIB_NAME = des.so
DES_LIB = $(DES_LIB_DIR)/$(DES_LIB_NAME)


SRCS := main.c
OBJS := $(patsubst %.c, $(APP_OBJ_DIR)/%.o, $(SRCS))

CC = /usr/bin/gcc
LINKER_FLAGS = -L$(DES_LIB_DIR)
INCLUDE_FLAGS = -I$(DES_INCLUDE_DIR)


all: prepare modules $(MODULE_OUTPUT)


$(MODULE_OUTPUT): $(OBJS)
	$(CC) -o $@ $< $(DES_LIB) $(INCLUDE_FLAGS) $(LINKER_FLAGS)


$(OBJS): $(SRCS)
	$(CC) -c -o $@ $(INCLUDE_FLAGS) $<


modules:
	cd src && make all


prepare:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(APP_DIRECTORIES)


clean:
	rm -rf $(BUILD_DIR)