CFLAGS = -Wall -Wextra -std=c++17 
CC = g++
CMD := $(CC) $(CFLAGS)

board_files := ./board/board.o
game_files := ./game/game.o
ui_files := ./ui/web/WebUI.o
utils := ./utils/utils.o
main := ./main.o

chex_files := $(board_files) $(game_files) $(utils) $(main) $(ui_files)

chex: $(chex_files)
	mkdir -p bin
	$(CMD) $(chex_files) -o ./bin/chex

chex/main: main.cpp
	$(CMD) -c ./main.cpp

utils: ./utils/utils.cpp ./engine/utils.hpp
	$(CMD) ./engine/utils.cpp

chex/board: ./board/board.cpp ./board/board.hpp
	$(CMD) -c ./board/board.cpp 

chex/game: ./game/game.cpp ./game/game.hpp
	$(CMD) -c ./game/game.cpp  -o ./game/game.o

chex/ui/web: ./ui/web/WebUI.hpp ./ui/web/WebUI.cpp
	$(CMD) -c ./ui/web/WebUI.cpp -o ./ui/web/WebUI.o

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
	rm -rf $(chex_files)
	rm -rf ./tests/**/*.o
	rm -rf ./utils/*.o
	rm -rf ./bin
