#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#define STILOU_IMPLEMENTATION
#include "stilou.h"

#define WIDTH  800
#define HEIGHT 600

uint32_t pixels[HEIGHT*WIDTH] = {0};

void render_canvas(Stilou_Canvas canvas) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        exit(1);
    }

    for (size_t y = 0; y < canvas.height; ++y) {
        for (size_t x = 0; x < canvas.width; ++x) {
            uint32_t color = canvas.pixels[y*canvas.width + x];
            SDL_SetRenderDrawColor(renderer,
                                   (color & 0xFF000000) >> (8*3),  // R
                                   (color & 0x00FF0000) >> (8*2),  // G
                                   (color & 0x0000FF00) >> (8*1),  // B
                                   (color & 0x000000FF) >> (8*0)); // A
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    SDL_RenderPresent(renderer);

    int quit = 0;
    SDL_Event event;
    while (!quit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {
    Stilou_Canvas canvas = stilou_create_canvas(pixels, WIDTH, HEIGHT);
    stilou_fill_canvas(canvas, 0xFF00FFFF);
    render_canvas(canvas);
    return 0;
}
