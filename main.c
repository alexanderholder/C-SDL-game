#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void show_start_screen(SDL_Renderer *renderer, SDL_Window *window) {
  // Get the window size
  int window_width, window_height;
  SDL_GetWindowSize(window, &window_width, &window_height);

  // Initialize the TTF library
  if (TTF_Init() < 0) {
      printf("TTF_Init Error: %s\n", TTF_GetError());
      return;
  }

  // Load a font
  // Adjust the font size based on the window size
  int font_size = window_height / 20; // adjust as needed
  TTF_Font *font = TTF_OpenFont("./assets/OpenSans_Condensed-Regular.ttf", font_size);
  if (font == NULL) {
      printf("TTF_OpenFont Error: %s\n", TTF_GetError());
      TTF_Quit();
      return;
  }

  // Create a surface with the text
  SDL_Color color = {0, 0, 0, 255}; // red
  SDL_Surface *surface = TTF_RenderText_Solid(font, "Press any key to start", color);
  if (surface == NULL) {
      printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
      TTF_CloseFont(font);
      TTF_Quit();
      return;
  }

  // Create a texture from the surface and render it
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect rect;
  rect.w = window_width / 2; // half of the window width
  rect.h = window_height / 2; // half of the window height
  rect.x = window_width / 4; // centered horizontally
  rect.y = window_height / 4; // centered vertically

  SDL_RenderCopy(renderer, texture, NULL, &rect);

  // Clean up
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  TTF_CloseFont(font);

  // Present the rendered start screen to the user
  SDL_RenderPresent(renderer);

  // Wait for the user to press a key
  SDL_Event event;
  while (1) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        TTF_Quit();
        return;
      }
    }
  }
}

int main (int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  SDL_Delay(10000);

  show_start_screen(renderer, window);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
