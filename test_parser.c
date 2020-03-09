#include <stdio.h>
#include "parser.h"
 
int main (void)
{

    /*
    char i[25];
    intToStr(10, i, 2);
    printf("intToStr : %s\n", i);

    char t[25];
    reverse(t, 5);
    printf("Rev : %s\n", t);*/
    
    printf("%f\n", parseAt("x*x", 0.5));

    printf("%f\n", parseAt("x**0.5", 4));
 
    return 0;
}