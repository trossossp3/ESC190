#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

void addIndex(node **head, int add, int index)
{
    node *cur = *head;
    node *prev = NULL;
    node *new = (node *)malloc(sizeof(node));
    new->value = add;
    
    if (index ==0)
    {
        printf("HELLO");
        new->next = *head;
        *head = new;
        return;
    }
    int i;
    for (i = 0; i < index; i++)
    {
        prev = cur;
        cur = cur->next;
    }

    prev->next = new;
    new->next = cur;
}
int main()
{
    node *head = NULL;
    addIndex(&head, 40,0);
    addIndex(&head, 50,1)
    addIndex(&head, 40,2);
    addIndex(&head, 50,3);
    printf("HELLO\n");
    node *cur = head;
    while(cur!=NULL){
        printf("%d\n",(cur)->value);
        node* temp;
        temp = cur;

        cur= cur->next;
        free(temp);
    }
}