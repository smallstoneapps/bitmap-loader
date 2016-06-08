# Bitmap Loader v1.1.1 [![Build Status](http://img.shields.io/travis/smallstoneapps/bitmap-loader.svg?style=flat-square)](https://travis-ci.org/smallstoneapps/bitmap-loader/)&nbsp;[![npm (scoped)](https://img.shields.io/npm/v/@smallstoneapps/bitmap-loader.svg?maxAge=2592000&style=flat-square)](https://www.npmjs.com/package/@smallstoneapps/bitmap-loader)&nbsp;[![MIT License](http://img.shields.io/badge/license-MIT-lightgray.svg?style=flat-square)](./LICENSE)

Pebble library to do lazy loading of bitmaps from resources

## What does it do?

Bitmap Loader will automatically load bitmaps when they are needed, rather than
having to handle the loading of them yourself.

The function `bitmaps_get_bitmap` takes a *RESOURCE_ID* as an argument, and
returns a pointer to a *GBitmap*. If this is the first time that the bitmap has
been requested, it will load the image from resources.

## Installation

*You must be using Pebble SDK 3.12 or newer to use this library.*

To install the package to your app, use the pebble tool:

```
pebble package install @smallstoneapps/bitmap-loader
```

## Usage

```c
// This is not a complete example, but should demonstrate the basic usage of
// the Bitmap Loader library.

#include <@smallstoneapps/bitmap-loader/bitmap-loader.h>

static void init(void) {
  bitmaps_init();
}

static void deiinit(void) {
  bitmaps_cleanup();
}

static void window_load(Window* window) {
  bitmap_layer_set_bitmap(bitmaps_get_bitmap(RESOURCE_ID_BITMAP_1));
  GBitmap* bitmap = (bitmaps_get_bitmap(RESOURCE_ID_BITMAP_2));
}
```

## Function Documentation

Initialise the Bitmap Loader

**Note:** Call this once, preferably in your *init* function.

```c
void bitmaps_init(void);
```

Get the bitmap using its resource ID.

```c
GBitmap* bitmaps_get_bitmap(uint32_t res_id);
```

Get a bitmap from a group. You can use this to make sure you only keep one
bitmap for a single location in memory. If there is already a bitmap loaded
for the given group, it will replace it with the one you are requesting.

```c
GBitmap* bitmaps_get_bitmap_in_group(uint32_t res_id, uint8_t group);
```

Get a sub bitmap from a larger bitmap given its resource ID and a rectangle.
If the parent bitmap has already been loaded it will not be loaded again.

```c
GBitmap* bitmaps_get_sub_bitmap(uint32_t res_id, GRect rect);
```

Cleanup the Bitmap Loader.

**Note** Call this in your *deinit* function.

```c
void bitmaps_cleanup(void);
```
