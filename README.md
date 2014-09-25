# Bitmap Loader [![Build Status](http://img.shields.io/travis/smallstoneapps/bitmap-loader.svg?style=flat-square)](https://travis-ci.org/smallstoneapps/bitmap-loader/)&nbsp;![Version 2.1](http://img.shields.io/badge/version-2.1-orange.svg?style=flat-square)&nbsp;[![MIT License](http://img.shields.io/badge/license-MIT-lightgray.svg?style=flat-square)](./LICENSE)&nbsp;[![Support my development](http://img.shields.io/gittip/matthewtole.svg?style=flat-square)](https://www.gittip.com/matthewtole/)


Pebble library to do lazy loading of bitmaps from resources

## What does it do?

Bitmap Loader will automatically load bitmaps when they are needed, rather than
having to handle the loading of them yourself.

The function `bitmaps_get_bitmap` takes a *RESOURCE_ID* as an argument, and
returns a pointer to a *GBitmap*. If this is the first time that the bitmap has
been requested, it will load the image from resources.

## Usage

```c
// This is not a complete example, but should demonstrate the basic usage of
// the Bitmap Loader library.

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

    void bitmaps_init(void);

Get the bitmap using its resource ID.

    GBitmap* bitmaps_get_bitmap(uint32_t res_id);

Cleanup the Bitmap Loader.

**Note** Call this in your *deinit* function.

    void bitmaps_cleanup(void);
