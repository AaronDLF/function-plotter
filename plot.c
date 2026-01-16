#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR 0xFF0000

void draw_at_grid_coordinates(SDL_Surface *psurface, SDL_Rect *prect,
                              Uint32 color) {

  int x_grid = WIDTH / 2 + prect->x;
  int y_grid = HEIGHT / 2 - prect->y;
  SDL_Rect *shifted_rect = &(SDL_Rect){x_grid, y_grid, prect->w, prect->h};
  SDL_FillRect(psurface, shifted_rect, color);
}

void draw_grid(SDL_Surface *psurface) {
  SDL_Rect x_axis;
  x_axis.x = -WIDTH / 2;
  x_axis.y = 0;
  x_axis.w = WIDTH;
  x_axis.h = 2;
  draw_at_grid_coordinates(psurface, &x_axis, COLOR);
}

int main() {
  printf("Welcome to the function plotter!\n");
  SDL_Window *pwindow =
      SDL_CreateWindow("Function Plotter", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  SDL_Rect rect = (SDL_Rect){50, 50, 50, 50};

  draw_at_grid_coordinates(psurface, &rect, COLOR);
  draw_grid(psurface);

  SDL_Event event;
  bool app_running = true;

  while (app_running) {

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = false;
      }
    }
    SDL_UpdateWindowSurface(pwindow);
  }
}
