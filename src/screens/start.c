#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void show_start_screen(SDL_Renderer *renderer, SDL_Window *window)
{
  int window_width, window_height;
  SDL_GetWindowSize(window, &window_width, &window_height);

  // Initialize the TTF library
  if (TTF_Init() < 0)
  {
    printf("TTF_Init Error: %s\n", TTF_GetError());
    return;
  }

  int font_size = window_height / 20;
  TTF_Font *font = TTF_OpenFont("../assets/OpenSans_Condensed-Regular.ttf", font_size);
  if (font == NULL)
  {
    printf("TTF_OpenFont Error: %s\n", TTF_GetError());
    TTF_Quit();
    return;
  }

  SDL_Color color = {255, 255, 255, 255}; // white
  SDL_Surface *surface = TTF_RenderText_Blended(font, "Press any key to start", color);
  if (surface == NULL)
  {
    printf("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
    TTF_CloseFont(font);
    TTF_Quit();
    return;
  }

  // Create a texture from the surface and render it
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect rect;
  rect.w = window_width / 2;
  rect.h = window_height / 2;
  rect.x = window_width / 4;
  rect.y = window_height / 4;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black

  SDL_Rect bgRect = rect;
  SDL_RenderFillRect(renderer, &bgRect);

  SDL_RenderCopy(renderer, texture, NULL, &rect);

  // Clean up
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  TTF_CloseFont(font);

  // Present the rendered start screen to the user
  SDL_RenderPresent(renderer);

  // Wait for the user to press a key
  SDL_Event event;
  while (1)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_KEYDOWN)
      {
        TTF_Quit();
        return;
      }
    }
  }
}
