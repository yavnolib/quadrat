#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#include "equation.h"

//======================================================================
int is_equali(int a, int b) {
    return (a == b) ? 1 : 0;

}

//=====================================================================
void clear_input() {
    fseek(stdin, 0, SEEK_END);

}

//======================================================================
int is_equalf(float a, float b) {

    if ((fabs(a - b) < EPSILON) || ((a == INFINITY) && (b == INFINITY)))
        return 1;
    else
        return 0;

}

//======================================================================
void equation_initialize(struct Equation* eq, int except) {
    assert(eq != NULL);

    eq->a = NAN;
    eq->b = NAN;
    eq->c = NAN;
    eq->x1 = NAN;
    eq->x2 = NAN;

    eq->bin_type = 0;
    eq->roots_type = 0;
    eq->root_cnt = 0;
    eq->imaginary_part = NAN;
    eq->real_part = NAN;

}

//======================================================================
void equation_input(struct Equation* eq) {
    assert(eq != NULL);

    char answer = 0;
    int status = 0;

    do {
        printf("Please enter quadratic equation's coefficients:\n");

        status = scanf("%f %f %f", &(eq->a), &(eq->b), &(eq->c));
        clear_input();

        if (status != 3)
            fprintf(stderr, "\n\t\tWrong input\n\n");

    } while (status != 3);

    assert(isfinite(eq->a));
    assert(isfinite(eq->b));
    assert(isfinite(eq->c));
}

//======================================================================
void equation_input_with_args(struct Equation* eq, int a, int b, int c) {
    assert(eq != NULL);

    eq->a = a;
    eq->b = b;
    eq->c = c;

    assert(isfinite(eq->a));
    assert(isfinite(eq->b));
    assert(isfinite(eq->c));
}

//======================================================================
void get_eq_type(struct Equation* eq) {
    assert(eq != NULL);

    float a = eq->a;
    float b = eq->b;
    float c = eq->c;

    eq->bin_type = COEFF_ALL;

    if (is_equalf(a, 0)) eq->bin_type &= ~COEFF_A;    //  00000111 11111011 000000011
    if (is_equalf(b, 0)) eq->bin_type &= ~COEFF_B;
    if (is_equalf(c, 0)) eq->bin_type &= ~COEFF_C;
}

//======================================================================
void print_eq_form(struct Equation* eq) {
    assert(eq != NULL);
    // WITHOUT ALL  0                   0 = 0
    // 4 = 100                ax^2 = 0
    // 1 = 001              c = 0
    // 5 = 101                  ax^2+c = 0
    // 2 = 010                bx = 0
    // 6 = 110                  ax^2+bx = 0
    // 3 = 011                  bx+c = 0
    // 7 = 111                       ax^2+bx+c = 0
    printf("\nEntered coefficients:\n");

    if (eq->bin_type == NO_COEFF) // a = 0, b = 0, c = 0
        printf("0 = 0\n");

    else {
        if (eq->bin_type & COEFF_A) {
            printf("a = %.2f\n", eq->a);
        }
        if (eq->bin_type & COEFF_B) {
            printf("b = %.2f\n", eq->b);
        }
        if (eq->bin_type & COEFF_C) {
            printf("c = %.2f\n", eq->c);
        }
    }

    printf("\n");

}


//======================================================================
void solve_eq(struct Equation* eq) {
    assert(eq != NULL);
    /*
        одна буква х
        (01*) bx+c=0        //3           x=-c/b ONE_ROOT
        (02*) bx=0          // WITHOUT A_C        x=0
        (1*) ax^2=0 => x=0  // WITHOUT B_C        x=0
        (2*) ax^2+c=0 =>    // WITHOUT B
                        if (c>0 and a<0) or (c<0 and a>0):
                            x = +-sqrt( |c|/|a| )
                        else
                            x = +-i*sqrt( |c|/|a| )
        две буквы х
        (3*) ax^2+bx=0 => x(ax+b)=0 => x=0, x=-b/a WITHOUT C
        (4*) ax^2+bx+c=0 => 7
            D=b^2-4*a*c
            switch(D):
                D=0 => x=-b/2a
                D>0 => x1 = ( -b - sqrt(D) )/2a
                       x2 = ( -b + sqrt(D) )/2a
                D<0 => x1 = ( -b - i*sqrt(|D|) )/2a
                       x2 = ( -b + i*sqrt(|D|) )/2a
    */
    float a = eq->a;
    float b = eq->b;
    float c = eq->c;

    float D = b * b - 4 * a * c;
    float D_abs_sqrt = sqrtf(fabs(D));
    float sqrt_d = sqrtf(D);

    assert(!((a == INFINITY) && (b == INFINITY))); // D_OVERFLOW

    float x1 = 0.0;
    float x2 = 0.0;

    if (!(eq->bin_type & COEFF_ALL)) {              // W/O ALL
        eq->roots_type = REAL;
        eq->root_cnt = ONE_ROOT;
        eq->x1 = INFINITY;
        eq->x2 = EMPTY_X;
        return;

    }

    if ((eq->bin_type & (COEFF_A | COEFF_B)) == 0) {      // W/o AB

        eq->roots_type = NO_ROOTS_IS;
        eq->root_cnt = NO_ROOTS_R;
        eq->x1 = EMPTY_X;
        eq->x2 = EMPTY_X;
        return;

    }

    if ((eq->bin_type & (COEFF_B | COEFF_C)) == 0) {  // W/O BC

        eq->roots_type = REAL;
        eq->root_cnt = ONE_ROOT;
        eq->x1 = 0;
        eq->x2 = EMPTY_X;
        return;

    }

    if ((eq->bin_type & (COEFF_A | COEFF_C)) == 0)  //    W/O AC
    {
        eq->roots_type = REAL;
        eq->root_cnt = ONE_ROOT;
        eq->x1 = 0;
        eq->x2 = EMPTY_X;

        return;
    }

    if (!(eq->bin_type & COEFF_A)) //WITHOUT A
    {
        eq->roots_type = REAL;
        eq->root_cnt = ONE_ROOT;
        eq->x1 = (-1.0 * c) / b;
        eq->x2 = EMPTY_X;

        return;
    }


    if ((!(eq->bin_type & COEFF_B))) { // WITHOUT B

        if (D > FLT_MIN) {
            eq->roots_type = REAL;
            eq->root_cnt = TWO_ROOTS;

            float sqrt = sqrtf(fabs(c) / fabs(a));
            eq->x1 = sqrt;
            eq->x2 = -1.0 * sqrt;
            return;

        }

        else {
            /*
            x = +-i*sqrt( |c|/|a| )
            */
            eq->roots_type = COMPLEX;
            eq->root_cnt = TWO_COMP;
            eq->x1 = COMPLEX_X;
            eq->x2 = COMPLEX_X;
            eq->real_part = 0.0;
            eq->imaginary_part = sqrtf(fabs(eq->c) / fabs(eq->a));
            return;

        }

    }

    if ((!(eq->bin_type & COEFF_C))) {          //  W/O C

        eq->roots_type = REAL;
        eq->root_cnt = TWO_ROOTS;
        eq->x1 = 0;
        eq->x2 = (-1.0 * b) / a;
        return;

    }

    if (eq->bin_type == COEFF_ALL) {            // 7

        if (is_equalf(D, 0)) {
            eq->roots_type = REAL;
            eq->root_cnt = ONE_ROOT;
            eq->x1 = (-1.0 * b) / (2.0 * a);
            eq->x2 = EMPTY_X;
            return;

        }
        else if (D > 0) {
            eq->roots_type = REAL;
            eq->root_cnt = TWO_ROOTS;

            x1 = ((-1.0 * b) - sqrt_d) / (2.0 * a);
            x2 = ((-1.0 * b) + sqrt_d) / (2.0 * a);

            if (x1 < x2) {
                eq->x1 = x1;
                eq->x2 = x2;
            }
            else {
                eq->x1 = x2;
                eq->x2 = x1;
            }
            return;

        }

        else if (D < 0) {
            eq->roots_type = COMPLEX;
            eq->root_cnt = TWO_COMP;
            eq->x1 = COMPLEX_X;
            eq->x2 = COMPLEX_X;
            eq->real_part = (-1.0 * b) / (2.0 * a);
            eq->imaginary_part = D_abs_sqrt / (2.0 * a);
            return;

        }

    }


    fprintf(stderr, "\n\t\tUNKNOWN ERROR\n\n");

}

//======================================================================
void print_complex_solution(struct Equation* eq) {
    assert(eq != NULL);

    if ((!(eq->bin_type & COEFF_B))) {
        /*
            x = +-i*sqrt( |c|/|a| )
        */
        printf("\nThe equation has solutions only in complex numbers.\nAnswer: ");
        printf("x = +-%.3f*i", eq->imaginary_part);
        return;

    }

    if (eq->bin_type == COEFF_ALL) {
        /*
                    D<0 => x1 = ( -b - i*sqrt(|D|) )/2a
                           x2 = ( -b + i*sqrt(|D|) )/2a
        */
        printf("\nDiscriminant less than zero.\nThe equation has solutions only in complex numbers.\nAnswer: ");

        if (eq->a > 0) {
            printf("x = %.2f + %.2f*i ; ", eq->real_part, eq->imaginary_part);
            printf("x = %.2f - %.2f*i\n", eq->real_part, eq->imaginary_part);
        }
        else {
            printf("x = %.2f + %.2f*i ; ", eq->real_part, -1.0 * eq->imaginary_part);
            printf("x = %.2f - %.2f*i\n", eq->real_part, -1.0 * eq->imaginary_part);
        }

        return;
    }

    fprintf(stderr, "\n\t\tUNKNOWN ERROR\n\n");

}

//======================================================================
void print_roots(struct Equation* eq) {
    assert(eq != NULL);

    if ((eq->roots_type) == COMPLEX)
        print_complex_solution(eq);

    else {
        switch (eq->root_cnt)
        {
        case ONE_ROOT:

            printf("\nAnswer: x = %.2f", eq->x1);

            break;

        case TWO_ROOTS:

            printf("\nAnswer: x = %.2f ; x = %.2f", eq->x1, eq->x2);

            break;

        case NO_ROOTS_R:

            printf("\nNo solutions");

            break;

        default:

            fprintf(stderr, "\n\t\tUNKNOWN ERROR\n\n");

            break;
        }
    }
}

//======================================================================
void enter_equation(struct Equation* eq) {
    assert(eq != NULL);

    get_eq_type(eq);
    print_eq_form(eq); // return values if error 
}

//======================================================================
int want_again() {
    char y_or_n = 0;

    printf("\nWant to introduce another equation? y/n: ");
    scanf("%c", &y_or_n);
    clear_input();

    if ((y_or_n == 'y') || (y_or_n == 'Y')) {
        return 1;
    }
    else if ((y_or_n == 'n') || (y_or_n == 'N')) {
        return 0;
    }
    else {
        printf("\nEnter y to continue or n to terminate the program");
        want_again();
    }
}

//=======================================================================
void set_bit(int* eq_type, int pos) {
    int bit = 1;
    pos -= 1;
    bit = bit << pos;
    *eq_type = *eq_type | bit;
}

//======================================================================
int get_bit(int eq_type, int pos) {
    switch (pos)
    {
    case 1:
        return (eq_type & 1) ? 1 : 0;
        break;

    case 2:
        return (eq_type & 2) ? 1 : 0;
        break;

    case 3:
        return (eq_type & 4) ? 1 : 0;
        break;

    default:
        printf("\tUNKNOWN ERROR\n");
        return -1;
        break;
    }
}

//=======================================================================
int is_positive(float a) {
    return (a > 0) ? 1 : 0;

}

//=======================================================================
int invert(int bin) {
    int inv_bin = ~bin;                                // 00000100   11111011 & 00000111 = 011
    inv_bin &= 7;
    return inv_bin;

}
