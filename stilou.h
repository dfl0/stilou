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
void stilou_fill_triangle(Stilou_Canvas canvas, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);

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

void stilou_fill_triangle(Stilou_Canvas canvas, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color) {
    int x_min = x1 < x2 ? (x1 < x3 ? x1 : x3) : (x2 < x3 ? x2 : x3);
    int y_min = y1 < y2 ? (y1 < y3 ? y1 : y3) : (y2 < y3 ? y2 : y3);
    int x_max = x1 > x2 ? (x1 > x3 ? x1 : x3) : (x2 > x3 ? x2 : x3);
    int y_max = y1 > y2 ? (y1 > y3 ? y1 : y3) : (y2 > y3 ? y2 : y3);

    // edge vectors
    int e1[] = {x2 - x1, y2 - y1};
    int e2[] = {x3 - x2, y3 - y2};
    int e3[] = {x1 - x3, y1 - y3};

    for (int r = y_min; r < y_max; ++r) {
        for (int c = x_min; c < x_max; ++c) {
            // relative position vectors
            int u1[] = {c - x1, r - y1};
            int u2[] = {c - x2, r - y2};
            int u3[] = {c - x3, r - y3};

            // dot with edge normals (half-space test)
            if (u1[0]*(-e1[1]) + u1[1]*e1[0] > 0 &&
                u2[0]*(-e2[1]) + u2[1]*e2[0] > 0 &&
                u3[0]*(-e3[1]) + u3[1]*e3[0] > 0) {
                stilou_draw_pixel(canvas, c, r, color);
            }
        }
    }
}

#endif // STILOU_IMPLEMENTATION
