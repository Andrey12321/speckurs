#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BUFFER_SIZE 1000
#define MAX_MATCHES 10

void print_regex_error(int errcode, const regex_t *regex) {
    char err_message[100];
    regerror(errcode, regex, err_message, sizeof(err_message));
    fprintf(stderr, "Regex error: %s\n", err_message);
}

int perform_substitution(const char *pattern, const char *replacement, const char *input) {
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    char buffer[BUFFER_SIZE];
    
    int compile_status = regcomp(&regex, pattern, REG_EXTENDED);
    if (compile_status != 0) {
        print_regex_error(compile_status, &regex);
        return 1;
    }

    const char *input_ptr = input;
    char *buffer_ptr = buffer;
    
    if (regexec(&regex, input_ptr, MAX_MATCHES, matches, 0) == 0) {
        size_t prefix_len = matches[0].rm_so;
        strncpy(buffer_ptr, input_ptr, prefix_len);
        buffer_ptr += prefix_len;

        const char *replacement_ptr = replacement;
        while (*replacement_ptr && buffer_ptr - buffer < sizeof(buffer) - 1) {
            if (*replacement_ptr == '\\' && *(replacement_ptr + 1) >= '0' && *(replacement_ptr + 1) <= '9') {
                int ref_num = *(replacement_ptr + 1) - '0';
                replacement_ptr += 2;
                if (matches[ref_num].rm_so == -1) {
                    fprintf(stderr, "Error: Invalid reference \\%d\n", ref_num);
                    regfree(&regex);
                    return 1;
                }
                size_t match_len = matches[ref_num].rm_eo - matches[ref_num].rm_so;
                strncpy(buffer_ptr, input_ptr + matches[ref_num].rm_so, match_len);
                buffer_ptr += match_len;
            } else if (*replacement_ptr == '\\' && *(replacement_ptr + 1) == '\\') {
                *buffer_ptr++ = '\\';
                replacement_ptr += 2;
            } else {
                *buffer_ptr++ = *replacement_ptr++;
            }
        }

        const char* suffix_start = input_ptr + matches[0].rm_eo;
        size_t suffix_len = strlen(suffix_start);
        strncpy(buffer_ptr, suffix_start, suffix_len);
        buffer_ptr += suffix_len;

        *buffer_ptr = '\0';
    } else {
        strncpy(buffer, input, BUFFER_SIZE - 1);
        buffer[BUFFER_SIZE - 1] = '\0';
    }

    printf("%s\n", buffer);
    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <pattern> <replacement> <input>\n", argv[0]);
        return 1;
    }
    return perform_substitution(argv[1], argv[2], argv[3]);
}
