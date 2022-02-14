#include "lab3.h"
#include <stdio.h>
//Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta){
    struct party_node* temp = (struct party_node*)malloc(sizeof(struct party_node));
    temp->item = item;
    temp->price = price;
    temp->ta = ta;

    temp->next = *head;
    *head = temp;
    return 0;

    // add the thing to check if word is "IDw\E"
}

//Remove the last item added
void remove_request(struct party_node **head){
    struct party_node* temp = *head;
    *head = (*head)->next;
    free(temp);


}

//Sort party item requests - in place?
void make_sorted(struct party_node **head){
    print_list(*head);
    struct party_node* curr =  NULL;
    struct party_node* prev =  NULL;
    int sort =0;

    do{
        curr = *head;
        sort = 0;
        while(curr->next !=NULL){
            if(curr->price < curr->next->price){
               
                if (curr == *head){ //if the current node is the first node
                    printf("hello");
                    struct party_node* temp =  NULL;
                    temp = curr->next;
                    *head = temp;
                    print_list(*head);
                    temp->next = curr;
                    // print_list(*head);
                    curr->next =temp->next;
                    
                   
                    sort =1;
                }
                
            }
            curr = curr->next;

        }
        prev = curr;
       
    }
     while(sort);

}

//Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
    //Add code here
}

//Print the current list - hope this is helpful!
void print_list(struct party_node *head){
    int count = 1;
    printf("The current list contains:\n");
    while(head!=NULL){
        printf("Item %d: %s, %.2lf, requested by %s\n",
            count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}