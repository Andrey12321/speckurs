#include "roman.h"
#include <string.h>

const RomanNumeral roman_table[] = {
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"},
    {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

/**
 * Преобразует римское число в арабское
 * @param roman Римское число
 * @return Арабское число
 */
int roman_to_arabic(const char *roman) {
    int result = 0;
    for (int i = 0; roman[i] != '\0'; i++) {
        for (int j = 0; j < sizeof(roman_table) / sizeof(roman_table[0]); j++) {
            if (strncmp(roman + i, roman_table[j].roman, strlen(roman_table[j].roman)) == 0) {
                result += roman_table[j].value;
                i += strlen(roman_table[j].roman) - 1;
                break;
            }
        }
    }
    return result;
}

/**
 * Преобразует арабское число в римское
 * @param number Арабское число
 * @param result Римское число (выходной параметр)
 */
void arabic_to_roman(int number, char *result) {
    result[0] = '\0';
    for (int i = 0; i < sizeof(roman_table) / sizeof(roman_table[0]); i++) {
        while (number >= roman_table[i].value) {
            strcat(result, roman_table[i].roman);
            number -= roman_table[i].value;
        }
    }
}
