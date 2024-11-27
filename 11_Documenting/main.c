#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include "roman.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "locales"

// Прототипы функций
void guess_number(int roman);
void print_help(const char *progname);

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess_number", LOCALE_PATH);
    textdomain("guess_number");

    int roman = 0;
    if (argc > 1) {
        if (strcmp(argv[1], "-r") == 0) {
            roman = 1;
        } else if (strcmp(argv[1], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else {
            fprintf(stderr, _("Unknown option: %s\n"), argv[1]);
            print_help(argv[0]);
            return 1;
        }
    }

    printf(_("Think of a number between 1 and 100.\n"));
    guess_number(roman);

    return 0;
}

/**
 * Функция угадывания числа
 * @param roman Если 1, то программа работает в римской системе счисления
 */
void guess_number(int roman) {
    int low = 1, high = 100;
    char response[3];
    char roman_mid[20];

    while (low < high) {
        int mid = (low + high) / 2;
        if (roman) {
            arabic_to_roman(mid, roman_mid);
            printf(_("Is the number greater than %s? (yes/no)\n"), roman_mid);
        } else {
            printf(_("Is the number greater than %d? (yes/no)\n"), mid);
        }

        if (scanf("%2s", response) != 1) {
            printf(_("Input error. Please try again.\n"));
            continue;
        }

        if (response[0] == 'y' || response[0] == 'Y') {
            low = mid + 1;
        } else if (response[0] == 'n' || response[0] == 'N') {
            high = mid;
        } else {
            printf(_("Input error. Please enter 'yes' or 'no'.\n"));
        }
    }

    if (roman) {
        arabic_to_roman(low, roman_mid);
        printf(_("Your number is %s!\n"), roman_mid);
    } else {
        printf(_("Your number is %d!\n"), low);
    }
}

/**
 * Печатает справку о программе
 * @param progname Имя программы
 */
void print_help(const char *progname) {
    printf(_("Usage: %s [-r|--help]\n"), progname);
    printf(_("\nOptions:\n"));
    printf(_("  -r        Use Roman numerals\n"));
    printf(_("  --help    Show this help message\n"));
}
