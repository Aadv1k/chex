CFLAGS = -Wall -Wextra
CC = g++
CMD := $(CC) $(CFLAGS)

chex_files := ./src/main.o ./src/board.o ./utils/utils.o

chex: $(chex_files)
	mkdir -p bin
	$(CMD) $(chex_files) -o ./bin/chex

chex/board: ./src/board.cpp ./src/board.hpp
	$(CMD) ./src/board.cpp

chex/utils: ./utils/utils.cpp ./src/utils.hpp
	$(CMD) ./src/utils.cpp

format:
	clang-format -i ./src/*

all: clean format chex

clean: 
	rm -rf ./src/*.o
	rm -rf ./utils/*.o
	rm -rf ./bin
