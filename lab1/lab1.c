#include <math.h>
#include <string.h>
double split_bill(double base_amount , double tax_rate , double tip_rate , int num_people){
    double total_pay =  base_amount + tax_rate*base_amount + tip_rate*base_amount;
    return total_pay/num_people;
}


double adjust_price(double original_price) {
    double adjusted_price = 10 *sqrt(original_price);
    return adjusted_price;
}

int sandy_eats(char menu_item []){
    int length = strlen(menu_item);
    if(length%2!=0){
        return 0;
    }
    char *j;
    char *k;
    char *l;
    char *fish;
    j = strchr(menu_item, 'j');
    // k = strstr(menu_item, "k");
    // l = strstr(menu_item, "l");
    // fish = strstr(menu_item,"fish");
    if(j == NULL){
        return 1;
    }else{
        return 0;
    }

}