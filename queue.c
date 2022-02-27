#include <stdio.h>
#include <stdlib.h>
struct node{
    int value;
    struct node* next;
};


int peek(struct node **head){
    if(*head == NULL){
        return 0;
    }
    return (*head)->value;
    
    
}

int dequeue(struct node **head, struct node **rear){
    if(*head ==NULL){
        return 0;
    }

    struct node *temp = *head;
    *head = temp->next;
    if(*head == NULL){
        *rear = NULL;
    }

    free(temp);
    return 1;
}
int enqueue(struct node **head, struct node **rear, int value){
   
    
    
    struct node* new = (struct node*)(malloc(sizeof(struct node)));
    new->value = value;
    new->next = NULL;
  
    if(*head == NULL){
        
        *head = new;
        *rear = new;
        
    }else{
        
        (*rear)->next = new;
        *rear = new;
    }
    return 1;  

}

