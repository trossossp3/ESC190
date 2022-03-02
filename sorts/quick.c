#include "swap.c"
int partion(int arr[], int low, int high){
    //low being the first index
    //high is last index of arr

    int leftPivot = low-1; //index of value to left of pivot
    int pivot = arr[high];

    for(int i=low;i<high;i++){
        if(arr[i]<pivot){
            leftPivot++;
            swap(&arr[i],&arr[leftPivot]);
        }
    }

    swap(&arr[high], &arr[leftPivot+1]);
    return leftPivot+1;
}


void quick(int arr[], int low, int high)
{

    if (low < high)
    {
        int mid = partion(arr, low, high);
        quick(arr, low, mid - 1);
        quick(arr, mid + 1, high);
    }
}