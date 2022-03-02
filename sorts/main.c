#include <stdio.h>
// #include "insertion.c"
#include "quick.c"
// #include "selection.c"
// #include "bubble.c"
#include "merge.c"

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(){
    int arr[] = {5,4,3,2,1};
    int size = sizeof(arr)/sizeof(arr[0]);
    int sorted[size];
    // insertion(arr, size);
    // mergesort(sorted, arr, size);
    quick(arr,0,size-1);
    printArray(arr, size);
}

