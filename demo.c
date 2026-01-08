#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <SDL2/SDL.h>

#define STILOU_IMPLEMENTATION
#include "stilou.h"

#define WIDTH  800
#define HEIGHT 600

uint32_t pixels[HEIGHT*WIDTH] = {0};

void init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        exit(1);
    }
}

SDL_Window *init_window() {
    SDL_Window *window = SDL_CreateWindow("stilou", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        exit(1);
    }

    return window;
}

SDL_Renderer *init_renderer(SDL_Window *window) {
    return SDL_CreateRenderer(window, -1, 0);
}

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void render_canvas(Stilou_Canvas canvas) {
    static SDL_Texture *texture = NULL;

    if (!texture) {
        texture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    canvas.width, canvas.height);
    }

    SDL_UpdateTexture(texture, NULL, canvas.pixels, canvas.width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

int should_quit() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 1;
        }
    }
    return 0;
}

void quit_sdl() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {
    // initialize SDL, as well as the window and renderer
    init_sdl();
    window = init_window();  // TODO: maybe use canvas as input
    renderer = init_renderer(window);

    // create a stilou canvas
    Stilou_Canvas canvas = stilou_create_canvas(pixels, WIDTH, HEIGHT);

    int target_fps = 60;
    int nanos_per_frame = 1000*1000*1000/target_fps;

    struct timespec t;

    size_t rect_w = 150;
    size_t rect_h = 100;
    int x = canvas.width/2 - rect_w/2;
    int y = canvas.height/2 - rect_h/2;

    int x_speed = 5;
    int y_speed = 5;

    while (!should_quit()) {
        clock_t frame_start = clock();

        x += x_speed;
        y += y_speed;
        if ((size_t)x + rect_w > canvas.width || x < 0) x_speed *= -1;
        if ((size_t)y + rect_h > canvas.height || y < 0) y_speed *= -1;

        // start drawing
        stilou_fill_canvas(canvas, 0x202020FF); // (clear screen)
        stilou_fill_circle(canvas, 300, 200, 100, 0x2020F0FF);
        stilou_fill_rect(canvas, x, y, rect_w, rect_h, 0xF02020FF);

        // show the drawing
        render_canvas(canvas);

        // maintain a consistent framerate
        int nanos_taken = (clock() - frame_start)*1000*1000*1000/CLOCKS_PER_SEC;
        if (nanos_taken < nanos_per_frame) {
            t.tv_sec = 0;
            t.tv_nsec = nanos_per_frame - nanos_taken;
            if (nanosleep(&t, NULL) < 0) exit(1);
        }
    }

    quit_sdl();
    return 0;
}
