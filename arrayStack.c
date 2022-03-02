#include <stdio.h>
#include <stdlib.h>
struct el{
    int value;
};

struct stack{
    int num_el;
    int max_el;
    struct el** cargo;
};

void push(struct stack* stackk, struct el* in){
    
    if(stackk->num_el == stackk->max_el){
        //not enough space for new shit
        stackk->max_el =  stackk->max_el*2;
        stackk->cargo =  (struct el**)realloc(stackk->cargo,(sizeof(struct el*) * stackk->max_el));
    }
    stackk->cargo[stackk->num_el] = in;
    stackk->num_el++;
    printf("element added\n");
}
void printEl(struct el* ele){
    printf("el has value %d\n", ele->value);
}
void pop(struct stack* stackk){
    printf("%i element freed\n", stackk->cargo[stackk->num_el-1]->value);
    stackk->num_el--;
    
    free(stackk->cargo[stackk->num_el]);
   
}
void peek(struct stack* stackk){
    printf("%i element at top\n", stackk->cargo[stackk->num_el-1]->value);
}
void freeCargo(struct stack* stackk){
    for(int i =0; i < stackk->num_el; i++){
        free(stackk->cargo[i]);
    }
}
int main(){
    struct stack* stackk = (struct stack*)malloc(sizeof(struct stack));
    stackk->num_el = 0;
 
    stackk-> max_el = 10;    
    stackk -> cargo = (struct el**)malloc(sizeof(struct el*) * stackk->max_el);
    
    struct el* first = (struct el*)(malloc(sizeof(struct el)));
    first->value = 69;

    struct el* sec = (struct el*)(malloc(sizeof(struct el)));
    sec->value = 420;
    
    push(stackk, first);
    printf("num elements %d\n", stackk->num_el);
    push(stackk, sec);
    peek(stackk);
    printf("num elements %d\n", stackk->num_el);
    // push(stackk, sec);
    // pop(stackk);
//    printf("num elements %d\n", stackk->num_el);

    peek(stackk);
    freeCargo(stackk);
 //   peek(stackk);
	free(stackk->cargo);
	free(stackk);


}
