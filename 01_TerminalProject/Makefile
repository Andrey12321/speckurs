CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = Show

$(TARGET): Show.o
	$(CC) $(CFLAGS) -o $(TARGET) Show.o -lncurses

Show.o: Show.c
	$(CC) $(CFLAGS) -c Show.c

clean:
	rm -f *.o $(TARGET)

.PHONY: clean
