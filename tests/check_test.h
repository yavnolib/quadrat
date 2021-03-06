#pragma once

#include <stdio.h>
#include "equation.h"

void init_test(struct Equation* inp, struct Equation* out,
               float a, float b, float c,
               int type, int roots_type, int root,
               float x1, float x2,
               float real_part, float imaginary_part);

int check_ans(struct Equation* inp, struct Equation* out);

void start_test(struct Equation* input, struct Equation* output);