#pragma once


#include <pebble.h>


/**
 * Initialise the bitmap loading library.
 */
void bitmaps_init(void);

/**
 * Returns a pointer to the bitmap as specified by a resource ID.
 * If the bitmap has not been requested before, it will be loaded.
 */
GBitmap* bitmaps_get_bitmap(uint32_t res_id);

/**
 * Returns a pointer to the bitmap as specified by a resource ID.
 * If the bitmap has not been requested before, it will be loaded.
 * If another bitmap has been loaded with the same group number, it will be
 * unloaded.
 */
GBitmap* bitmaps_get_bitmap_in_group(uint32_t res_id, uint8_t group);

/**
 * Returns a pointer to a bitmap that is a subset of a larger bitmap.
 * You provide the resource and the rectangle, and it gives you back the
 * sub-bitmap.
 */
GBitmap* bitmaps_get_sub_bitmap(uint32_t res_id, GRect rect);

/**
 * Unload all the bitmaps from memory.
 */
void bitmaps_cleanup(void);
