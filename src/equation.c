#include <stdio.h>
#include "equation.h"
#include "float.h"
#include <limits.h>
#include <math.h>
#include <assert.h>


//======================================================================
void equation_initialize(struct Equation* eq) {

    assert(eq != NULL);
    eq->a = NAN;
    eq->b = NAN;
    eq->c = NAN;
    eq->x1 = NAN;
    eq->x2 = NAN;
    eq->type = 0;
    eq->is_complex = 0;
    eq->root = 0;
}

//======================================================================
void equation_input(struct Equation* eq) {
    char answer = 0;
    
    assert(eq != NULL);
    while (!(isfinite(eq->a) && isfinite(eq->b) && isfinite(eq->c))) {
        printf("Введите коэффициенты квадратного уравнения ax^2+bx+c=0 в соответствующем порядке.\n Дробную часть отделите запятой. \n");
        scanf("%f %f %f", &(eq->a), &(eq->b), &(eq->c));
        fseek(stdin, 0, SEEK_END);
        if (!(isfinite(eq->a) && isfinite(eq->b) && isfinite(eq->c))) {
            fprintf(stderr, "\n\t\tWrong input\n\n");
            fflush(stdin);
        }
    }
    
    assert(isfinite(eq->a));
    assert(isfinite(eq->b));
    assert(isfinite(eq->c));
    
    assert(!(((eq->a) == 0) && ((eq->b) == 0) && ((eq->c) == 0)));
}

//======================================================================
void get_eq_type(struct Equation* eq) {
    assert(eq != NULL);
    
    if ((eq->b) == 0) {          // ax^2+c   или ax^2 или c=0(елси а=0)
        assert((eq->a) != 0);
        if ((eq->c) == 0)
            eq->type = WITHOUT_B_C;
        else
            eq->type = WITHOUT_B;

    }
    else if ((eq->c) == 0) {    // ax^2+bx=0    bx=0      
        if ((eq->a) == 0)
            eq->type = WITHOUT_A_C;
        else
            eq->type = WITHOUT_C;
    }
    else if ((eq->a) == 0) {
        eq->type = WITHOUT_A;
    }
    else
        eq->type = FULL;

}

//======================================================================
void print_eq_form(struct Equation* eq) {
    assert(eq != NULL);

    printf("\nВведённое уравнение: ");
 
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
        if((eq->c)>0)
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
    default:
        assert(0);
        break;
    }
}


//======================================================================
void solve_eq(struct Equation* eq) {
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
    assert(eq != NULL);
    float a = eq->a;
    float b = eq->b;
    float c = eq->c;
    float D = b * b - 4 * a * c;
    float x1 = 0.0;
    float x2 = 0.0;
    switch (eq->type)
    {
    case WITHOUT_A:
        eq->is_complex = REAL;
        eq->root = ONE_ROOT;
        eq->x1 = (-1.0 * c) / b;
        eq->x2 = EMPTY_R;
        break;
    case WITHOUT_A_C:
        eq->is_complex = REAL;
        eq->root = ONE_ROOT;
        eq->x1 = 0;
        eq->x2 = EMPTY_R;
        break;
    case WITHOUT_B:
        if (D>0) {
            eq->is_complex = REAL;
            eq->root = TWO_ROOTS;
            eq->x1 = sqrtf(fabs(c) / fabs(a));
            eq->x2 = -1.0 * sqrtf(fabs(c) / fabs(a));
        }
        else {
            eq->is_complex = COMPLEX;
            eq->root = TWO_COMP;
            eq->x1 = COMPLEX_R;
            eq->x2 = COMPLEX_R;
        }
        break;
    case WITHOUT_B_C:
        eq->is_complex = REAL;
        eq->root = ONE_ROOT;
        eq->x1 = 0;
        eq->x2 = EMPTY_R;
        break;
    case WITHOUT_C:
        eq->is_complex = REAL;
        eq->root = TWO_ROOTS;
        eq->x1 = 0;
        eq->x2 = (-1.0 * b) / a;
        break;
    case FULL:
        if (D > FLT_MIN) {
            eq->is_complex = REAL;
            eq->root = TWO_ROOTS;
            
            x1 = ((-1.0 * b) - sqrt(D)) / (2.0 * a);
            x2 = ((-1.0 * b) + sqrt(D)) / (2.0 * a);

            if (x1 < x2) {
                eq->x1 = x1;
                eq->x2 = x2;
            }
            else {
                eq->x1 = x2;
                eq->x2 = x1;
            }
        }
        else if (D < (-1.0* FLT_MIN) ) {
            eq->is_complex = COMPLEX;
            eq->root = TWO_COMP;
            eq->x1 = COMPLEX_R;
            eq->x2 = COMPLEX_R;
        }
        else {
            eq->is_complex = REAL;
            eq->root = ONE_ROOT;
            eq->x1 = (-1.0 * b) / (2.0 * a);
            eq->x2 = EMPTY_R;
        }
        break;
    default:
        assert(0);
        break;
    }
}

//======================================================================
void print_complex_solution(struct Equation* eq) {
    assert(eq != NULL);
    float D_sqrt = sqrtf(fabs((eq->b) * (eq->b) - 4.0 * (eq->a) * (eq->c)));

    switch (eq->type)
    {
    case WITHOUT_B:
        /*
            x = +-i*sqrt( |c|/|a| )
        */
        printf("\nУравнение имеет решения только в комплексных числах.\nОтвет: ");
        printf("x = +-%.2f*i",sqrtf(fabs(eq->c)/fabs(eq->a)));
        break;
    case FULL:
        /*
                    D<0 => x1 = ( -b - i*sqrt(|D|) )/2a
                           x2 = ( -b + i*sqrt(|D|) )/2a
        */
        printf("\nДискриминант меньше нуля.\nУравнение имеет решения только в комплексных числах.\nОтвет: ");
        printf("x = (%.2f - %.2f*i)/%.2f ; ", -1.0 * (eq->b), D_sqrt, (eq->a) * 2.0);
        printf("x = (%.2f + %.2f*i)/%.2f ; ", -1.0 * (eq->b), D_sqrt, (eq->a) * 2.0);
        break;
    default:
        assert(0);
        break;
    }
}

//======================================================================
void print_roots(struct Equation* eq) {
    assert(eq != NULL);
    if ((eq->is_complex) == COMPLEX)
        print_complex_solution(eq);
    else {
        switch (eq->root)
        {
        case ONE_ROOT:
            printf("\nОтвет: x = %.2f", eq->x1);
            break;
        case TWO_ROOTS:
            printf("\nОтвет: x = %.2f ; x = %.2f", eq->x1, eq->x2);
            break;
        default:
            break;
        }
    }
}

//======================================================================
void enter_equation(struct Equation* eq) {
    assert(eq != NULL);
    
    equation_input(eq);
    get_eq_type(eq);
    print_eq_form(eq);
}

//======================================================================
int want_again() {
    char y_or_n = 0;
    printf("\nХотите ввести еще одно уравнение? y/n: ");
    scanf("%c", &y_or_n);
    fseek(stdin, 0, SEEK_END);
    if ((y_or_n == 'y') || (y_or_n == 'Y')) {
        return 1;
    }
    else if ((y_or_n == 'n') || (y_or_n == 'N')) {
        return 0;
    }
    else {
        printf("\nВведите y , чтобы продолжить или n , чтобы прекратить выполнение программы");
        want_again();
    }
}
