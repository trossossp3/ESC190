#include "linkedlist.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
int main(){
    struct node *head = NULL;
    head = insert_node(head,1);
    printf("%d", head->data);
    return 0;
}

struct node* insert_node(struct node *head, int value){
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data=value;
    new_node->next=head;
    head=new_node;
    return head;
}
int search_list(struct node *head, int value){
    while(head!=NULL){
        if (head->data == value){
            return 1;
        }
        head=head->next;
    }
    return 0;
}

struct node* delete_node(struct node *head, int value){
    struct node *curr = head;
    struct node *prev = NULL;
    while (curr != NULL && curr->data!=value){
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL){
        return head;
    }else if (prev == NULL){
        head = head->next;
    }else{
        prev->next = curr->next;
    }
    free(curr);
    return head;
}