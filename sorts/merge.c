void merge(int result[], int arr1[], int arr2[], int n1, int n2){
    int i = 0;
    int j=0;
    int r=0;
    while(i<n1 &&j<n2){
        if(arr1[i]<arr2[j]){
            result[r] = arr1[i];
            i++;
            r++;
        }else{
            result[r] = arr2[j];
            j++;
            r++;
        }
    }

    while(i<n1){
        result[r++] = arr1[i++];
    }
    while(j<n2){
        result[r++] = arr2[j];
    }


}

void mergesort(int sorted[], int unsorted[], int len){
    /*
    unsorted is the unsorted data with length len
    */
    int nl = len/2;
    int nr = len -nl;

    int larr[nl];
    int rarr[nr];

    for(int i =0;i<nl;i++){
        larr[i] = unsorted[i];
    }
    for(int i =0; i<nr;i++){
        rarr[i] = unsorted[i+nl];
    }
    int lsort[nl];
    int rsort[nr];

    if(nr ==0){
        sorted[0] = larr[0];
    }else if(nl==0){
        sorted[0] = rarr[0];
    }else if(nl ==1 && nr==1){
        merge(sorted, larr, rarr, nl,nr);
    }else{
        mergesort(lsort,larr,nl);
        mergesort(rsort, rarr, nr);

        merge(sorted, lsort,rsort,nl,nr);
    }
}