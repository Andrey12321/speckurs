#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 70

void show_file(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    show_file(argv[1]);

    endwin();
    return EXIT_SUCCESS;
}

void show_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        endwin();
        fprintf(stderr, "Cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char *lines[MAX_LINES];
    int line_count = 0;

    while (line_count < MAX_LINES) {
        lines[line_count] = (char *)malloc(MAX_LINE_LENGTH + 1);
        if (fgets(lines[line_count], MAX_LINE_LENGTH + 1, file) == NULL) {
            free(lines[line_count]);
            break;
        }
        // Remove newline character if present
        size_t len = strlen(lines[line_count]);
        if (len > 0 && lines[line_count][len - 1] == '\n') {
            lines[line_count][len - 1] = '\0';
        }
        line_count++;
    }
    fclose(file);

    int ch;
    int start_line = 0;
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int lines_per_page = max_y - 1;

    while (1) {
        werase(stdscr);
        mvprintw(0, 0, "File: %s", filename);
        for (int i = 0; i < lines_per_page; i++) {
            int line_index = start_line + i;
            if (line_index >= line_count) {
                break;
            }
            mvprintw(i + 1, 0, "%.*s", MAX_LINE_LENGTH, lines[line_index]);
        }
        refresh();

        ch = getch();
        if (ch == 27) { // ESC key
            break;
        } else if (ch == ' ') {
            start_line++;
            if (start_line >= line_count) {
                start_line = 0;  // Начать показ с начала файла после достижения конца
            }
        }
    }

    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
}
