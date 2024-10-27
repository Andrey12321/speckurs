CC = gcc
CFLAGS = -Wall -Wextra -fPIC
LDFLAGS = -shared

all: move protect.so

move: move.c
	$(CC) -o move move.c

protect.so: protect.c
	$(CC) $(LDFLAGS) -o protect.so protect.c

clean:
	rm -f move protect.so
