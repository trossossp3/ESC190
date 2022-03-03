#include <stdio.h>
typedef struct el{
    int value;
}el;

void change(int arr[]){
    arr[2] = 69;
}

void change1(int *in){
    int temp = 10;
    *in = 10;
}
int main()
{
    int q = 5;
    int* cat = &q;
    change1(cat);
    printf("%d\n", *cat);

    int arr[] = {1,2,3,4};
    change(arr);
    printf("%d", arr[2]);




}

