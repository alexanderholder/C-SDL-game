# C SDL Game

Just a bit of fun making a retro game using C with SDL

## Deps

You'll need to install the following:

- brew install SDL2
- brew install SDL2_image
- brew install SDL2_ttf

## Running the game

Compile with `clang main.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -o build/game`
Then run the game with `./build/game`
