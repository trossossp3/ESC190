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
    temp->ta = (char *)malloc(sizeof(char) * (len_ta+1));
    temp->item = (char *)malloc(sizeof(char) * (len_item+1));

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
    if (*head == NULL)
    {
        return;
    }
    struct party_node *temp = *head;

    free(temp->item);
    free(temp->ta);
    *head = (temp)->next;
    free(temp);
    return;
}

// Sort party item requests - in place?
int getCount(struct party_node **head)
{
    int count = 0;
    struct party_node *curr = *head;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}
struct party_node *swap(struct party_node *ptr1, struct party_node *ptr2)
{
    struct party_node *tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}
void make_sorted(struct party_node **head)
{
    struct party_node **h;
    int i, j, swapped;
    int count = getCount(head);
    for (i = 0; i < count; i++)
    {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++)
        {

            struct party_node *p1 = *h;
            struct party_node *p2 = p1->next;

            if (p1->price < p2->price)
            {
                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &((*h)->next);
        }
        if (swapped == 0)
            break;
    }
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
            struct party_node *temp = curr;
            if (prev == NULL)
            { // if we are looking at first index
                *head = (*head)->next;
            }
            else
            {
                prev->next = curr->next;
            }
            curr = curr->next;
            free(temp->item);
            free(temp->ta);
            free(temp);
        }
        else
        {
            cost += curr->price;
            prev = curr;
            curr = curr->next;
        }

        
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