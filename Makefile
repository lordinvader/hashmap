CC = gcc
INCLUDE = include/
CFLAGS = -g -Wall -Werror -pedantic -I $(INCLUDE)

all: Makefile dirs

test: bin/test-hashmap
	./bin/test-hashmap

bin/test-hashmap: build/test-hashmap.o build/hashmap.o build/hashfun.o build/compare.o
	$(CC) $(CFLAGS) $+ -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: test/%.c
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p build bin
