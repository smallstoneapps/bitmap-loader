#include <pebble.h>
#include "pebble-bitmap-loader/bitmap-loader.h"

static Window *window;
static BitmapLayer* bitmap_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  bitmap_layer_set_bitmap(bitmap_layer, bitmaps_get_bitmap_in_group(RESOURCE_ID_BITMAP_1, 1));
  APP_LOG(APP_LOG_LEVEL_INFO, "%d", heap_bytes_free());
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  bitmap_layer_set_bitmap(bitmap_layer, bitmaps_get_bitmap_in_group(RESOURCE_ID_BITMAP_2, 1));
  APP_LOG(APP_LOG_LEVEL_INFO, "%d", heap_bytes_free());
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  bitmap_layer_set_bitmap(bitmap_layer, bitmaps_get_bitmap_in_group(RESOURCE_ID_BITMAP_3, 1));
  APP_LOG(APP_LOG_LEVEL_INFO, "%d", heap_bytes_free());
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 152));
  bitmap_layer_set_bitmap(bitmap_layer, bitmaps_get_bitmap_in_group(RESOURCE_ID_BITMAP_1, 1));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bitmap_layer));
  APP_LOG(APP_LOG_LEVEL_INFO, "%d", heap_bytes_free());
}

static void window_unload(Window *window) {
  bitmap_layer_destroy(bitmap_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  bitmaps_init();
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
