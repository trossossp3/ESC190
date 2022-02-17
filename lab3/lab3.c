#include "lab3.h"
#include <stdio.h>
// Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta)
{
    if (*item == 'I' && *(item + 1) == 'D' && *(item + 2) == 'E' && *(item + 3) == '\0')
    {
        return -1;
    }

    struct party_node *temp = (struct party_node *)malloc(sizeof(struct party_node));
    int len_item = 0;
    int len_ta = 0;

    while (*(item + len_item) != '\0')
    {
        len_item++;
    }
    while (*(item + len_ta) != '\0')
    {
        len_ta++;
    }
    temp->ta = (char *)malloc(sizeof(char) * (len_ta + 1));
    temp->item = (char *)malloc(sizeof(char) * (len_item + 1));

    for (int i = 0; i < len_item + 1; i++)
    {
        temp->item[i] = item[i];
    }
    for (int i = 0; i < len_ta + 1; i++)
    {
        temp->ta[i] = ta[i];
    }

    temp->price = price;
    temp->next = *head;
    *head = temp;
    return 0;

    // add the thing to check if word is "IDw\E"
}

// Remove the last item added
void remove_request(struct party_node **head)
{
    struct party_node *temp = *head;

    free(temp->item);
    free(temp->ta);
    *head = (temp)->next;
    free(temp);
}

// Sort party item requests - in place?
void make_sorted(struct party_node **head)
{printf("\nsorting\n");
    int swapped;
    struct party_node *a;
    struct party_node *b;
    struct party_node *prev_a;
    struct party_node *prev_b;

    if (*head == NULL)
        return;

    do
    {
        // printf("hello");
        swapped = 0;
        a = *head;
        b = a->next;
        prev_a = NULL;
        prev_b = a;
        
        while (b != NULL && a!=NULL)
        {
            printf("\na price:%f\n", a->price);
        printf("b price%f\n", b->price);
            if (a->price < b->price)
            {
                
              swap(head,a,b,prev_a,prev_b);
              printf("\njust did swap\n");
                printf("a price:%f\n", a->price);
                printf("b price%f\n", b->price);
                swapped = 1;
            }
            prev_a = a;
            a = a->next;
            b = b->next;
        }

    } while (swapped);
}

void swap(struct party_node **head, struct party_node *a, struct party_node *b, struct party_node *a_prev, struct party_node *b_prev)
{

    if (a_prev == NULL)
    {
        *head = b;
    }
    else
    {
        a_prev->next = b;
    }
    if (b == NULL)
    {
        *head = a;
    }
    else
    {
        b_prev->next = a;
    }

    struct party_node *temp = b->next;
    a->next = temp;
    // printf("deep pain");
    // a_prev->next = b;
    // printf("on the edge");
    b->next = a;
    return;
}

// Trim list to fit the budget
double finalize_list(struct party_node **head, double budget)
{

    struct party_node *curr = *head;
    struct party_node *prev = NULL;
    double cost = 0;
    while (curr != NULL)
    {
        if (cost + curr->price > budget)
        {
            if (prev == NULL)
            { // if we are looking at first index
                *head = (*head)->next;
            }
            else
            {
                prev->next = curr->next;
            }
        }
        else
        {
            cost += curr->price;
            prev = curr;
        }
        curr = curr->next;
    }

    return budget - cost;
}

// Print the current list - hope this is helpful!
void print_list(struct party_node *head)
{
    int count = 1;
    printf("The current list contains:\n");
    while (head != NULL)
    {
        printf("Item %d: %s, %.2lf, requested by %s\n",
               count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}