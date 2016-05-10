PEBBLE_HEADERS=tests/include
LIB_HEADERS=node_modules/@smallstoneapps/linked-list/dist/include -I node_modules/@smallstoneapps/linked-list/include

CC=gcc
ifeq ($(TRAVIS), true)
CFLAGS=-std=c99
else
CFLAGS=-std=c11
endif
CINCLUDES=-I "$(PEBBLE_HEADERS)" -I tests/ -I $(LIB_HEADERS) -I include/

TEST_FILES=tests/bitmap-loader.c
SRC_FILES=src/c/bitmap-loader.c
TEST_EXTRAS=tests/src/pebble.c
LIB_FILES=node_modules/@smallstoneapps/linked-list/src/c/linked-list.c

all: test

test:
	@$(CC) $(CFLAGS) $(CINCLUDES) $(TEST_FILES) $(SRC_FILES) $(LIB_FILES) $(TEST_EXTRAS) -o tests/run
	@tests/run || (echo 'Bitmap Loader tests failed' | terminal-notifier; exit 1)
	@rm tests/run
	@printf "\x1B[0m"
