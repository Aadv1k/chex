CFLAGS = -Wall -Wextra -std=c++17
CXX = g++
CMD := $(CXX) $(CFLAGS)

board_files := board/board.o
game_files := game/game.o
ui_files := ui/web/WebUI.o
utils := utils/utils.o
main := main.o

BUILD_DIR = bin

chex_files := $(board_files) $(game_files) $(utils) $(main) $(ui_files) 
tests := $(wildcard ./tests/*) $(board_files)

ifeq ($(OS),Windows_NT)

chex: $(chex_files)
	IF NOT EXIST ./$(BUILD_DIR) MKDIR $(BUILD_DIR)
	$(CMD) -lws2_32 $(chex_files) -o .\$(BUILD_DIR)\chex.exe

clean:
	IF EXIST $(BUILD_DIR) RMDIR /S /Q $(BUILD_DIR)
	IF EXIST *.o DEL /S /Q *.o
else

chex: $(chex_files)
	mkdir -p $(BUILD_DIR)
	$(CMD) $(chex_files) -o ./$(BUILD_DIR)/chex

clean:
	rm -rf $(chex_files)
	rm -rf ./tests/*.o
endif


chex/tests:
	$(CMD) $(tests) -o ./$(BUILD_DIR)/chex.test

$(main): main.cpp
	$(CMD) -c $(CFLAGS) $< -o $@

$(utils): utils/utils.cpp utils/utils.hpp
	$(CMD) -c $(CFLAGS) $< -o $@

$(board_files): board/board.cpp board/board.hpp
	$(CMD) -c $(CFLAGS) $< -o $@

$(game_files): game/game.cpp game/game.hpp
	$(CMD) -c $(CFLAGS) $< -o $@

$(ui_files): ui/web/WebUI.cpp ui/web/WebUI.hpp ui/web/index.h
	$(CMD) -c $(CFLAGS) $< -o $@

format:
	clang-format -i ./**/*.cpp
	clang-format -i ./**/*.hpp

all: chex

.PHONY: format all clean clean_win32

