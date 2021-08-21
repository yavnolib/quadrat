#pragma once
#include <stdio.h>      

#define WITHOUT_A 55555   
#define WITHOUT_A_C 66666 
#define WITHOUT_B 77777 
#define WITHOUT_B_C 88888 
#define WITHOUT_C 99999 
#define FULL 12121 

#define COMPLEX 44444
#define REAL 33333

#define TWO_ROOTS 12345
#define ONE_ROOT 11111
#define TWO_COMP 21313

struct Equation {
	float a;
	float b;
	float c;
	float x1;
	float x2;
	int type;
	int is_complex;
	int root;
};
void equation_initialize(struct Equation* eq);
void equation_input(struct Equation* eq);
void get_eq_type(struct Equation* eq);
void print_eq_form(struct Equation* eq);
void solve_eq(struct Equation* eq);
void print_complex_solution(struct Equation* eq);
void print_roots(struct Equation* eq);
void enter_equation(struct Equation* eq);
void solve_and_print(struct Equation* eq);
