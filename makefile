CFLAGS = -Wall -Wextra
CC = g++
CMD := $(CC) $(CFLAGS)

chex_files := ./src/main.cpp

main: $(chex_files)
	$(CMD) $(chex_files) -o ./bin/chex.exe

all: main

.PHONY: pre-build

pre-build:
	mkdir bin
