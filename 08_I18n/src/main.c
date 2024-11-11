#include <stdio.h>
#include <locale.h>
#include <libintl.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "locales"

void guess_number();

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("guess_number", LOCALE_PATH);
    textdomain("guess_number");

    printf(_("Think of a number between 1 and 100.\n"));
    guess_number();

    return 0;
}

void guess_number() {
    int low = 1, high = 100;
    char response[3];

    while (low < high) {
        int mid = (low + high) / 2;
        printf(_("Is the number greater than %d? (yes/no)\n"), mid);
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

    printf(_("Your number is %d!\n"), low);
}

