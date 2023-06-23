CFLAGS := -Wall -Wextra -std=c++17 -Wno-type-limits -Wno-sign-compare
CXX := g++
CMD := $(CXX) $(CFLAGS)

BUILD_DIR := bin
SRC_DIR := .
OBJ_DIR := obj

SRC_DIRS := $(SRC_DIR) board game ui/web utils ui/console
SRC_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_FILES := $(wildcard tests/*.cpp)

LIBS := lib/mongoose.cpp

ifeq ($(OS),Windows_NT) # ON WINDOWS

chex: $(OBJ_FILES)
	IF NOT EXIST $(BUILD_DIR) MKDIR $(BUILD_DIR) 
	$(CMD) $(OBJ_FILES) $(LIBS) -lws2_32 -o $(BUILD_DIR)/chex.exe

clean:
	IF EXIST $(BUILD_DIR) RMDIR /S /Q $(BUILD_DIR)
	IF EXIST $(OBJ_DIR) RMDIR /S /Q $(OBJ_DIR)

else # ON UNIX

chex: $(OBJ_FILES)
	mkdir -p $(BUILD_DIR)
	$(CMD) $(OBJ_FILES) -o $(BUILD_DIR)/chex

clean:
	rm -rf */*.o
	rm -rf $(BUILD_DIR) $(OBJ_DIR)

endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp

ifeq ($(OS),Windows_NT) 
	IF NOT EXIST $(OBJ_DIR) MKDIR $(OBJ_DIR) 
else
	mkdir -p $(OBJ_DIR)
endif

	$(CMD) -c $(CFLAGS) $< -o $@

chex/tests: $(TEST_FILES) $(OBJ_FILES)
	$(MKDIR_P) $(BUILD_DIR)
	$(CMD) $(TEST_FILES) $(OBJ_FILES) -o $(BUILD_DIR)/chex.test

format:
	clang-format -i $(SRC_FILES) $(wildcard */*.hpp)

all: chex

.PHONY: format all clean
