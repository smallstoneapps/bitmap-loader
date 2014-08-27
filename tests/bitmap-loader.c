/*

Bitmap Loader v2.1
On-demand loading of bitmaps from resources.
http://smallstoneapps.github.io/bitmap-loader/

----------------------

The MIT License (MIT)

Copyright © 2014 Matthew Tole

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

--------------------

tests/bitmap-loader.c

*/

#include "unit.h"
#include "./src/pebble-extra.h"
#include "../src/bitmap-loader.h"

#define VERSION_LABEL "2.1"

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
  bitmaps_init();
}

static void after_each(void) {
  bitmaps_cleanup();
}

static char* all_tests() {
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