#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rhash.h>
#include <ctype.h>

#ifdef HAVE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

void output_hash(unsigned char *digest, size_t size, int hex_format) {
    char buffer[130];
    if (hex_format) {
        rhash_print_bytes(buffer, digest, size, RHPR_HEX);
    } else {
        rhash_print_bytes(buffer, digest, size, RHPR_BASE64);
    }
    printf("%s\n", buffer);
}

void compute_hash(const char *input, int hash_type, int hex_format) {
    unsigned char digest[64];
    size_t size = rhash_get_digest_size(hash_type);

    rhash_library_init();
    rhash_msg(hash_type, input, strlen(input), digest);

    output_hash(digest, size, hex_format);
}

void compute_file_hash(const char *file, int hash_type, int hex_format) {
    unsigned char digest[64];
    size_t size = rhash_get_digest_size(hash_type);

    rhash_library_init();
    if (rhash_file(hash_type, file, digest) < 0) {
        fprintf(stderr, "Ошибка чтения файла %s\n", file);
        return;
    }

    output_hash(digest, size, hex_format);
}

int main() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
#ifdef HAVE_READLINE
        line = readline("Введите команду: ");
        if (!line) break;
        if (*line) add_history(line);
#else
        if (getline(&line, &len, stdin) == -1) break;
        line[strcspn(line, "\n")] = 0;
#endif

        char *hash_name = strtok(line, " ");
        char *arg = strtok(NULL, " ");

        if (!hash_name || !arg) {
            fprintf(stderr, "Неправильная команда.\n");
            continue;
        }

        int is_file = arg[0] != '"';
        int hex_format = isupper(hash_name[0]);
        int hash_type;

        if (strcasecmp(hash_name, "md5") == 0) {
            hash_type = RHASH_MD5;
        } else if (strcasecmp(hash_name, "sha1") == 0) {
            hash_type = RHASH_SHA1;
        } else if (strcasecmp(hash_name, "tth") == 0) {
            hash_type = RHASH_TTH;
        } else {
            fprintf(stderr, "Неизвестная команда: %s\n", hash_name);
            continue;
        }

        if (is_file) {
            compute_file_hash(arg, hash_type, hex_format);
        } else {
            char *data = arg + 1;  // Убираем "
            compute_hash(data, hash_type, hex_format);
        }
#ifdef HAVE_READLINE
        free(line);
#endif
    }

#ifndef HAVE_READLINE
    free(line);
#endif

    return 0;
}
