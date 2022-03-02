#include <stdio.h>
typedef struct el{
    int value;
}el;

void change(int arr[]){
    arr[2] = 69;
}
int main()

{
    int arr[] = {1,2,34};
    printf("%i", arr[2]);
    change(arr);
    printf("%i", arr[2]);
}

