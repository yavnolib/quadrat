#pragma once
#include <stdio.h>
#include "equation.h"
#include "check_test.h"
#include <math.h>
#include <assert.h>
#include "colorized_term.h"

void init_test(struct Equation* inp, struct Equation* out, 
			   float a, float b, float c,
			   int type, int roots_type, int root_cnt,
	           float x1, float x2, 
			   float real_part, float imaginary_part) {

	assert(inp != NULL);
	assert(out != NULL);
	
	inp->a = a;
	out->a = a;

	inp->b = b;
	out->b = b;


	inp->c = c;
	out->c = c;

	inp->real_part = real_part; inp->imaginary_part = imaginary_part;

	out->real_part = NAN; out->imaginary_part = NAN;

	inp->type = type;
	out->type = type;

	inp->roots_type = roots_type; // roots_type
	inp->root_cnt = root_cnt;
	inp->x1 = x1;
	inp->x2 = x2;

	
	out->roots_type = 0;
	out->root_cnt = 0;
	out->x1 = NAN;
	out->x2 = NAN;
}

int check_ans(struct Equation* inp, struct Equation* out) {
	assert(inp != NULL);
	assert(out != NULL);
	
	static int count = 1;
	printf("\n==============\nTest number: %d\n", count);
	count++;

	print_eq_form(out);
	
	if ((inp->roots_type == out->roots_type) && (inp->root_cnt == out->root_cnt)) {

		switch (inp->root_cnt)
		{
		case TWO_COMP:

			if (is_equalf(inp->real_part, out->real_part) && is_equalf(inp->imaginary_part, out->imaginary_part)) // check complex and real part, add in struct
				return 1;

			break;

		case ONE_ROOT:

			if (is_equalf((inp->x1), (out->x1)) && is_equali(inp->x2,out->x2))
				return 1;


			break;

		case TWO_ROOTS:

			if (is_equalf((inp->x1), (out->x1)) && is_equalf((inp->x2), (out->x2)))
				return 1;

			break;

		case NO_ROOTS_R:

			if (is_equalf(inp->x1, out->x1) && is_equalf(inp->x2, out->x2))
				return 1;

			break;

		default:

			fprintf(stderr, "\n\t\tUNKNOWN ERROR\n\n");
 
			break;
		}
	}

	return 0;

}
void print_data(struct Equation* input, struct Equation* output, int correct) {

	if (correct) {
		printf("\n"ANSI_COLOR_GREEN    "The answers matched"     ANSI_COLOR_RESET "\n");
		printf("Data:\ninput: a = %.2f, b = %.2f, c = %.2f\n\t x1 = %.2f, x2 = %.2f\n",
			input->a, input->b, input->c, input->x1, input->x2);
		printf("output: a = %.2f, b = %.2f, c = %.2f\n\t x1 = %.2f, x2 = %.2f\n",
			input->a, input->b, input->c, input->x1, input->x2);
	}

	else {
		printf("\n"ANSI_COLOR_RED     "The answers NOT matched"     ANSI_COLOR_RESET "\n");
		printf("Data:\ninput: a = %.2f, b = %.2f, c = %.2f\n\t x1 = %.2f, x2 = %.2f\n",
			input->a, input->b, input->c, input->x1, input->x2);
		printf("output: a = %.2f, b = %.2f, c = %.2f\n\t x1 = %.2f, x2 = %.2f\n",
			input->a, input->b, input->c, input->x1, input->x2);
	}

}
void start_test(struct Equation* input, struct Equation* output) {
	
	printf("Tests are running...\n");
	int correct_ans = 0;

	// format init_test(&input, &output, 5.48, 6.48, 0.0, WITHOUT_C, REAL, TWO_ROOTS, 0, -1.18248);
	// a, b, c, TYPE, COMPLEX, ROOT, x1, x2, real_part, imaginary_part
	float checkers[TEST_COUNT][TEST_ARGS] =
	{
		{5.48, 6.48,  0.0,     WITHOUT_C,         REAL,		 TWO_ROOTS,        0,   -1.18248, 0, 0},
		{1.0 ,  0.0,  0.0,   WITHOUT_B_C,         REAL,		  ONE_ROOT,        0,    EMPTY_X, 0, 0},
		{48.8, 58.2,  1.0,          FULL,         REAL,		 TWO_ROOTS, -1.17519, -0.0174371, 0, 0},
		{-7.0, 49.0,  1.0,          FULL,         REAL,		 TWO_ROOTS, -0.020349,    7.0203, 0, 0},
		{ 0.0, 49.0,  1.0,     WITHOUT_A,		  REAL,		  ONE_ROOT, -0.020408,   EMPTY_X, 0, 0},
		{ 0.0, 49.0,  0.0,   WITHOUT_A_C,         REAL,		  ONE_ROOT,       0.0,   EMPTY_X, 0, 0},
		{ 1.0,  0.0, -9.0,     WITHOUT_B,         REAL,		 TWO_ROOTS,       3.0,      -3.0, 0, 0},
		{ 1.0,  0.0,  9.0,     WITHOUT_B,      COMPLEX,		  TWO_COMP, COMPLEX_X, COMPLEX_X, 0, 3},
		{ 0.0,  0.0,  0.0,   WITHOUT_ALL,		  REAL,		  ONE_ROOT,  INFINITY,   EMPTY_X, 0, 0},
		{ 0.0,  0.0,  9.0, NO_ROOTS_TYPE,  NO_ROOTS_IS,		NO_ROOTS_R,   EMPTY_X,   EMPTY_X, 0, 0},
	};

	for (size_t i = 0; i < TEST_COUNT; i++) {

		init_test(input, output, checkers[i][0], checkers[i][1], checkers[i][2], checkers[i][3], 
			checkers[i][4], checkers[i][5], checkers[i][6], checkers[i][7], checkers[i][8], checkers[i][9]);

		solve_eq(output);

		if (check_ans(input, output)) {
			print_data(input, output, TRUE);
			correct_ans++;
		}

		else {
			print_data(input, output, FALSE);
		}

	}

	switch (correct_ans)
	{
	case TEST_COUNT:

		printf("\nAll tests completed successfully\n===========\n");

		break;

	default:

		printf("\nCompleted successfully %d tests.\n===========\n", correct_ans);

		break;
	}

}
