.PHONY: clean print run count gdb asm elf

### cppfile = display.cpp enemy.cpp item.cpp main.cpp move.cpp msg.cpp res.cpp

CC = g++

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
DAT_DIR = data

cppfile = $(shell find $(SRC_DIR) -name "*.cpp")
sdlpre  = $(shell find /usr/include -name SDL.h)
sdltar = /usr/include/SDL/SDL.h

GITFLAGS = -q --author='ouxianfei <nickouxianfei@gmail.com>' --no-verify --allow-empty

info = This projects need SDL lib, \
	 if your OS haven\'t install it, \
	 to install it by apt-get install libsdl1.2-dev in debian, \
	 or https://www.libsdl.org/ in windows.

CFLAGS = -O2 -Wall -Werror -lSDL -Iinclude -I.
### CFLAGS = -Wall -Werror -lSDL -Iinclude -I.

game_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(cppfile))

game: $(game_OBJ)
ifneq ($(sdlpre), $(sdltar))
	@echo "\033[1;31m$(info)\033[0m\n"
else
	@mkdir -p obj
	@$(CC) -o obj/$@ $(game_OBJ) $(CFLAGS)
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo + $<
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(CFLAGS)

# extra rules here

print:
	@echo "\033[1;31m$(info)\033[0m\n"
	@echo cppfile : $(cppfile)
	@echo game_OBJ : $(game_OBJ)

clean:
	@clear
	@rm -rf obj asm elf bin perf.data

run: game
	$(call git_cmd, "run the game")
	@$(OBJ_DIR)/game

count:
	@printf "total lines:" && (find . -name *.cpp -or -name *.h | xargs cat | wc -l) && echo

gdb: game
	@gdb $(OBJ_DIR)/game

asm: game
	@mkdir -p asm
	@objdump -S $(OBJ_DIR)/game > asm/game.S
	@vim asm/game.S

elf: game
	@mkdir -p elf
	@readelf -a $(OBJ_DIR)/game > elf/game.elf
	@vim elf/game.elf
