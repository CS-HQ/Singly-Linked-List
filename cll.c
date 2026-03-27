#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

// 1. Initialize
void create_list(struct node **head_ref) {
    *head_ref = NULL;
}

// Helper: Create Node
struct node* create_node(int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 2. Add at Front
void add_at_front(struct node **head_ref, int data) {
    struct node *newNode = create_node(data);
    if (*head_ref == NULL) {
        newNode->next = newNode; // Points to itself
        *head_ref = newNode;
        return;
    }
    
    // We must find the last node to update its 'next' to the new head
    struct node *temp = *head_ref;
    while (temp->next != *head_ref) {
        temp = temp->next;
    }
    
    newNode->next = *head_ref;
    temp->next = newNode; // Last node now points to new front
    *head_ref = newNode;   // Update head
}

// 3. Add at Last
void add_at_last(struct node **head_ref, int data) {
    struct node *newNode = create_node(data);
    if (*head_ref == NULL) {
        newNode->next = newNode;
        *head_ref = newNode;
        return;
    }
    
    struct node *temp = *head_ref;
    while (temp->next != *head_ref) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->next = *head_ref; // Link back to head
}

// 4. Add at Position
void add_at_pos(struct node **head_ref, int data, int pos) {
    if (pos == 1) {
        add_at_front(head_ref, data);
        return;
    }
    struct node *temp = *head_ref;
    for (int i = 1; i < pos - 1 && temp->next != *head_ref; i++) {
        temp = temp->next;
    }
    
    struct node *newNode = create_node(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

// 5. Display
void display(struct node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct node *temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(Head)\n");
}

// 6. Delete Front
void delete_front(struct node **head_ref) {
    if (*head_ref == NULL) return;
    
    struct node *temp = *head_ref;
    struct node *last = *head_ref;
    
    // If only one node
    if (temp->next == *head_ref) {
        free(temp);
        *head_ref = NULL;
        return;
    }
    
    // Find last node to update its link
    while (last->next != *head_ref) {
        last = last->next;
    }
    
    *head_ref = (*head_ref)->next;
    last->next = *head_ref;
    free(temp);
}

// 7. Delete Last
void delete_last(struct node **head_ref) {
    if (*head_ref == NULL) return;
    
    struct node *temp = *head_ref;
    if (temp->next == *head_ref) {
        free(temp);
        *head_ref = NULL;
        return;
    }
    
    struct node *prev = NULL;
    while (temp->next != *head_ref) {
        prev = temp;
        temp = temp->next;
    }
    
    prev->next = *head_ref;
    free(temp);
}

// 8. Delete at Position
void delete_at_pos(struct node **head_ref, int pos) {
    if (*head_ref == NULL) return;
    if (pos == 1) {
        delete_front(head_ref);
        return;
    }
    
    struct node *temp = *head_ref;
    struct node *prev = NULL;
    for (int i = 1; i < pos && temp->next != *head_ref; i++) {
        prev = temp;
        temp = temp->next;
    }
    
    prev->next = temp->next;
    free(temp);
}

// 9. Free List
void free_list(struct node **head_ref) {
    if (*head_ref == NULL) return;
    struct node *current = *head_ref;
    struct node *next_node;
    
    // Break the circle to use standard free logic
    struct node *last = *head_ref;
    while (last->next != *head_ref) last = last->next;
    last->next = NULL; 
    
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *head_ref = NULL;
    printf("Circular list memory freed.\n");
}

int main() {
    struct node *head;
    create_list(&head);

    add_at_front(&head, 10);
    add_at_last(&head, 30);
    add_at_pos(&head, 20, 2); // 10 -> 20 -> 30 -> (Head)
    display(head);

    delete_at_pos(&head, 2);
    display(head);

    free_list(&head);
    return 0;
}