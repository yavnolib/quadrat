#pragma once
#include <stdio.h>
#include "equation.h"

void init_test(struct Equation* inp, struct Equation* out, float a, float b, float c, int type, int is_complex, int root, float x1, float x2);

int check_ans(struct Equation* inp, struct Equation* out);

void start_test(struct Equation* input, struct Equation* output);
