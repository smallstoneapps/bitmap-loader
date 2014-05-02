/***
 * Bitmap Loader v2.0.3
 * On-demand loading of bitmaps from resources.
 *
 * bitmap-loader.c
 ***/

#pragma once

#include <pebble.h>

void bitmaps_init(void);
GBitmap* bitmaps_get_bitmap(uint32_t res_id);
void bitmaps_cleanup(void);
