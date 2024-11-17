#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

void generate_maze(int size, char wall, char path) {
    char maze[MAX_SIZE][MAX_SIZE];
    int i, j;

    // Инициализация лабиринта (все стены)
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            maze[i][j] = wall;
        }
    }

    // Заполнение проходов случайным образом
    srand(time(NULL));
    for (i = 1; i < size - 1; i++) {
        for (j = 1; j < size - 1; j++) {
            if (rand() % 2 == 0) {
                maze[i][j] = path;
            }
        }
    }

    // Печать лабиринта
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);

    generate_maze(size, '#', '.');
    return 0;
}
