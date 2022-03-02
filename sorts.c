#include <stdio.h>

void insertion(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int j = i - 1;
        int key = arr[i];

        while (arr[j] > key && j >= 0)
        {
            arr[j + 1] = arr[j];

            --j;
        }
        arr[j + 1] = key;
    }
}
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void selection(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {

        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        swap(&(arr[i]), &(arr[min]));
    }
}

void bubble(int arr[], int size)
{
    int swaps = 0;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j + 1] < arr[j])
            {
                swaps = 1;
                swap(&(arr[j + 1]), &(arr[j]));
            }
        }
        if (swaps == 0)
        {
            break;
        }
    }
}
void merge(int result[], int arr1[], int arr2[], int n1, int n2)
{
    /*
    Merge two arrays, <arr1> and <arr2>, that are both
    sorted in ascending order. Store the resulting
    sorted array in <result>.
    <arr1> and <arr2> have lengths <n1> and <n2>,
    respectively.
    <result> has length <n1> + <n2>
    */
    // i1 is a counter for arr1
    // i2 is a counter for arr2
    int i1 = 0, i2 = 0;
    int i = 0; // counter for result
    while (i1 < n1 && i2 < n2)
    {
        if (arr1[i1] <= arr2[i2])
        {
            result[i++] = arr1[i1++];
        }
        else
        {
            result[i++] = arr2[i2++];
        }
    }
    // pick off the remaining array
    while (i1 < n1)
    {
        result[i++] = arr1[i1++];
    }
    while (i2 < n2)
    {
        result[i++] = arr2[i2++];
    }
}
void mergesort(int sorted[], int unsorted[], int n)
{
    /*
    Recursive implementation of Mergesort.
    Note: this implementation is _not_ in place.
    */
    // determine the lengths of the left and
    // right halves of the unsorted array
    int n_l = n / 2;
    int n_r = n - n_l;
    // create arrays to store the left and right
    // partititions of the unsorted array
    int l[n_l];
    int r[n_r];
    // copy over arrays into l and r
    for (int i = 0; i < n_l; i++)
    {
        l[i] = unsorted[i];
    }
    for (int j = 0; j < n_r; j++)
    {
        r[j] = unsorted[n_l + j];
    }
    // create a new arrays to store the sorted left and
    // right subpartitions
    int sorted_l[n_l];
    int sorted_r[n_r];
    // first, check if we have degenerate cases
    // where there is no sorting needed to be done
    if (n_l == 0)
    {
        sorted[0] = r[0];
    }
    else if (n_r == 0)
    {
        sorted[0] = l[0];
    }
    else if (n_l == 1 && n_r == 1)
    {
        // merge them, they are sorted
        merge(sorted, l, r, n_l, n_r);
    }
    else
    {
        // recursive call to further subdivide
        // into left and right
        mergesort(sorted_l, l, n_l);
        mergesort(sorted_r, r, n_r);
        // now have l and r sorted into sorted_l and sorted_r
        // merge them into our final result
        merge(sorted, sorted_l, sorted_r, n_l, n_r);
    }
}

int partion(int arr[], int low, int high)
{
    int pivot = arr[high]; // right side quicksort

    int i = low - 1; // pointer for element to the left of correct pivot position

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]); // when there is an element smaller than the pivot incremenet the pointer to element to left of pivot and swap the smaller element with wtever is beside the pivot
        }
    }
    swap(&arr[high], &arr[i + 1]);
    return i + 1;
}

void quicksort(int arr[], int low, int high)
{

    if (low < high)
    {
        int mid = partion(arr, low, high);
        quicksort(arr, low, mid - 1);
        quicksort(arr, mid + 1, high);
    }
}
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quicksort(arr, 0, n - 1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}