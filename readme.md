# SDL Game

## Deps

You'll need to run:

- brew install SDL2
- brew install SDL2_image
- brew install SDL2_ttf

## Running the game

Compile with `clang game.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -o build/game`
Then run the game with `./build/game`
