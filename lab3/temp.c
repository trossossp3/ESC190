/ Trim list to fit the budget
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
            free(temp->item);
            free(temp->ta);
            free(temp);
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