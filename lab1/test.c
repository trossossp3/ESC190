#include <stdio.h>
#include <string.h>
#include <math.h>
int main(){
    char test[] = " a  s";
    printf("%d", strlen(test));
    int count = 0;
    for (int i =0; i<strlen(test); i++){
        if(test[i]!=' '){
            count++;
        }
    }

    printf("%i", count);
}