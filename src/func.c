#include <stdio.h> 
#include "equation.h"

// возможные формы уравнений
    /* Возможные варианты после ввода
            ax^2+bx+c=0     x^2+x+c=0   x^2+bx+c=0  ax^2+x+c=0   -  2 буквы х
            ax^2+bx=0       x^2+x=0     x^2+bx=0    ax^2+x=0     -  2 буквы х

            ax^2+c=0        x^2+c=0                              -  1 буква х
            ax^2=0          x^2=0                                -  1 буква х

    */
    /*
    одна буква х
    (1*) ax^2=0 => x=0
    (2*) ax^2+c=0 =>
                    if (c>0 and a<0) or (c<0 and a>0):
                        x = +-sqrt( |c|/|a| )
                    else
                        x = +-i*sqrt( |c|/|a| )
    две буквы х
    (3*) ax^2+bx=0 => x(ax+b)=0 => x=0, x=-b/a
    (4*) ax^2+bx+c=0 =>
        D=b^2-4*a*c
        switch(D):
            D=0 => x=-b/2a
            D>0 => x1 = ( -b - sqrt(D) )/2a
                   x2 = ( -b + sqrt(D) )/2a
            D<0 => x1 = ( -b - i*sqrt(|D|) )/2a
                   x2 = ( -b + i*sqrt(|D|) )/2a
    */

// Определения функций
int ABS(int n) {// работает
    if (n >= 0)
        return n;
    else
        return n * (-1);
}
int count_x(char str[], size_t length) { // работает
    int count = 0;
    for (size_t ind = 0; ind < length; ind++)
    {
        if ((*(str + ind) == 'х') || (*(str + ind) == 'x'))
            count = count + 1;

    }
    return count;
}
size_t last_x_entry(char str[], size_t length) { // работает
    size_t pos;
    for (size_t ind = 0; ind < length; ind++)
    {
        if ((*(str + ind) == 'х') || (*(str + ind) == 'x'))
            pos = ind;
    }
    return pos;
}
size_t first_x_entry(char str[], size_t length) { // работает
    size_t pos;
    int leng = (int)length;
    for (int ind = leng - 1; ind >= 0; ind--)
    {
        if ((*(str + ind) == 'х') || (*(str + ind) == 'x'))
            pos = ind;
    }
    return pos;
}
int ten_pow(size_t n) { // работает
    int res = 1;
    for (size_t count = 0; count < n; count++) {
        res *= 10;
    }
    return res;
}
int get_opposite(int n) { // работает
    return n * (-1);
}
size_t pow_ch(char str[], size_t length) { // работает
    size_t pos;
    for (size_t ind = 0; ind < length; ind++)
    {
        if (*(str + ind) == '^')
            pos = ind;
    }
    return pos;
}
int get_ratio(char str[], size_t length, size_t left_index, size_t right_index) { // края включительно (работает)
    size_t capacity = right_index - left_index;
    int rate = 0;
    for (size_t ind = left_index; ind <= right_index; ind++) {
        rate += ((int)str[ind] - 48) * ten_pow(capacity);
        capacity--;
    }
    return rate;
}
int gcd(int a, int b) {
    a = ABS(a), b = ABS(b);
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int reduce_fraction(int a, int b) {
    int x = gcd(a, b);
    a /= x;
    b /= x;
    return a;
}
int int_sqrt(int n) {
    if (n < 2)
        return n;
    else {
        int smallCandidate = int_sqrt(n >> 2) << 1;
        int largeCandidate = smallCandidate + 1;
        if ((largeCandidate * largeCandidate) > n)
            return smallCandidate;
        else
            return largeCandidate;
    }
}
int is_sqr(int n) {
    if (n == (int_sqrt(n) * int_sqrt(n)))
        return 1;
    else
        return 0;
}
