#include <stdio.h>
#include <stdlib.h>

// Define the linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new list node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to extract a node from the linked list by position
Node* extractNode(Node** head, int position) {
    if (head == NULL || *head == NULL) {
        return NULL; // Empty list, nothing to extract
    }

    Node* current = *head;
    Node* prev = NULL;

    // Special case for the head
    if (position == 0) {
        *head = current->next;
        return current;
    }

    // Locate the node at the given position
    for (int i = 0; current != NULL && i < position; ++i) {
        prev = current;
        current = current->next;
    }

    // If position is more than number of nodes
    if (current == NULL) {
        return NULL;
    }

    // Unlink the node from the linked list
    prev->next = current->next;

    return current;
}

// Function to free an extracted node
void freeNode(Node* node) {
    free(node);
}

/* Example usage of the function:
int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    
    // Extract the node at position 1 (which has data '2')
    Node* extracted = extractNode(&head, 1);
    if (extracted) {
        // ... use the extracted data ...

        // Once done, free the extracted node
        freeNode(extracted);
    }

    // Remember to free the rest of the list
    while (head) {
        Node* to_free = head;
        head = head->next;
        freeNode(to_free);
    }

    return 0;
}
*/