MODULE_NAME = des

PROJECT_ROOT_DIR 	= ..
CURRENT_DIR 		= $(shell pwd)
SOURCE_DIR 			= $(CURRENT_DIR)
OBJ_DIR 			= $(CURRENT_DIR)/obj

INCLUDE_DIR 		= $(CURRENT_DIR)/include
OUTPUT_DIR 			= $(PROJECT_ROOT_DIR)/lib

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=%.o)
TARGET_OBJ = $(OBJ_DIR)/$(OBJS)

TARGET = $(MODULE_NAME).so

OUTPUT = $(MODULE_NAME).so

INCLUDE_FLAGS = -I$(INCLUDE_DIR)

COMPILER_FLAGS = -fPIC --shared 

CC = /usr/bin/gcc


all: prepare $(TARGET)

$(TARGET): $(TARGET_OBJ)
	$(CC) $(COMPILER_FLAGS) -o $(OUTPUT_DIR)/$@ $(TARGET_OBJ)

$(TARGET_OBJ): $(SRCS)
	$(CC) -c -o $(TARGET_OBJ) $(INCLUDE_FLAGS) $(SRCS)
	

prepare:
	mkdir -p ../lib
	mkdir -p obj
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OUTPUT_DIR)
	

