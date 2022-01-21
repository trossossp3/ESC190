#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
double split_bill(double base_amount , double tax_rate , double tip_rate , int num_people){
    double tax_total=  base_amount + tax_rate*base_amount;
    double tip_total = tax_total + tax_total*tip_rate;
    double total = round(tip_total*100)/100;
    double per_person =  round(total/num_people *100)/100;
    printf("%f\n", per_person *num_people);
    printf("%f\n", tip_total);
    if (per_person * num_people < tip_total){
        per_person +=0.01;
    }
    
    return per_person;
}


double adjust_price(double original_price) {
    double adjusted_price = 10 *sqrt(original_price);
    return adjusted_price;
}

int sandy_eats(char menu_item []){
   
    int count = 0;
    for (int i =0; i<strlen(menu_item); i++){
        menu_item[i] = tolower(menu_item[i]);
        if(menu_item[i]!=' '){
            count++;
        }
    }
    if(count%2!=0){
        return 0;
    }
    char *j;
    char *k;
    char *l;
    char *fish;
    j = strchr(menu_item, 'j'); //returns pointer to first letter in string or null
    k = strchr(menu_item, 'k');
    l = strchr(menu_item, 'l');
    fish = strstr(menu_item, "fish");
   
    if(j == NULL && k == NULL && l==NULL && fish == NULL){
        return 1;
    }else{
        return 0;
    }

}

void imagine_fish(char thing []){
    strcat(thing, "fish");
}