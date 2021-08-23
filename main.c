/*! \mainpage QUADRAT
 *
 * \section intro_sec Introduction
 * This program allows you to solve quadratic and linear equations, displays the answer in fractional numbers, rounded to two decimal places.
 * - The program can solve equations with complex roots.
 * - You can enter multiple equations if you like. The program will ask you if you want to enter a new equation or not (y/n?)
 */

#include <stdio.h>      
#include <stdlib.h>
#include <locale.h>     
#include <ctype.h>      
#include "equation.h"
#include "check_test.h"


int main(int argc, char* argv[])
{   
    setlocale(LC_ALL, "");
    
    struct Equation test_inp;
    struct Equation test_out;

    struct Equation quadro;
    
    start_test(&test_inp, &test_out);
    
    do {
        equation_initialize(&quadro);
        enter_equation(&quadro);
        solve_eq(&quadro);
        print_roots(&quadro);
    } while (want_again());

    return 0;
}

