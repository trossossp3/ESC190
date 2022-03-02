#include <stdlib.h>
#include <stdio.h>
/*

make a queue struct that keeps track of the amout of elements added and removed and just free shit when u need
*/

typedef struct el{
    int value;
}el;

typedef struct Queue{
    int max_els;
    int num_els;
    int num_del;
    el** cargo;
}Queue;

void enqueue(Queue* q, el* e){
    int availabilty = (q->max_els)-(q->num_del)-(q->num_els);
    if(availabilty<=0){
        //make the queue bigger
        q->cargo = (el**)realloc(q->cargo, sizeof(el*)*q->max_els*2);
        q->max_els = q->max_els*2;
    }
    q->cargo[q->num_del+q->num_els] = e;
    
    printf("%d element added\n", q->cargo[q->num_del+q->num_els]->value);
    q->num_els++;
}

void dequeue(Queue* q){
    printf("dequeued element %d\n", q->cargo[q->num_del]->value);
    free(q->cargo[q->num_del]);
    q->num_del++;
    q->num_els--;
}
void freeEls(Queue* q){

    for(int i = 0; i<q->num_els;i++){
        free(q->cargo[i+q->num_del]);
    }
}
int main(){
    int max =10;
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->max_els=10;
    q->num_del=0;
    q->num_els=0;
    q->cargo = (el**)malloc(sizeof(el*)*q->max_els);

    // printf("happy");

    el* fir = (el*)malloc(sizeof(el*));
    fir->value =10;

    el* sec = (el*)malloc(sizeof(el*));
    sec->value =100;

    enqueue(q, fir);
    enqueue(q, sec);
    // dequeue(q);
    freeEls(q);
    free(q->cargo);
    free(q);
    printf("happy");


}