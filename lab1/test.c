#include <stdio.h>
#include <string.h>
#include <math.h>
int main(){
    double x = 56.123;
    double rounded = round(x*100)/100;
    printf("%f", rounded);  
    return 0;
}