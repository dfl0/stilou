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
void stilou_draw_pixel(Stilou_Canvas canvas, size_t x, size_t y, uint32_t color);

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

void stilou_draw_pixel(Stilou_Canvas canvas, size_t x, size_t y, uint32_t color) {
    if (x < canvas.width && y < canvas.height) {
        canvas.pixels[y*canvas.width + x] = color;
    }
}

#endif // STILOU_IMPLEMENTATION
