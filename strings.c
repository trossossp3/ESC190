#include <string.h>
#include <stdio.h>

int main(){
    char str1[1000] = "HELLO";
    int i =0;
    for (i = 0; str1[i] != '\0'; ++i);
    printf("%d\n", i);
    char str2[] = "fella";
    char str3[100];
    strcat(str1, str2);
   
    strcpy(str3, str1);
    printf("%s\n", str3);
  
   
    printf("%s\n", str1);
    printf("%d\n",strlen(str1));
  
    printf("%c",str1[3]);
    //strcpr
    //strcmp
    //strlen
    //strcat
}