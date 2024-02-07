#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple string append function
void str_append(char *dest, const char *src) {
    strcat(dest, src);
}

// Define the maximum length of a node label
#define MAX_LABEL_LENGTH 50

// A node representation in the graph
typedef struct Node {
    char label[MAX_LABEL_LENGTH];
    int num_edges;
    struct Node **edges; // An array of pointers to other nodes (dependencies)
} Node;

// Function prototypes
Node* create_node(const char *label);
void add_edge(Node *from, Node *to);
void print_dependency_graph(Node *nodes[], int num_nodes);
void free_graph(Node *nodes[], int num_nodes);

// Main function demonstrating the graph printing
int main() {
    // Creating graph nodes
    Node *a = create_node("A");
    Node *b = create_node("B");
    Node *c = create_node("C");

    // Adding edges
    add_edge(a, b); // A -> B
    add_edge(a, c); // A -> C
    add_edge(b, c); // B -> C

    // Graph array
    Node *graph[] = {a, b, c};
    print_dependency_graph(graph, 3);

    // Cleaning up memory
    free_graph(graph, 3);

    return 0;
}

// Function implementations
Node* create_node(const char *label) {
    Node *node = malloc(sizeof(Node));
    strncpy(node->label, label, MAX_LABEL_LENGTH);
    node->label[MAX_LABEL_LENGTH - 1] = '\0'; // Ensure null termination
    node->num_edges = 0;
    node->edges = NULL;
    return node;
}

void add_edge(Node *from, Node *to) {
    from->num_edges++;
    from->edges = realloc(from->edges, from->num_edges * sizeof(Node*));
    from->edges[from->num_edges - 1] = to;
}

void print_dependency_graph(Node *nodes[], int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        Node *node = nodes[i];
        for (int j = 0; j < node->num_edges; j++) {
            char output[MAX_LABEL_LENGTH * 3];
            strcpy(output, node->label);
            str_append(output, " -> ");
            str_append(output, node->edges[j]->label);
            printf("%s\n", output);
        }
    }
}

void free_graph(Node *nodes[], int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        free(nodes[i]->edges);
        free(nodes[i]);
    }
}


In this code sample:
- `str_append` uses `strcat` to concatenate two strings.
- `create_node` allocates a new node and initializes its label.
- `add_edge` adds a directed edge between two nodes by reallocating the `edges` array of the `from` node.
- `print_dependency_graph` iterates through all the nodes and their edges, building an output string to represent the edge (arrow) and prints it to the console.
- `free_graph` frees the dynamically allocated edge arrays and nodes.