#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void print_error(const char *msg) {
    perror(msg);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];

    // Проверка существования infile
    if (access(infile, F_OK) == -1) {
        print_error("Error: infile does not exist");
        return EXIT_FAILURE;
    }

    // Открытие infile
    int src_fd = open(infile, O_RDONLY);
    if (src_fd == -1) {
        print_error("Error opening infile");
        return EXIT_FAILURE;
    }

    // Открытие outfile
    int dest_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        print_error("Error opening/creating outfile");
        close(src_fd);
        return EXIT_FAILURE;
    }

    char buffer[4096];
    ssize_t bytes_read;

    // Копирование содержимого infile в outfile
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            print_error("Error writing to outfile");
            close(src_fd);
            close(dest_fd);
            return EXIT_FAILURE;
        }
    }

    if (bytes_read == -1) {
        print_error("Error reading infile");
        close(src_fd);
        close(dest_fd);
        return EXIT_FAILURE;
    }

    // Закрытие файлов
    close(src_fd);
    close(dest_fd);

    // Удаление infile
    if (unlink(infile) == -1) {
        print_error("Error deleting infile");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
