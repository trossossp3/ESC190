#include "swap.c"


void bubble(int arr[], int size){
    int swaped = 0;
    for(int i =0; i <size-1;i++){
        for(int j=0; j<size-1-i;j++){
            if(arr[j] > arr[j+1]){
                swaped = 1;
                swap(&arr[j], &arr[j+1]);
            }
        }
        if(swaped == 0){
            return;
        }
    }
}