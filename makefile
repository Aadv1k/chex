CFLAGS = -Wall -Wextra -std=c++17 
CC = g++
CMD := $(CC) $(CFLAGS)

chex_files := ./src/main.o ./src/board/board.o ./utils/utils.o

chex: $(chex_files)
	mkdir -p bin
	$(CMD) $(chex_files) -o ./bin/chex

chex/board: ./src/board/board.cpp ./src/board/board.hpp
	$(CMD) ./src/board.cpp

chex/utils: ./utils/utils.cpp ./src/utils.hpp
	$(CMD) ./src/utils.cpp

format:
	clang-format -i ./src/*

all: clean chex

clean_win32:
	DEL /Q /F /S .\src\*.o
	DEL /Q /F /S .\utils\*.o
	RD /S /Q .\bin

chex_win32: $(chex_files)
	if not exist "bin" then mkdir bin
	$(CMD) $(chex_files) -o ./bin/chex.exe

all_win32: clean_win32 chex_win32 

clean: 
	rm -rf ./src/*/**.o
	rm -rf ./utils/*.o
	rm -rf ./bin
