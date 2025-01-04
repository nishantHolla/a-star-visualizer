CC=gcc
CFLAGS=-Wall -Wextra -pedantic
INCLUDE=-Isrc/include -Isrc/include/raylib
LIBRARY=-Lsrc/lib
LIB=-lm -ldl -lpthread -lGL -lrt -lX11
SRC=src/*.c
OUT=out/asv
UNAME_S=$(shell uname)

ifeq ($(UNAME_S),Linux)
	OS_LIB=-lraylib-linux
else ifeq ($(UNAME_S),Darwin)
	OS_LIB=-lraylibmac
endif

pre:
	mkdir -p out
	cd out && ln -sf ../src/assets .

debug: pre
	$(CC) $(CFLAGS) -ggdb $(INCLUDE) $(LIBRARY) -o $(OUT) $(SRC) $(LIB) $(OS_LIB)

runDebug: pre
	$(CC) $(CFLAGS) -ggdb $(INCLUDE) $(LIBRARY) -o $(OUT) $(SRC) $(LIB) $(OS_LIB) && cd out && ./asv

release: pre
	$(CC) $(CFLAGS) -O3 $(INCLUDE) $(LIBRARY) -o $(OUT) $(SRC) $(LIB) $(OS_LIB)
