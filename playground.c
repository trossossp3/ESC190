#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char** temp = malloc(sizeof(char*)*3);
    temp[0] = malloc(2);
    temp[0] = "a\0";
    temp[1] = malloc(2);
    temp[1] = "b\0";
    temp[2] = malloc(2);
    temp[2]=  "c\0";
    int count = 0;
    for(int i = 0; strcmp("c", temp[i]) != 0;i++)
        count++;

    
    printf("%s", temp[0]);
    printf("%d", count);
}