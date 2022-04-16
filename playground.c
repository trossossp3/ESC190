#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
    char *text = "The test string is here";
    char *subtext = malloc(strlen(text));

    memcpy(subtext, &text[0], strlen(text) - 1);
    subtext[strlen(text) - 1] = '\0';
    printf("The original string is: %s\n", text);
    printf("Substring is: %s", subtext);

    return 0;
}