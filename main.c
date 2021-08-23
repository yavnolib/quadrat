#include <stdio.h>      // ввод-вывод
#include <stdlib.h>
#include <locale.h>     // setlocale ( LC_ALL, "");
#include <ctype.h>      // isdigit (c)
#include "equation.h"
#include "check_test.h"
//#include <string.h>     // strlen (a)


int main(int argc, char* argv[])
{   
    setlocale(LC_ALL, "");
    
    struct Equation test_inp;
    struct Equation test_out;
    
    start_test(&test_inp, &test_out);
    //char str[100];
    //printf("\nEnter a eq : ");
    //fgets(str, 100, stdin);
    //str_analys(str);

    //return 0;
    struct Equation quadro;
    do {
        equation_initialize(&quadro);
        enter_equation(&quadro);
        solve_eq(&quadro);
        print_roots(&quadro);
    } while (want_again());
    return 0;
}

