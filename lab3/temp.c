#include "lab3.h"

// Construct Node
struct party_node* construct_node(char *item, double price, char *ta) {
    /// Construct new node
    struct party_node* new = (struct party_node *)malloc(sizeof(struct party_node));

    // Acquire string lengths
    int item_len = 0;
    int ta_len = 0;
    while(*(item+item_len) != '\0') { item_len++; }
    while(*(ta+ta_len) != '\0') { ta_len++; }

    // Allocate memory values
    new->item = (char *)malloc((item_len + 1)*sizeof(char)); // Space for '\0'
    new->ta = (char *)malloc((ta_len + 1)*sizeof(char)); // Space for '\0'

    //Assign values
    for(int i = 0; i < item_len+1; i++) { new->item[i] = item[i]; }
    for(int i = 0; i < ta_len+1; i++) { new->ta[i] = ta[i]; }
    new->price = price;
    new->next = NULL;

    return new;
}

// Check if string is "IDE"
int is_IDE(char *item) {
    // Check if it's an IDE
    char ide[4] = "IDE\0";
    int ide_len = 4;
    int equal = 1;
    int iter = 0;
    while(iter < ide_len && (iter > 0 || item[iter-1] == '\0')) {
        if(ide[iter] != item[iter]) { equal = 0; } 
        iter++;
    }
    return equal;
}

// Check if a list is sorted in decreasing price
int check_sorted(struct party_node *head) {
    int prev_price = head->price;
    struct party_node* beyond = head->next;
    while(beyond != NULL) {
        if(beyond->price > prev_price) { return 0; }
        prev_price = beyond->price;
        beyond = beyond->next;
    }

    return 1;
}

//Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta){
    if(is_IDE(item) == 1) {return -1;}

    // Construct node
    struct party_node* this = construct_node(item, price, ta);

    // Set to head
    if(*head == NULL) { *head = this; }
    else { 
        this->next = *head;
        *head = this;
    }

    // Allocated memory
    return 0;
}

//Remove the last item added
void remove_request(struct party_node **head){
    struct party_node* this = *head;
    if(this == NULL) { return; }

    // Free the data fields and set the new head
    free(this->item);
    free(this->ta);
    *head = this->next;
    free(this);
}


// Swap two items in the list
void swap_elements(struct party_node **head, int ind_a, int ind_b) {
    if(ind_a == ind_b) { return; }

    struct party_node* node_a = NULL;
    struct party_node* node_b = NULL;
    struct party_node* prev_a = NULL;
    struct party_node* prev_b = NULL;

    struct party_node* curr;
    int count;

    // Iterate through to find a
    node_a = *head;
    count = 0;
    while(node_a != NULL && count < ind_a) {
        prev_a = node_a;
        node_a = node_a->next;
        count++;
    }

    // Iterate through to find b
    node_b = *head;
    count = 0;
    while(node_b != NULL && count < ind_b) {
        prev_b = node_b;
        node_b = node_b->next;
        count++;
    }


    if(prev_a == NULL) { *head = node_b; }
    else { prev_a->next = node_b; }
    if(prev_b == NULL) { *head = node_a; }
    else { prev_b->next = node_a; }

    struct party_node* after_b = node_b->next;
    (*node_b).next = node_a->next;
    node_a->next = after_b;    
    
    return;
}

//Sort party item requests - in place?
struct party_node** insertion_sort_pass(struct party_node **head){
    // Insertion sort
    int lead_ind = 0;
    struct party_node* lead = *head;

    while(lead->next != NULL) {
        int max_ind = lead_ind;
        struct party_node* max = lead;
        struct party_node* curr = lead->next;
        int count = lead_ind+1;

        while(curr != NULL) {
            if(curr->price > max->price) {
                max = curr;
                max_ind = count;
            }
            count++;
            curr = curr->next;
        }
        
        if(max_ind != lead_ind) {
            swap_elements(head, lead_ind, max_ind);
            return head;
        } else {
            lead = lead->next;
            lead_ind++;
        }
    }

    return head;
}

void make_sorted(struct party_node** head) {
    struct party_node* this = *head;
    int num_elem = 0;
    while(this != NULL) { this = this->next; num_elem++; }
    
    struct party_node* lead = *head;
    int lead_ind = 0;
    while(lead->next != NULL) {

        // Execute insertion sort passes
        int max_ind = lead_ind;
        struct party_node* max = lead;
        int curr_ind = lead_ind+1;
        struct party_node* curr = lead->next;

        while(curr != NULL) {
            if(curr->price > max->price) {
                max_ind = curr_ind;
                max = curr;
            }
            curr_ind++;
            curr = curr->next;
        }
        // In case it swaps directly beside, this will make sure the node advances along the list
        if(max_ind != lead_ind+1) { lead = lead->next; }
        swap_elements(head, max_ind, lead_ind);
        lead_ind++;
    }
}



void remove_in_place(struct party_node* to_remove) {
    free(to_remove->item);
    free(to_remove->ta);
    free(to_remove);
}

//Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
    struct party_node* curr = *head;
    struct party_node* curr_prev = NULL;
    while(budget > 0 && curr != NULL) {
        if(curr->price <= budget) {
            budget -= curr->price;
            curr_prev = curr;
            curr = curr->next;
        } else {
            struct party_node* this = curr;

            if(curr_prev == NULL) {
                curr = curr->next;
                *head = curr;
            }
            else {
                curr = curr->next;
                curr_prev->next = curr;
            }
            
            remove_in_place(this);
        }
    }

    return budget;
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