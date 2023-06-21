CFLAGS := -Wall -Wextra -std=c++17 -Wno-type-limits -Wno-sign-compare
CXX := g++
CMD := $(CXX) $(CFLAGS)

BUILD_DIR := bin
SRC_DIR := .
OBJ_DIR := obj

SRC_DIRS := $(SRC_DIR) board game ui/web utils
SRC_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_FILES := $(wildcard tests/*.cpp)

ifeq ($(OS),Windows_NT)
MKDIR_P := mkdir
RM := rmdir /s /q
DEL := del /s /q
EXE_EXT := .exe
else
MKDIR_P := mkdir -p
RM := rm -rf
DEL := rm -rf
EXE_EXT :=
endif

chex: $(OBJ_FILES)
	$(MKDIR_P) $(BUILD_DIR)
	$(CMD) $(OBJ_FILES) -o $(BUILD_DIR)/chex$(EXE_EXT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(OBJ_DIR)
	$(CMD) -c $(CFLAGS) $< -o $@

chex/tests: $(TEST_FILES) $(OBJ_FILES)
	$(MKDIR_P) $(BUILD_DIR)
	$(CMD) $(TEST_FILES) $(OBJ_FILES) -o $(BUILD_DIR)/chex.test

format:
	clang-format -i $(SRC_FILES) $(wildcard */*.hpp)

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(BUILD_DIR)
	$(DEL) $(SRC_DIR)/*.o
	$(DEL) tests/*.o

all: chex

.PHONY: format all clean
