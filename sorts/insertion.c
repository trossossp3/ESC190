#include <stdlib.h>
#include <stdio.h>


void insertion(int arr[], int size){

    for(int i =1; i <size;i++){ // i is the boundry index
        int key = arr[i];
        int j = i-1;

        while(arr[j]>key && j>=0){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key; //while loop will stop when it finds an element less than key so we want to put the key infront of that element thus [j+1]
    }
}