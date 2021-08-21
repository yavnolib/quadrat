#include <stdio.h>      // ввод-вывод
#include <stdlib.h>
#include <locale.h>     // setlocale ( LC_ALL, "");
#include <ctype.h>      // isdigit (c)
#include "equation.h"
//#include <string.h>     // strlen (a)


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    //char str[100];
    //printf("\nEnter a eq : ");
    //fgets(str, 100, stdin);
    //str_analys(str);
    //return 0;
    struct Equation quadro;
    enter_equation(&quadro);
    solve_and_print(&quadro);
    return 0;
}

