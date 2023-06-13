CFLAGS = -Wall -Wextra
CC = g++
CMD := $(CC) $(CFLAGS)

chex_files := ./src/main.o ./src/board.o

chex/main: $(chex_files)
	$(CMD) $(chex_files) -o ./bin/chex.exe

chex/board: ./src/board.cpp ./src/board.hpp
	$(CMD) ./src/board.cpp

format:
	clang-format -i ./src/*

all: chex/main
