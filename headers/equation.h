#pragma once
/*! \file equation.h
 * Equation's properties. */


#include <stdio.h>      

 //! constant for number comparisons
#define PRECISION 1e-6


 //! constant for equation without a
#define WITHOUT_A 55555

 //! constant for equation without a and c
#define WITHOUT_A_C 66666

 //! constant for equation without b
#define WITHOUT_B 77777 

 //! constant for equation without b and c
#define WITHOUT_B_C 88888

 //! constant for equation without c
#define WITHOUT_C 99999

 //! constant for full equation
#define FULL 12121

 //! constant for complex solutions
#define COMPLEX 44444

 //! constant for real solutions
#define REAL 33333

 //! constant for equations with two solutions
#define TWO_ROOTS 12345

 //! constant for equations with one solution
#define ONE_ROOT 11111

 //! constant for equations with two complex solutions
#define TWO_COMP 21313

//! constant for empty root
#define EMPTY_R 85585

//! constant for complex root
#define COMPLEX_R 56794

//! \struct Equation "equation.h"
/*! Structure of the equation, which include equation'c coefficients, roots and equation's type. */
struct Equation {
	float a; /*!< Coefficient with x^2. */
	float b; /*!< Coefficient with x^1. */
	float c; /*!< Coefficient with x^0. */
	float x1; /*!< First possible root. */
	float x2; /*!< Second possible root. */
	int type; /*!< Type of equation. */
	int is_complex; /*!< Root type. */
	int root; /*!< Number of roots. */
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
