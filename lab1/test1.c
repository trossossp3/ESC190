#include <stdio.h> //need this to use the printf () function
#include <math.h>
#include "lab1.c" //need this to link our Lab 1 functions
#include "lab1.h"
int main()
{
    // Testing Part 1
    
    double test_p1 = split_bill(50.02, 0.13, 0.15, 2);
    printf("The split will be: $%.2f.\n", (test_p1));
    // $32 .50
    //Add more tests here ...

    // Testing Part 2
    double test_p2 = adjust_price(25.00);
    printf("The adjusted price is: $%.2f.\n", test_p2);
    // Should be $50 .00

    // Testing Part 3
    char test_food[10] = "a";
    char test[20] = "hi";

    int test_p3 = sandy_eats(test_food);
    if (test_p3 == 0)
    {
        printf("Sandy would NOT eat0 '%s '.\n", test_food);
    }
    else
    {
        printf("Sandy would eat '%s '.\n", test_food);
    }
    // Sandy would eat ‘Three Cheese Pizza ’.

    // Testing Part 4
    char test_p4[30] = "zebra";
    imagine_fish(test_p4);
    printf("Just imagine , a %s!\n", test_p4);
    // Just imagine , a zebrafish!
    return 0;
}