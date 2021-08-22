#pragma once
#include <stdio.h>
#include "equation.h"
#include "check_test.h"
#include "math.h"
#include "assert.h"


void init_test(struct Equation* inp, struct Equation* out, float a, float b, float c, int type, int is_complex, int root, float x1, float x2) {
	assert(inp != NULL);
	assert(out != NULL);
	
	inp->a = a;
	out->a = a;

	inp->b = b;
	out->b = b;

	inp->c = c;
	out->c = c;

	inp->type = type;
	inp->is_complex = is_complex;
	inp->root = root;
	inp->x1 = x1;
	inp->x2 = x2;

	out->type = type;
	out->is_complex = 0;
	out->root = 0;
	out->x1 = NAN;
	out->x2 = NAN;

	
}

int check_ans(struct Equation* inp, struct Equation* out) {
	assert(inp != NULL);
	assert(out != NULL);

	print_eq_form(out);
	

	// roundf(val * 100) / 100
	if ((inp->is_complex) == (out->is_complex)) {
		if ((inp->root) == (out->root)) {
			if ((out->root) == TWO_COMP) {
				if (inp->x1 == COMPLEX_R) {
					return 1;
				}
				else if (inp->x2 == COMPLEX_R) {
					return 1;
				}
				else
					return 0;
			}
			else if ((out->root) == ONE_ROOT) {
				float inp_round_x1 = roundf((inp->x1) * 100.0) / 100.0;
				float out_round_x1 = roundf((out->x1) * 100.0) / 100.0;
				if ((inp_round_x1 == out_round_x1)&&((inp->x2)==(out->x2)))
					return 1;
				else
					return 0;
			}
			else if((out->root) == TWO_ROOTS){
				float inp_round_x1 = roundf((inp->x1) * 100.0) / 100.0;
				float out_round_x1 = roundf((out->x1) * 100.0) / 100.0;

				float inp_round_x2 = roundf((inp->x2) * 100.0) / 100.0;
				float out_round_x2 = roundf((out->x2) * 100.0) / 100.0;

				if ((inp_round_x1 == out_round_x1) && (inp_round_x2 == out_round_x2)) {
					return 1;
				}
				else
					return 0;
			}
			else {
				return 0;
			}

		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}
void start_test(struct Equation* input, struct Equation* output) {
	
	printf("Tests are running...\n");
	int correct_ans = 0;

	// format init_test(&input, &output, 5.48, 6.48, 0.0, WITHOUT_C, REAL, TWO_ROOTS, 0, -1.18248);
	// a, b, c, TYPE, COMPLEX, ROOT, x1, x2
	float checkers[8][8] =
	{
		{5.48, 6.48,  0.0,   WITHOUT_C,    REAL, TWO_ROOTS,        0,   -1.18248},
		{1.0 ,  0.0,  0.0, WITHOUT_B_C,    REAL,  ONE_ROOT,        0,    EMPTY_R},
		{48.8, 58.2,  1.0,        FULL,    REAL, TWO_ROOTS, -1.17519, -0.0174371},
		{-7.0, 49.0,  1.0,        FULL,    REAL, TWO_ROOTS, -0.020349,    7.0203},
		{ 0.0, 49.0,  1.0,   WITHOUT_A,    REAL,  ONE_ROOT, -0.020408,   EMPTY_R},
		{ 0.0, 49.0,  0.0, WITHOUT_A_C,    REAL,  ONE_ROOT,       0.0,   EMPTY_R},
		{ 1.0,  0.0, -9.0,   WITHOUT_B,    REAL, TWO_ROOTS,       3.0,      -3.0},
		{ 1.0,  0.0,  9.0,   WITHOUT_B, COMPLEX,  TWO_COMP, COMPLEX_R, COMPLEX_R},
	};

	for (size_t ind = 0; ind < 8; ind++) {
		init_test(input, output, checkers[ind][0], checkers[ind][1], checkers[ind][2], checkers[ind][3], 
			checkers[ind][4], checkers[ind][5], checkers[ind][6], checkers[ind][7]);
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
	case 8:
		printf("\nAll tests completed successfully\n");
		break;
	default:
		printf("\nCompleted successfully %d tests.\n",correct_ans);
		break;
	}

}
