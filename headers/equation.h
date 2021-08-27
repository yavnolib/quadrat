#pragma once
/*! \file equation.h
 * Equation's properties. */

#include <stdio.h>      

 //! Constant for comparison of float
#define EPSILON 1e-4

 //! \struct Equation "equation.h"
 /*! Structure of the equation, which include equation'c coefficients, roots and equation's type. */
struct Equation {
    float a; /*!< Coefficient with x^2. */
    float b; /*!< Coefficient with x^1. */
    float c; /*!< Coefficient with x^0. */
    float x1; /*!< First possible root. */
    float x2; /*!< Second possible root. */
    float real_part; /*!< Real part of complex root. */
    float imaginary_part; /*!< Imaginary part of complex root. */
    int type; /*!< Type of equation. */
    int roots_type; /*!< Root type. */
    int root_cnt; /*!< Number of roots. */
};

//! \enum x_type "equation.h"
/*! Constants for type of root */
enum x_type {
    EMPTY_X = 22222, /*!< Constant for empty root */
    COMPLEX_X = 22223       /*!< Constant for complex root */
};

//! \enum x_type "equation.h"
/*! Constants for number of roots */
enum root_count {
    ONE_ROOT =   11111, /*!< Constant for equation with one root */
    NO_ROOTS_R = 11112,       /*!< Constant for equation without roots */
    TWO_ROOTS =  11113,        /*!< Constant for equation with two roots */
    TWO_COMP =   11114          /*!< Constant for equation with two complex roots */
};

//! \enum x_type "equation.h"
/*! Constants for type of equation */
enum equation_type {
    WITHOUT_ALL = 88888, /*!< Constant for equation without a,b,c coefficients */
    NO_ROOTS_TYPE = 88889,       /*!< Constant for equation without roots */
    WITHOUT_A = 88890,           /*!< Constant for equation without a coefficient */
    WITHOUT_A_C = 89891,         /*!< Constant for equation without a, c coefficients */        
    WITHOUT_B = 88892,           /*!< Constant for equation without b coefficient */
    WITHOUT_B_C = 88893,         /*!< Constant for equation without b, c coefficients */
    WITHOUT_C = 83894,           /*!< Constant for equation without c coefficient */
    FULL = 88895                /*!< Constant for equation with all coefficients */
};

//! \enum x_type "equation.h"
/*! Constants for type of equation's roots */
enum iscomplex_type {
    COMPLEX = 33333,     /*!< Constant for equation with complex roots */
    REAL = 33334,                /*!< Constant for equation with not complex roots */
    NO_ROOTS_IS = 33335         /*!< Constant for equation without routs */
};


//! Initializes equation, leaving all its members in valid state
//! before input is placed.
/*! \param equation - the equation to be initialized */
void equation_initialize(struct Equation* eq);

//! Function that receives input from user.
/*! \param equation - the equation where input should be placed. */
void equation_input(struct Equation* eq);

//! A function that determines the type of an equation
/*! \param equation - introduced equation. */
void get_eq_type(struct Equation* eq);

//! A function that displays the entered equation in its normal form
/*! \param equation - introduced equation. */
void print_eq_form(struct Equation* eq);

//! Solves the equation, roots are places into the equation's structure.
/*! \param equation - the equation to be solved. */
void solve_eq(struct Equation* eq);

//! A function that outputs the complex roots of an equation if they are
/*! \param equation - equation with type COMPLEX. */
void print_complex_solution(struct Equation* eq);

//! A function that outputs all the roots of the equation
/*! \param equation - solved equation. */
void print_roots(struct Equation* eq);

//! A function that combines inputting an equation, getting its type, and outputting an equation
/*! \param equation - equation to be introduced. */
void enter_equation(struct Equation* eq);

//! A function that asks if the user wants to continue
int want_again();

//! A function that tests the equality of two float numbers
/*! \param equation - two float numbers. */
int is_equalf(float a, float b);

//! A function that tests the equality of two integer numbers
/*! \param equation - two integer numbers. */
int is_equali(int a, int b);

//! A function for clear input
void clear_input();
