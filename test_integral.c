#include <stdio.h>
#include "integral.h"
 
int main (void)
{
    
    printf("integral 2*x + 1  : %f\n", integral(0, 1, "2*x + 1"));
    printf("-----------------\n");

    printf("integral 3*x*x + 2*x + 2  : %f\n", integral(0, 1, "3*x*x + 2*x + 2"));
    printf("-----------------\n");


    // Unit Circle
    printf("integral (1-x**2)**0.5  : %f\n", integral(0, 1, "4 * (1-x**2)**0.5"));
    printf("-----------------\n");
    
 
    return 0;
}