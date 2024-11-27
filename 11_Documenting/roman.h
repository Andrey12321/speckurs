#ifndef ROMAN_H
#define ROMAN_H

// Структура для римских чисел
typedef struct {
    int value;
    const char *roman;
} RomanNumeral;

int roman_to_arabic(const char *roman);
void arabic_to_roman(int number, char *result);

#endif // ROMAN_H
