CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
SANITIZE = -fsanitize=address,undefined

SRC = src/cmap.c
TEST_SRC = tests/main.c

test_main: $(SRC) $(TEST_SRC) include/cmap.h
	$(CC) $(CFLAGS) $(SANITIZE) $(SRC) $(TEST_SRC) -o $@

test: test_main
	./test_main

clean:
	rm -f test_main

.PHONY: test clean