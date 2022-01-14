#include <stdio.h>
#include <string.h>
int main(){
    char str[] = "cat in hat";
    char subStr[] = "an";
    printf("%s\n",str);
    char *point;
    point = strstr(str,"cat");
    printf("The substring is: %s\n", point);
    if(point == NULL){
        printf("Hello");
    }
    return 0;
}