#include <stdio.h>
#include <stdlib.h>

// Define the Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = value;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to append a node to the list
void append(Node** head, int value) {
    Node* new_node = createNode(value);
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}

// Function to extract a sublist from the linked list
Node* extractSublist(Node* head, int start, int length) {
    Node* current = head;
    Node* sublistHead = NULL;
    Node* sublistTail = NULL;
    int index = 0;

    while (current != NULL && index < start + length) {
        if (index >= start) {
            // Append the current node's data to the sublist
            if (sublistHead == NULL) {
                sublistHead = createNode(current->data);
                sublistTail = sublistHead;
            } else {
                append(&sublistTail, current->data);
                sublistTail = sublistTail->next;
            }
        }
        current = current->next;
        index++;
    }

  return sublistHead;
}

// Function to free the memory allocated for the linked list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


This snippet includes a structure definition for a node in a singly linked list, functions to create a new node, append a node, extract a sublist from that list, and a function to free the linked list memory.