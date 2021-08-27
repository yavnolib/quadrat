#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#include "equation.h"

//======================================================================
int is_equali(int a, int b) {

    if (a == b) {
        return 1;
    }

    else {
        return 0;
    }
}

//=====================================================================
void clear_input() {
    fseek(stdin, 0, SEEK_END);
}

//======================================================================
int is_equalf(float a, float b) { // 

    if ( ( fabs(a-b) < EPSILON ) || ( (a == INFINITY) && (b == INFINITY) ) )
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
    eq->type = 0;
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
        
        status = scanf( "%f %f %f", &(eq->a), &(eq->b), &(eq->c) );
        clear_input();

        if ( status != 3 )
            fprintf(stderr, "\n\t\tWrong input\n\n");

    } while (status != 3);
    
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

    if (is_equalf(a, 0) && is_equalf(b, 0) && is_equalf(c,0) ) {
        eq->type = WITHOUT_ALL;
    }

    else if (is_equalf(b,0)) {          // ax^2+c   или ax^2 или c=0 (если а=0)

        if (is_equalf(c, 0))
            eq->type = WITHOUT_B_C;

        else if (is_equalf(a, 0))
            eq->type = NO_ROOTS_TYPE;

        else
            eq->type = WITHOUT_B;

    }

    else if (is_equalf(c, 0)) {    // ax^2+bx=0    bx=0    

        if (is_equalf(a, 0))
            eq->type = WITHOUT_A_C;

        else
            eq->type = WITHOUT_C;
    }

    else if (is_equalf(a, 0)) {
        eq->type = WITHOUT_A;
    }

    else
        eq->type = FULL;
}

//======================================================================
void print_eq_form(struct Equation* eq) {
    assert(eq != NULL);

    printf("Your equation:\n ");
 
    switch (eq->type)
    {

    case WITHOUT_A:

        if((eq->c)>0)
            printf("%.2f * x + %.2f = 0\n", eq->b, eq->c);
        else
            printf("%.2f * x - %.2f = 0\n", eq->b, fabs(eq->c));

        break;

    case WITHOUT_A_C:

        printf("%.2f * x = 0\n", eq->b);

        break;

    case WITHOUT_B:

        if((eq->c) > 0)
            printf("%.2f * x^2 + %.2f = 0\n", eq->a, eq->c);
        else
            printf("%.2f * x^2 - %.2f = 0\n", eq->a, fabs(eq->c));

        break;

    case WITHOUT_B_C:

        printf("%.2f * x^2 = 0\n", eq->a);

        break;

    case WITHOUT_C:

        if((eq->b)>0)
            printf("%.2f * x^2 + %.2f * x = 0\n", eq->a, eq->b);
        else
            printf("%.2f * x^2 - %.2f * x = 0\n", eq->a, fabs(eq->b));

        break;

    case FULL:

        if ((eq->b) > 0) {

            if ((eq->c) > 0) {
                printf("%.2f * x^2 + %.2f * x + %.2f = 0\n", eq->a, eq->b, eq->c);
            }

            else {
                printf("%.2f * x^2 + %.2f * x - %.2f = 0\n", eq->a, eq->b, fabs(eq->c));
            }

        }
        else {

            if ((eq->c) > 0) {
                printf("%.2f * x^2 - %.2f * x + %.2f = 0\n", eq->a, fabs(eq->b), eq->c);
            }

            else {
                printf("%.2f * x^2 - %.2f * x - %.2f = 0\n", eq->a, fabs(eq->b), fabs(eq->c));
            }

        }

        break;

    case WITHOUT_ALL:

        printf("0 = 0\n");

        break;

    case NO_ROOTS_TYPE:

        printf("%.2f = 0\n", eq->c);

        break;

    default:

        fprintf(stderr, "\n\t\tUNKNOWN ERROR\n\n");

        break;
    }
}


//======================================================================
void solve_eq(struct Equation* eq) {
    assert(eq != NULL);
    /*
        одна буква х
        (01*) bx+c=0        //WITHOUT_A           x=-c/b ONE_ROOT
        (02*) bx=0          // WITHOUT A_C        x=0
        (1*) ax^2=0 => x=0  // WITHOUT B_C        x=0
        (2*) ax^2+c=0 =>    // WITHOUT B          
                        if (c>0 and a<0) or (c<0 and a>0):
                            x = +-sqrt( |c|/|a| )
                        else
                            x = +-i*sqrt( |c|/|a| )
        две буквы х
        (3*) ax^2+bx=0 => x(ax+b)=0 => x=0, x=-b/a WITHOUT C
        (4*) ax^2+bx+c=0 => FULL
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

    switch (eq->type)
    {
    case WITHOUT_A:

        eq->roots_type = REAL;
        eq->root_cnt = ONE_ROOT;
        eq->x1 = (-1.0 * c) / b;
        eq->x2 = EMPTY_X;

        break;

    case WITHOUT_A_C:

        eq->roots_type = REAL;
        eq->root_cnt = ONE_ROOT;
        eq->x1 = 0;
        eq->x2 = EMPTY_X;

        break;

    case WITHOUT_B:

        if (D > FLT_MIN) { 
            eq->roots_type = REAL;
            eq->root_cnt = TWO_ROOTS;

            float sqrt = sqrtf(fabs(c) / fabs(a));
            eq->x1 = sqrt;
            eq->x2 = -1.0 * sqrt;
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
            
        }

        break;

    case WITHOUT_B_C:

        eq->roots_type = REAL;
        eq->root_cnt = ONE_ROOT;
        eq->x1 = 0;
        eq->x2 = EMPTY_X;

        break;

    case WITHOUT_C:

        eq->roots_type = REAL;
        eq->root_cnt = TWO_ROOTS;
        eq->x1 = 0;
        eq->x2 = (-1.0 * b) / a;

        break;

    case FULL:

        if (is_equalf(D, 0)) {
            eq->roots_type = REAL;
            eq->root_cnt = ONE_ROOT;
            eq->x1 = (-1.0 * b) / (2.0 * a);
            eq->x2 = EMPTY_X;
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
        }

        else if (D < 0) {
            eq->roots_type = COMPLEX;
            eq->root_cnt = TWO_COMP;
            eq->x1 = COMPLEX_X;
            eq->x2 = COMPLEX_X;
            eq->real_part = (-1.0 * b) / (2.0 * a);
            eq->imaginary_part = D_abs_sqrt / (2.0 * a);
            
        }

        break;

    case WITHOUT_ALL:

        eq->roots_type = REAL;
        eq->root_cnt = ONE_ROOT;
        eq->x1 = INFINITY;
        eq->x2 = EMPTY_X;

        break;

    case NO_ROOTS_TYPE:

        eq->roots_type = NO_ROOTS_IS;
        eq->root_cnt = NO_ROOTS_R;
        eq->x1 = EMPTY_X;
        eq->x2 = EMPTY_X;

        break;

    default:

        fprintf(stderr, "\n\t\tUNKNOWN ERROR\n\n");

        break;
    }
}

//======================================================================
void print_complex_solution(struct Equation* eq) {
    assert(eq != NULL);

    switch (eq->type)
    {
    case WITHOUT_B:
        /*
            x = +-i*sqrt( |c|/|a| )
        */
        printf("\nThe equation has solutions only in complex numbers.\nAnswer: ");
        printf("x = +-%.3f*i",eq->imaginary_part);

        break;

    case FULL:
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

        break;

    default:

        fprintf(stderr, "\n\t\tUNKNOWN ERROR\n\n");

        break;
    }
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
    
    equation_input(eq);
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
