#include <stdio.h>      // ввод-вывод
#include <stdlib.h>
#include <locale.h>     // setlocale ( LC_ALL, "");
#include <ctype.h>      // isdigit (c)
#include <string.h>     // strlen (a)
#include "equation.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    char str[100];
    printf("\nEnter a eq : ");
    fgets(str, 100, stdin);
    str_analys(str);
    return 0;
}
