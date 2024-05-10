CC = clang
CFLAGS = -I/opt/homebrew/include -I./include
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
SRC = $(wildcard src/*.c src/screens/*.c)
OBJ = $(patsubst src/%,build/%,$(SRC:.c=.o))
TARGET = build/game

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf build
