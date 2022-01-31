#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *p = (int *)malloc(sizeof(int)); //returns a pointer the the memory block created, take in the size of memory block
    fprintf(stdout, "Value stored at address %p: %d\n", p, *p);
    *p = 1;
    fprintf(stdout, "Value stored at address %p: %d\n", p, *p);
    free(p);
    fprintf(stdout, "Value stored at address %p: %d\n", p, *p); //unexpected behaviour 
    return 0;
}