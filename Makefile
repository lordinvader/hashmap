CC = gcc
INCLUDE = include/
CFLAGS = -g -O2 -Wall -Werror -pedantic -I $(INCLUDE)

all: Makefile dirs test

test: bin/test-hashmap
	./bin/test-hashmap

bin/test-hashmap: build/test-hashmap.o build/hashmap.o build/hashfun.o build/compare.o
	$(CC) $(CFLAGS) $+ -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: test/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -vfr bin build

dirs:
	mkdir -p build bin
