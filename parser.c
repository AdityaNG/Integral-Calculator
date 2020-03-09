#include <string.h>
#include <math.h>
#include "expr.h"

#include "parser_helper.c"

float parseAt(char *s1, float x) {
    char s[4096] = "x=";
    char num[25];
    ftoa(x, num, 9);
    //printf("num : %s\n", num);

    strcat(s, num);
    strcat(s,",");
    strcat(s, s1);
    //printf("Converting : %s\n", s);
    //char *res = replaceAll(s, "x", num);
    //printf("Converted : %s\n", res);

    struct expr_var_list vars = {0};
    struct expr *e = expr_create(s, strlen(s), &vars, user_funcs);
    if (e == NULL) {
        printf("FAIL: %s returned NULL\n", s);
        return 0;
    }

    float result = expr_eval(e);

    char *p = (char *)malloc(strlen(s) + 1);
    strncpy(p, s, strlen(s) + 1);
    for (char *it = p; *it; it++) {
        if (*it == '\n') {
        *it = '\\';
        }
    }

    //printf("Res %f\n", result);
    expr_destroy(e, &vars);
    free(p);
    return result;
}

// Reverses a string 'str' of length 'len' 
void reverse(char* str, int len) { 
    //printf("%s", str);
    int i = 0, j = len - 1, temp; 
    while (i < j) { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; 
        j--; 
    } 
} 

// Converts a given integer x to string str[].  
// d is the number of digits required in the output.  
// If d is more than the number of digits in x,  
// then 0s are added at the beginning. 
int intToStr(int x, char *str, int d) {
    //printf("%s", str);
    if (x==0) {
        str[0] = '0';
        return 1;
    }

    int i = 0; 
    while (x) { 
        str[i++] = (x % 10) + '0'; 
        x = x / 10; 
    }
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
  
    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
} 

// Converts a floating-point/double number to a string. 
void ftoa(float n, char* res, int afterpoint) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
  
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    int i = intToStr(ipart, res, 0); 
  
    // check for display option after point 
    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter  
        // is needed to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 
  
        intToStr((int)fpart, res + i + 1, afterpoint); 
    } 
} 
  

char *replaceAll(char *str, char *orig, char *rep) {
    static char buffer[4096];
    char *p;
    int i=0;

    while(str[i]){
        if (!(p=strstr(str+i,orig)))  return str;
        strncpy(buffer+strlen(buffer),str+i,(p-str)-i);
        buffer[p-str] = '\0';
        strcat(buffer,rep);
        //printf("STR:%s\n",buffer);
        i=(p-str)+strlen(orig);
    }

    return buffer;
}