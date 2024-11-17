CC = gcc
CFLAGS = -Wall -std=c99

# Исходники и бинарники
SOURCES = main.c patch1.c patch2.c patch3.c
OBJECTS = $(SOURCES:.c=.o)
BINARY = maze_generator

# Цели
all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINARY)

# Патчи
patch1.o: patch1.c
	$(CC) $(CFLAGS) patch1.c -o patch1.o

patch2.o: patch2.c
	$(CC) $(CFLAGS) patch2.c -o patch2.o

patch3.o: patch3.c
	$(CC) $(CFLAGS) patch3.c -o patch3.o

# Запуск бинарников
run:
	./$(BINARY) 123 . # 6

# Очистка
clean:
	rm -f $(OBJECTS) $(BINARY)

