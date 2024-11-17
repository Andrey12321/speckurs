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
    if (argc != 5) {
        printf("Usage: %s <seed> <size> <wall_char> <path_char>\n", argv[0]);
        return 1;
    }

    int seed = atoi(argv[1]);
    int size = atoi(argv[2]);
    char wall = argv[3][0];
    char path = argv[4][0];

    // Установка начального значения для генератора случайных чисел
    srand(seed);

    generate_maze(size, wall, path);
    return 0;
}
