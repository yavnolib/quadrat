#pragma once
#include <stdio.h>
#include "equation.h"
#include "check_test.h"
#include "math.h"
#include "assert.h"


void init_test(struct Equation* inp, struct Equation* out, 
			   float a, float b, float c, int type, 
			   int is_complex, int root, float x1, float x2) {

	assert(inp != NULL);
	assert(out != NULL);
	
	inp->a = a;
	out->a = a;

	inp->b = b;
	out->b = b;

	inp->c = c;
	out->c = c;

	inp->type = type;
	out->type = type;

	inp->is_complex = is_complex;
	inp->root = root;
	inp->x1 = x1;
	inp->x2 = x2;

	
	out->is_complex = 0;
	out->root = 0;
	out->x1 = NAN;
	out->x2 = NAN;
}

int check_ans(struct Equation* inp, struct Equation* out) {
	assert(inp != NULL);
	assert(out != NULL);

	printf("\nТестовое уравнение:");
	print_eq_form(out);
	
	if ((inp->is_complex == out->is_complex) && (inp->root == out->root)) {

		switch (inp->root)
		{
		case TWO_COMP:

			if (is_equali(inp->x1, out->x1) && is_equali(inp->x2, out->x2))
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

			if (is_equali(inp->x1, out->x1) && is_equali(inp->x2, out->x2))
				return 1;

			break;

		default:

			fprintf(stderr, "\n\t\tUNKNOWN ERROR\n\n");
 
			break;
		}
	}

	return 0;

}

void start_test(struct Equation* input, struct Equation* output) {
	
	printf("Tests are running...\n");
	int correct_ans = 0;

	// format init_test(&input, &output, 5.48, 6.48, 0.0, WITHOUT_C, REAL, TWO_ROOTS, 0, -1.18248);
	// a, b, c, TYPE, COMPLEX, ROOT, x1, x2
	float checkers[TEST_COUNT][TEST_ARGS] =
	{
		{5.48, 6.48,  0.0,     WITHOUT_C,         REAL,		 TWO_ROOTS,        0,   -1.18248},
		{1.0 ,  0.0,  0.0,   WITHOUT_B_C,         REAL,		  ONE_ROOT,        0,    EMPTY_X},
		{48.8, 58.2,  1.0,          FULL,         REAL,		 TWO_ROOTS, -1.17519, -0.0174371},
		{-7.0, 49.0,  1.0,          FULL,         REAL,		 TWO_ROOTS, -0.020349,    7.0203},
		{ 0.0, 49.0,  1.0,     WITHOUT_A,		  REAL,		  ONE_ROOT, -0.020408,   EMPTY_X},
		{ 0.0, 49.0,  0.0,   WITHOUT_A_C,         REAL,		  ONE_ROOT,       0.0,   EMPTY_X},
		{ 1.0,  0.0, -9.0,     WITHOUT_B,         REAL,		 TWO_ROOTS,       3.0,      -3.0},
		{ 1.0,  0.0,  9.0,     WITHOUT_B,      COMPLEX,		  TWO_COMP, COMPLEX_X, COMPLEX_X},
		{ 0.0,  0.0,  0.0,   WITHOUT_ALL,		  REAL,		  ONE_ROOT,  INFINITY,   EMPTY_X},
		{ 0.0,  0.0,  9.0, NO_ROOTS_TYPE,  NO_ROOTS_IS,		NO_ROOTS_R,   EMPTY_X,   EMPTY_X},
	};

	for (size_t i = 0; i < TEST_COUNT; i++) {

		init_test(input, output, checkers[i][0], checkers[i][1], checkers[i][2], checkers[i][3], 
			checkers[i][4], checkers[i][5], checkers[i][6], checkers[i][7]);

		solve_eq(output);

		if (check_ans(input, output)) {
			printf("Ответы совпали\n");
			correct_ans++;
		}

		else {
			printf("Ответы НЕ совпали\n");
		}

	}

	switch (correct_ans)
	{
	case TEST_COUNT:

		printf("\nAll tests completed successfully\n");

		break;

	default:

		printf("\nCompleted successfully %d tests.\n",correct_ans);

		break;
	}
}
