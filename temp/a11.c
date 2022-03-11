#include <stdio.h>

int main(){
    FILE *fp = fopen("text.txt", "r");
    int array[5] = { 0 };
    int i;
   
    for (i = 0; i < 5; i++) {
        fscanf(fp, "%d", &array[i]);
        printf("%d", array[i]);
    }

    fclose(fp);
    return 0;
}