#include "tinyexpr.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR 0x0000FF
#define GRID_COLOR 0xCCCCCC
#define X_START -10
#define X_END 10
#define Y_START -5
#define Y_END 5
#define STEP 0.05

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
  x_axis.h = 1;
  draw_at_grid_coordinates(psurface, &x_axis, GRID_COLOR);

  SDL_Rect y_axis;
  y_axis.x = 0;
  y_axis.y = HEIGHT / 2;
  y_axis.w = 1;
  y_axis.h = HEIGHT;
  draw_at_grid_coordinates(psurface, &y_axis, GRID_COLOR);
}

void draw_expr(SDL_Surface *psurface, char *expr) {

  double x;

  te_variable vars[] = {{"x", &x}};

  int err;
  te_expr *pexpr;

  if (pexpr) {

    for (x = X_START; x <= X_END; x += STEP) {
      pexpr = te_compile(expr, vars, 1, &err);
      double res = te_eval(pexpr);
      printf("The result of the expression is: %f \n", res);
      SDL_Rect line = (SDL_Rect){
          (float)(x * ((float)WIDTH / (X_END - X_START) / 2.0)),
          (float)(res * ((float)HEIGHT / (Y_END - Y_START) / 2.0)), 1, 1};
      draw_at_grid_coordinates(psurface, &line, COLOR);
    }

  } else {
    fprintf(stderr, "Error compiling expression at position: %d\n", err);
    exit(-1);
  }
}

int main(int argc, char *argv[]) {
  printf("Welcome to the function plotter!\n");

  if (argc != 2) {
    printf("Usage: %s <function>\n", argv[0]);
    return 0;
  }

  char *expr = argv[1];

  SDL_Window *pwindow =
      SDL_CreateWindow("Function Plotter", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  draw_grid(psurface);
  draw_expr(psurface, expr);

  SDL_Event event;
  bool app_running = true;
  SDL_UpdateWindowSurface(pwindow);

  while (app_running) {

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        app_running = false;
      }
    }
  }
}
