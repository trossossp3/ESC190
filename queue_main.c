#include "queue.c"
#include <stdio.h>

int main(){
    struct node *head = NULL;
    struct node *rear =NULL;

  

    enqueue(&head,&rear,10);
    // printf("%i", head->value);
    int x =peek(&head);
    printf("%d\n",x);
    enqueue(&head,&rear,100);
    dequeue(&head,&rear);
    int y =peek(&head);
    printf("%d",y);
}