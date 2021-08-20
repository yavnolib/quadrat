#pragma once
#define _CRT_SECURE_NO_WARNINGS
// Описания функций
int ABS(int n);                                   // Модуль числа
int count_x(char* str, size_t length);            // Количество "х" в строке
size_t last_x_entry(char str[], size_t length);  // Индекс последнего вхождения икса
size_t first_x_entry(char str[], size_t length); // Индекс первого вхождения икса
int ten_pow(size_t n);                           // 10^n
int get_opposite(int n);                         // Смена знака у числа
size_t pow_ch(char str[], size_t length);        // Индекс значка степени (^)
int get_ratio(char str[], size_t length, size_t left_index, size_t right_index); // Получить числовое значение коэффициентов a, b, c
int gcd(int a, int b);
int reduce_fraction(int a, int b);
void new_reduce(int* a, int* b);
char* remove_white_spaces(char* str);
int is_equal(char* str);
int RemoveEq(char* str);
void str_analys(char* str);
int is_sqr(int n);
int int_sqrt(int n);
