# stilou.h

A single-file, dependency-free graphics library for drawing directly to a
pre-allocated pixel buffer in C.

This library provides an easy way to render primitive shapes and (potentially)
images directly into some memory, supporting flexible output such as saving the
pixels to an image file, rendering them in an SDL window, displaying them in the
terminal, etc.

## Usage

To use this library, just add [`stilou.h`](./stilou.h) to your project and
`#include` it.

## Demo

A simple demo is provided in [`demo.c`](./demo.c) --- it initializes a canvas,
fills it with a color, and displays it in a window using SDL.

### Build and Run the Demo

> [!IMPORTANT]
> This demo uses [SDL2](https://www.libsdl.org/) to render the pixels in a
> window, so make sure it is installed on your system.

Build the demo with:

```console
$ make demo
```

Run it with:

```console
$ ./demo
```
