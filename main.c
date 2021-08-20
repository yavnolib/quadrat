#include <stdio.h>      // ввод-вывод
#include <stdlib.h>
#include <locale.h>     // setlocale ( LC_ALL, "");
#include <ctype.h>      // isdigit (c)
#include <string.h>     // strlen (a)

// Описания функций
int ABS(int n);                                   // Модуль числа
int count_x(char* str, size_t length);            // Количество "х" в строке
size_t last_x_entry (char str[], size_t length);  // Индекс последнего вхождения икса
size_t first_x_entry (char str[], size_t length); // Индекс первого вхождения икса
int ten_pow (size_t n);                           // 10^n
int get_opposite (int n);                         // Смена знака у числа
size_t pow_ch (char str[], size_t length);        // Индекс значка степени (^)
int get_ratio(char str[], size_t length, size_t left_index, size_t right_index); // Получить числовое значение коэффициентов a, b, c
int gcd(int a, int b);                // НОД 
int reduce_fraction (int a, int b);   // Сократить числа (пока криво работает)
int is_sqr(int n);                    // является ли число квадратом
int int_sqrt(int n);                  // взятие квадратного корня из целого квадрата
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

int main()
{
    setlocale (LC_ALL, "");       // русские вперёд!!!
    char str[100];                // хз зачем так много, но могу позволить

    printf( "Введите квадратное уравнение без пробелов (пример: ах^2+bx+c=0)\n" );
    scanf ( "%s", str);
    size_t len = strlen (str) - 2; // для обработки строки от ind=0 до ind<len (убирается "=0")
    /*
      !) позиция x^2 есть всегда, в отличие от х
      1) получаем количество букв х
    */
    int c_x = count_x (str, len);
    int a, b, c; // коэффициенты
    size_t x_pos, first_x_pos, last_x_pos, power_pos; // x_pos при одном иксе в строке, power_pos - индекс значка ^
    switch ( c_x ) {
        case 1:
          x_pos = first_x_entry (str, len);
          power_pos = pow_ch (str, len);
          if ( power_pos == ( len - 2 ) ) {
            // то (1*)
            printf ( "\nЕдинственное решение: x = 0" );
          }
          else{
            // то (2*)
            if ( x_pos == 0)
                a = 1;
            else{
                if ( str[0] == '-' ) {
                    if ( x_pos == 1 ) {
                        a = -1;
                    }
                    else{
                        a = get_opposite ( get_ratio ( str, len, 1, x_pos - 1 ) );
                    }
                }
                else{
                a = get_ratio (str, len, 0, x_pos - 1 );
                }
            }
            if ( str[power_pos+2] == '-' ) {
                c = get_opposite ( get_ratio (str, len, power_pos + 3, len - 1 ) );
            }
            else{
                c = get_ratio ( str, len, power_pos + 3, len - 1 );
            }
            if ( ( (c>0) && (a<0) ) || ( (c<0) && (a>0) ) ) {
                c = ABS(c);
                a = ABS(a);
                //a = a / ( c / reduce_fraction (c, a) );
                //c = reduce_fraction (c, a);
                printf("\n %d %d",c,a);
                if (a == 1){
                    printf ( "\n Ответ: x = +-sqrt(%d)", c );
                }
                else{
                printf ( "\n Ответ: x = +-sqrt(%d/%d)", c, a ); // |c| / |a|
                }
            }
            else{
                c = ABS(c);
                a = ABS(a);
                //a = a / ( c / reduce_fraction (c, a) );
                //c = reduce_fraction (c, a);
                printf("\n %d %d",c,a);
                if (a == 1){
                    printf ( "\n Ответ: x = +-i*sqrt(%d)", c );
                }
                else{
                printf ( "\n Ответ: x = +-i*sqrt(%d/%d)", c, a );
                }
            }
            // ПРАВИЛЬНЫЙ ВЫВОД С СОКРАЩЕННЫМИ ЧИСЛАМИ
          }
          break;

        case 2:
          first_x_pos = first_x_entry(str, len);
          last_x_pos  = last_x_entry (str, len);
          // поиск значения а
            if ( str[0] == '-' ) {
                if ( first_x_pos == 1 ) {
                    a = -1;
                }
                else{
                    a = get_opposite ( get_ratio ( str, len, 1, first_x_pos - 1) );
                }
            }
            else if ( !first_x_pos ){ // first_x_pos == 0
                a = 1;
            }
            else{
                a = get_ratio ( str, len, 0, first_x_pos - 1 );
            }
            // поиск значения b
            power_pos = pow_ch ( str, len); // индекс значка степени (^) в строке
            if ( str[power_pos + 2] == '-') {
                if ( (power_pos+3) == last_x_pos ) {// если сразу после знака стоит x
                    b = -1;
                }
                else{
                    b = get_opposite ( get_ratio ( str, len, power_pos + 3, last_x_pos - 1 ) );
                }
            }
            else{
                if ( ( power_pos + 3 ) == last_x_pos ){
                    b = 1;
                }
                else{
                    b = get_ratio (str, len, power_pos + 3, last_x_pos - 1 );
                }
            }

          if ( last_x_pos == (len-1) ) {
            // то (3*)
            // -b/a
            if ( ( (a>0) && (b<0) ) || ( (a<0) && (b>0) ) ) {  // если знаки разные |b|/|a|
                b = ABS(b);
                a = ABS(a);
                b = reduce_fraction (b, a);
                a = a / ( b / reduce_fraction (b, a) );
                if(a==1){
                    printf( "\nОтвет: x = 0, x = %d", b);
                }
                else{
                printf ( "\nОтвет: x = 0, x = %d/%d", b, a);
                }
            }
            else{                                              // если одинаковые   -|b| / |a|
                b = ABS(b);
                a = ABS(a);
                b = reduce_fraction (b, a);
                a = a / ( b / reduce_fraction (b, a) );
                if(a==1){
                    printf( "\nОтвет: x = 0, x = -%d", b);
                }
                else{
                printf ( "\nОтвет: x = 0, x = -%d/%d", b, a);
                }
            }
          }
          else{
            // то (4*)
            // поиск значения с
            if ( str[last_x_pos + 1] == '-') {
                c = get_opposite ( get_ratio ( str, len, last_x_pos + 2, len - 1 ) );
            }
            else{
                c = get_ratio ( str, len, last_x_pos + 2, len - 1);
            }
            int D;
            D = b*b - 4*a*c;
            printf ( "\nD=%d^2-4*%d*%d=%d", b, a, c, D );
            if ( !D ) { // D==0
                //x= -b/2a
                if ( ( (b<0) && (a>0) ) || ( (b>0) && (a<0) ) ) { // знаки разные => |b| / 2|a|
                    b = ABS(b);
                    a = 2*ABS(a);
                    b = reduce_fraction (b, a);
                    a = a / ( b / reduce_fraction (b, a) );
                    if(a==1){
                        printf ( "\n Ответ: x = %d", b);
                    }
                    else{
                    printf ( "\n Ответ: x = %d/%d", b, a);
                    }
                }
                else{
                    b = ABS(b);
                    a = 2*ABS(a);
                    b = reduce_fraction (b, a);
                    a = a / ( b / reduce_fraction (b, a) );
                    if(a==1){
                        printf ( "\n Ответ: x = -%d", b);
                    }
                    else{
                        printf ( "\n Ответ: x = -%d/%d", b, a );
                    }

                }
            }
            else if ( D>0 ) {
                b*=-1;
                printf ( "\n Ответ: x=(%d-sqrt(%d))/%d, x=(%d+sqrt(%d))/%d", b, D, 2*a, b, D, 2*a );
            }
            else{
                /*
                D<0 => x1 = ( -b - i*sqrt(|D|) )/2a
                       x2 = ( -b + i*sqrt(|D|) )/2a
                */
                printf ( "\n Ответ: x=(-%d-i*sqrt(%d))/%d, x=(-%d+i*sqrt(%d))/%d ", b, ABS(D), 2*a, b, ABS(D), 2*a);
            }
          }
          break;

        default:
          printf ( "\nКвадратное уравнение либо введено неправильно, либо введено не относительно переменной Х, либо уравнение не квадратное." );
          break;
        }
    return 0;
}




// Определения функций
int ABS(int n) {// работает
    if ( n >= 0 )
        return n;
    else
        return n * ( -1 );
}
int count_x(char str[], size_t length) { // работает
    int count = 0;
    for (size_t ind = 0; ind < length; ind++ )
    {
        if ( ( *(str + ind) == 'х' ) || ( *(str + ind) == 'x' ) )
            count = count + 1;

    }
    return count;
}
size_t last_x_entry(char str[], size_t length) { // работает
    size_t pos;
    for (size_t ind = 0; ind < length; ind++ )
    {
        if ( ( *(str + ind) == 'х' ) || ( *(str + ind) == 'x' ) )
            pos = ind;
    }
    return pos;
}
size_t first_x_entry (char str[], size_t length) { // работает
    size_t pos;
    int leng = (int) length;
    for (int ind = leng - 1; ind >= 0; ind-- )
    {
        if ( ( *(str + ind) == 'х' ) || ( *(str + ind) == 'x' ) )
            pos = ind;
    }
    return pos;
}
int ten_pow(size_t n) { // работает
    int res = 1;
    for (size_t count = 0; count < n; count++ ){
        res *= 10;
    }
    return res;
}
int get_opposite(int n) { // работает
    return n * (-1);
}
size_t pow_ch(char str[], size_t length) { // работает
    size_t pos;
    for (size_t ind = 0; ind < length; ind++ )
    {
        if (  *(str + ind) == '^' )
            pos = ind;
    }
    return pos;
}
int get_ratio(char str[], size_t length, size_t left_index, size_t right_index ) { // края включительно (работает)
    size_t capacity = right_index - left_index;
    int rate = 0;
    for (size_t ind = left_index; ind <= right_index; ind++ ){
        rate += ( (int) str[ind] - 48 ) * ten_pow (capacity);
        capacity--;
    }
    return rate;
}
int gcd(int a, int b) {
    a = ABS(a), b = ABS(b);
    if (b == 0)
        return a;
    else
        return gcd(b, a%b);
}
int reduce_fraction (int a, int b){
    int x = gcd (a, b);
    a /= x;
    b /= x;
    return a;
}
int int_sqrt(int n){
    if (n < 2)
        return n;
    else{
        int smallCandidate = int_sqrt(n >> 2) << 1;
        int largeCandidate = smallCandidate + 1;
        if ((largeCandidate*largeCandidate) > n)
            return smallCandidate;
        else
            return largeCandidate;
    }
}
int is_sqr(int n){
    if (n==(int_sqrt(n)*int_sqrt(n)))
        return 1;
    else
        return 0;
}
/// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  THE_END XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ///
