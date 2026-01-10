#ifndef STILOU_H_
#define STILOU_H_

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t *pixels;
    size_t width;
    size_t height;
} Stilou_Canvas;

Stilou_Canvas stilou_create_canvas(uint32_t *pixels, size_t width, size_t height);
void stilou_fill_canvas(Stilou_Canvas canvas, uint32_t color);
void stilou_draw_pixel(Stilou_Canvas canvas, int x, int y, uint32_t color);
void stilou_fill_rect(Stilou_Canvas canvas, int x, int y, size_t w, size_t h, uint32_t color);
void stilou_fill_circle(Stilou_Canvas canvas, int x, int y, size_t r, uint32_t color);

#endif // STILOU_H_

#ifdef STILOU_IMPLEMENTATION

Stilou_Canvas stilou_create_canvas(uint32_t *pixels, size_t width, size_t height) {
    return (Stilou_Canvas) {
        .pixels = pixels,
        .width = width,
        .height = height,
    };
}

void stilou_fill_canvas(Stilou_Canvas canvas, uint32_t color) {
    for (size_t i = 0; i < canvas.width*canvas.height; ++i) {
        canvas.pixels[i] = color;
    }
}

void stilou_draw_pixel(Stilou_Canvas canvas, int x, int y, uint32_t color) {
    if (x >= 0 && y >= 0 && x < (int)canvas.width && y < (int)canvas.height) {
        canvas.pixels[y*canvas.width + x] = color;
    }
}

void stilou_fill_rect(Stilou_Canvas canvas, int x, int y, size_t w, size_t h, uint32_t color) {
    for (int r = y; r < y + (int)h; ++r) {
        for (int c = x; c < x + (int)w; ++c) {
            stilou_draw_pixel(canvas, c, r, color);
        }
    }
}

void stilou_fill_circle(Stilou_Canvas canvas, int x, int y, size_t radius, uint32_t color) {
    for (int r = y - (int)radius; r < y + (int)radius; ++r) {
        for (int c = x - (int)radius; c < x + (int)radius; ++c) {
            int dx = c - x;
            int dy = r - y;
            if (dx*dx + dy*dy < (int)(radius*radius)) {
                stilou_draw_pixel(canvas, c, r, color);
            }
        }
    }
}

#endif // STILOU_IMPLEMENTATION
