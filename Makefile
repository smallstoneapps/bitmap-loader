# Bitmap Loader v2.2
# http://smallstoneapps.github.io/bitmap-loader/
#
# ----------------------
#
# The MIT License (MIT)
#
# Copyright © 2014 Matthew Tole
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# --------------------
#
# Makefile

PEBBLE_HEADERS=tests/include
LIB_HEADERS=src/libs/linked-list/src

CC=gcc
ifeq ($(TRAVIS), true)
CFLAGS=-std=c99
else
CFLAGS=-std=c11
endif
CINCLUDES=-I $(PEBBLE_HEADERS) -I tests/ -I $(LIB_HEADERS)

TEST_FILES=tests/bitmap-loader.c
SRC_FILES=src/bitmap-loader.c
TEST_EXTRAS=tests/src/pebble.c
LIB_FILES=src/libs/linked-list/src/linked-list.c

all: test

test:
	@$(CC) $(CFLAGS) $(CINCLUDES) $(TEST_FILES) $(SRC_FILES) $(LIB_FILES) $(TEST_EXTRAS) -o tests/run
	@tests/run || (echo 'Bitmap Loader tests failed' | terminal-notifier; exit 1)
	@rm tests/run
	@printf "\x1B[0m"