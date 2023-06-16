CFLAGS = -Wall -Wextra -std=c++17 
CC = g++
CMD := $(CC) $(CFLAGS)

engine_files := ./engine/board/board.o ./utils/utils.o
chex_files := ./engine/main.o $(engine_files)
engine_src := ./engine/board/board.cpp

chex: $(engine_files)
	mkdir -p bin
	$(CMD) $(chex_files) -o ./bin/chex

engine/tests:
	mkdir -p bin
	$(CMD) ./tests/board.cpp $(engine_src) -o ./bin/engine.test

engine/board: ./engine/board/board.cpp ./src/board/board.hpp
	$(CMD) ./engine/board/board.cpp

engine/utils: ./utils/utils.cpp ./engine/utils.hpp
	$(CMD) ./engine/utils.cpp

format:
	clang-format -i ./**/*.cpp
	clang-format -i ./**/*.hpp

all: clean chex

clean_win32:
	DEL /Q /F /S .\src\*.o
	DEL /Q /F /S .\utils\*.o
	RD /S /Q .\bin

engine_win32: $(engine_files)
	if not exist "bin" then mkdir bin
	$(CMD) $(engine_files) -o ./bin/engine.exe

all_win32: clean_win32 engine_win32 

clean: 
	rm -rf $(engine_files)
	rm -rf ./tests/**/*.o
	rm -rf ./utils/*.o
	rm -rf ./bin
