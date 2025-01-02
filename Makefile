CC=gcc
CFLAGS=-Wall -Wextra -pedantic
INCLUDE=-Isrc/include
LIBRARY=-Lsrc/lib
LIB=-lraylib
SRC=src/*.c
OUT=out/asv

debug:
	$(CC) $(CFLAGS) -ggdb $(INCLUDE) $(LIBRARY) $(LIB) -o $(OUT) $(SRC)

release:
	$(CC) $(CFLAGS) -O3 $(INCLUDE) $(LIBRARY) $(LIB) -o $(OUT) $(SRC)
