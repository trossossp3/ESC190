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
    temp->item = item;
    temp->price = price;
    temp->ta = ta;

    temp->next = *head;
    *head = temp;
    return 0;

    // add the thing to check if word is "IDw\E"
}

// Remove the last item added
void remove_request(struct party_node **head)
{
    struct party_node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Sort party item requests - in place?
void make_sorted(struct party_node **head)
{
    int swapped;
    struct party_node *curr;

    if (*head == NULL)
        return;

    do
    {
        swapped = 0;
        curr = *head;

        while (curr->next != NULL)
        {
            if (curr->price < curr->next->price)
            {

                swap(curr, curr->next);
                swapped = 1;
            }
            curr = curr->next;
        }

    } while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(struct party_node *a, struct party_node *b)
{
    double temp = a->price;
    a->price = b->price;
    b->price = temp;

    char *temp2 = a->item;
    a->item = b->item;
    b->item = temp2;

    char *temp3 = a->ta;
    a->ta = b->ta;
    b->ta = temp3;
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

    return budget-cost;
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