CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=gnu11 -fno-builtin

UNITY_DIR := unity/src
BIN_DIR := build
TARGET := $(BIN_DIR)/tests_runner

PROJECT_DIR := ..
TEST_SOURCES := test_runner.c test_sanity.c test_tictactoe.c test_common.c test_stubs.c
GAME_SOURCES := $(PROJECT_DIR)/src/tictactoe.c $(PROJECT_DIR)/src/common.c
UNITY_SOURCES := $(UNITY_DIR)/unity.c
SOURCES := $(TEST_SOURCES) $(GAME_SOURCES) $(UNITY_SOURCES)

INCLUDES := -I$(UNITY_DIR) -I$(PROJECT_DIR)/src/include

.PHONY: all run clean

all: $(TARGET)
	./$(TARGET)

run: all

$(TARGET): $(SOURCES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)

clean:
	rm -rf $(BIN_DIR)
