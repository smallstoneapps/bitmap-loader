#include "unit.h"
#include "./src/pebble-extra.h"
#include "bitmap-loader.h"

#define VERSION_LABEL "1.1.1"

// Colour code definitions to make the output all pretty.
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

// Keep track of how many tests have run, and how many have passed.
int tests_run = 0;
int tests_passed = 0;

static void before_each(void) {
  srand(time(NULL));
  bitmaps_init();
}

static void after_each(void) {
  bitmaps_cleanup();
}

// Test that bitmaps load correctly.
static char* test_bitmap_load_basic(void) {
  uint16_t id1 = 5;
  uint16_t id2 = 200;
  uint16_t id3 = 93;
  GBitmap* bitmap1 = bitmaps_get_bitmap(id1);
  GBitmap* bitmap2 = bitmaps_get_bitmap(id2);
  GBitmap* bitmap3 = bitmaps_get_bitmap(id3);
  mu_assert(bitmap1->reserved == id1, "Bitmap 1 was not loaded correctly.");
  mu_assert(bitmap2->reserved == id2, "Bitmap 2 was not loaded correctly.");
  mu_assert(bitmap3->reserved == id3, "Bitmap 3 was not loaded correctly.");
  return 0;
}

// Test that bitmaps don't load more than once.
static char* test_bitmap_load_once(void) {
  uint16_t id1 = 876;
  uint16_t id2 = 409;
  GBitmap* bitmap1 = bitmaps_get_bitmap(id1);
  GBitmap* bitmap2 = bitmaps_get_bitmap(id1);
  GBitmap* bitmap3 = bitmaps_get_bitmap(id2);
  mu_assert(bitmap1->reserved == id1, "Bitmap 1 did not have correct ID.");
  mu_assert(bitmap2->reserved == id1, "Bitmap 2 did not have correct ID.");
  mu_assert(bitmap3->reserved == id2, "Bitmap 3 did not have correct ID.");
  mu_assert(bitmap1->addr == bitmap2->addr, "Bitmap pointer did not match.");
  mu_assert(bitmap1->addr != bitmap3->addr, "Bitmap pointer matched when they should not.");
  return 0;
}

static char* test_bitmap_group_same(void) {
  uint16_t id1 = 531;
  uint16_t id2 = 107;
  uint8_t group1 = 1;
  GBitmap* bitmap1 = bitmaps_get_bitmap_in_group(id1, group1);
  GBitmap* bitmap2 = bitmaps_get_bitmap_in_group(id2, group1);
  mu_assert(bitmap1->reserved != id1, "Bitmap was not unloaded.");
  return 0;
}

static char* test_bitmap_group_different(void) {
  uint16_t id1 = 812;
  uint16_t id2 = 44;
  uint8_t group1 = 1;
  uint8_t group2 = 2;
  GBitmap* bitmap1 = bitmaps_get_bitmap_in_group(id1, group1);
  GBitmap* bitmap2 = bitmaps_get_bitmap_in_group(id2, group2);
  mu_assert(bitmap1->reserved == id1, "Bitmap 1 was unloaded.");
  mu_assert(bitmap2->reserved == id2, "Bitmap 2 was unloaded.");
  return 0;
}

static char* test_sub_bitmap(void) {
  uint16_t id = 812;
  GRect rect = GRect(0, 0, 16, 16);
  GBitmap* bitmap = bitmaps_get_sub_bitmap(id, rect);
  mu_assert(((GBitmap*)bitmap->addr)->reserved == id, "Bitmap was not created from the requested resource");
  mu_assert(grect_equal(&bitmap->bounds, &rect), "Bitmap has the wrong size and origin.");
  return 0;
}

static char* test_sub_bitmap_multiple_subs(void) {
  uint16_t id = 812;
  GRect rect1 = GRect(0, 0, 16, 16);
  GRect rect2 = GRect(0, 0, 16, 32);
  GBitmap* bitmap1 = bitmaps_get_sub_bitmap(id, rect1);
  GBitmap* bitmap2 = bitmaps_get_sub_bitmap(id, rect2);
  mu_assert(((GBitmap*)bitmap1->addr)->reserved == id, "Bitmap 1 was not created from the requested resource");
  mu_assert(((GBitmap*)bitmap2->addr)->reserved == id, "Bitmap 2 was not created from the requested resource");
  mu_assert(bitmap2->addr == bitmap1->addr, "Bitmap 1 and 2 were not created from the same bitmap");
  mu_assert(grect_equal(&bitmap1->bounds, &rect1), "Bitmap 1 has the wrong size and origin.");
  mu_assert(grect_equal(&bitmap2->bounds, &rect2), "Bitmap 1 has the wrong size and origin.");
  return 0;
}

static char* all_tests() {
  mu_run_test(test_bitmap_load_basic);
  mu_run_test(test_bitmap_load_once);
  mu_run_test(test_bitmap_group_same);
  mu_run_test(test_bitmap_group_different);
  mu_run_test(test_sub_bitmap);
  mu_run_test(test_sub_bitmap_multiple_subs);
  return 0;
}

// Test application entry point.
// Executes all the tests and prints the results in pretty colours.
int main(int argc, char **argv) {
  printf("%s-----------------------------------\n", KCYN);
  printf("| Running Bitmap Loader %s Tests |\n", VERSION_LABEL);
  printf("-----------------------------------\n%s", KNRM);
  char* result = all_tests();
  if (0 != result) {
    printf("%s- Failed Test:%s %s\n", KRED, KNRM, result);
  }
  printf("- Tests Run: %s%d%s\n", (tests_run == tests_passed) ? KGRN : KRED, tests_run, KNRM);
  printf("- Tests Passed: %s%d%s\n", (tests_run == tests_passed) ? KGRN : KRED, tests_passed, KNRM);

  printf("%s-----------------------------------%s\n", KCYN, KNRM);
  return result != 0;
}
