#include "math.h"
#include "parser.h"

float integral(float a, float b, char *exp) {
    if (a==b)
        return 0;
    
    int n=1;

    float res = (b-a)*parseAt(exp, (a+b)/2), old_res = 0;
    printf("Iteration : %d ; \t res = %f \n", n, res);
    n++;

    while (fabs(res-old_res)>0.0000001) {
        old_res = res;
        res=0;
        for (int i=0; i<=n; i++) {
            res += (b-a)/n * parseAt(exp, i*(b-a)/n + a);
        }
        if (n%100==0)
            printf("Iteration : %d ; \t res = %f \n", n, res);
        n++;
    }

    return res;
}