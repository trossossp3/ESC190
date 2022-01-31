#include <stdlib.h>
#include <stdio.h>

int main()
{

    int *ptr = calloc(2, sizeof(int));
    *(ptr + 1) = 2;
    *(ptr) = 3;
    int l = 2;
    append(&ptr,&l,98);
    printf("%d",ptr[2]);
    printf("%d",l);
}
void append(int **x, int *n, int val)
{
    *x = (int *)realloc(*x, (*n + 1) * sizeof(int));
	*(*x + *n) = val;
    *n = *n+1;
	

}