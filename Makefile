CC=gcc
CFLAGS=-Wall -Wextra -pedantic
INCLUDE=-Isrc/include
LIBRARY=-Lsrc/lib
LIB=-lraylib -lm -ldl -lpthread -lGL -lrt -lX11
SRC=src/*.c
OUT=out/asv


debug:
	$(CC) $(CFLAGS) -ggdb $(INCLUDE) $(LIBRARY) -o $(OUT) $(SRC) $(LIB)

runDebug:
	$(CC) $(CFLAGS) -ggdb $(INCLUDE) $(LIBRARY) -o $(OUT) $(SRC) $(LIB) && cd out && ./asv

release:
	$(CC) $(CFLAGS) -O3 $(INCLUDE) $(LIBRARY) -o $(OUT) $(SRC) $(LIB)
