#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  SDL_Window *window = NULL;
  SDL_Surface *window_surface = NULL;
  SDL_Surface *image_surface = NULL;
  SDL_Surface *optimazed_surface = NULL;

  const char *title = "I'm alive!";
  const char *image_path = "phoenix.png";

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    printf("Error initializing video: %s\n", SDL_GetError());
  } else {
    window =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         800, 800, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Error creating window: %s\n", SDL_GetError());
    } else {
      if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Error initializing image: %s\n", IMG_GetError());
      } else {
        window_surface = SDL_GetWindowSurface(window);
        image_surface = IMG_Load(image_path);

        if (image_surface == NULL) {
          printf("Error loading %s: %s\n", image_path, IMG_GetError());
        }
        // } else {
        //   optimazed_surface =
        //       SDL_ConvertSurface(image_surface, window_surface->format, 0);
        //   if (optimazed_surface == NULL) {
        //     printf("Error converting surface: %s\n", IMG_GetError());
        //   }
        //   SDL_FreeSurface(image_surface);
        // }
      }

      SDL_BlitSurface(image_surface, NULL, window_surface, NULL);
      SDL_UpdateWindowSurface(window);
      SDL_Delay(3000);
    }
  }

  IMG_Quit();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
