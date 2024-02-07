#include <stdio.h>
#include <stdlib.h>

// Defining a hypothetical packet structure
typedef struct packet {
    char *data; // Pointer to packet data
    int length; // Length of the data
} Packet;

// Node in the packet buffer queue
typedef struct packet_node {
    Packet packet;
    struct packet_node *next;
} PacketNode;

// Structure representing the entity 'a' with a packet buffer queue
typedef struct {
    PacketNode *head; // Head of the packet buffer queue
    PacketNode *tail; // Tail of the packet buffer queue
} EntityA;

// Declaration of function to free a packet
void free_packet(Packet *packet);

// Function to flush packet buffers for entity 'a'
void flush_packet_buffers(EntityA *a) {
    if (a == NULL) {
        return;
    }

    PacketNode *current = a->head;
    PacketNode *next;

    while (current != NULL) {
        next = current->next;
        free_packet(&current->packet);
        free(current);
        current = next;
    }

    // Reset the head and tail of the queue to indicate it is empty
    a->head = NULL;
    a->tail = NULL;
}

// Implementation of function to free a packet
void free_packet(Packet *packet) {
    if (packet->data != NULL) {
        free(packet->data);
    }
}

/* Please make sure to initialize EntityA with NULL values for head and tail
   before using flush_packet_buffers function. */
