#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES  10    // Maximum number of nodes in the graph
#define MAX_EDGES  10    // Maximum number of edges any node can have
#define BUFFER_SIZE 1024 // Buffer size for string operations

// Node structure to represent each node in the graph
typedef struct {
    int id;
    char name[32];
} Node;

// Graph structure using an adjacency list
typedef struct {
    Node nodes[MAX_NODES];
    int edges[MAX_NODES][MAX_EDGES];
    int node_count;
    int edge_count[MAX_NODES];
} Graph;

// Function to append a string to another string
void str_append(char *dest, const char *src) {
    strcat(dest, src);
}

// Function to initialize the graph
void init_graph(Graph *g) {
    g->node_count = 0;
    for (int i = 0; i < MAX_NODES; ++i) {
        g->edge_count[i] = 0;
    }
}

// Function to add a node to the graph
void add_node(Graph *g, int id, const char *name) {
    if (g->node_count == MAX_NODES) {
        printf("Error: Node limit reached\n");
        return;
    }
    g->nodes[g->node_count].id = id;
    strncpy(g->nodes[g->node_count].name, name, sizeof(g->nodes[g->node_count].name) - 1);
    g->nodes[g->node_count].name[sizeof(g->nodes[g->node_count].name) - 1] = '\0'; // Null-terminate the string
    g->node_count++;
}

// Function to add an edge to the graph
void add_edge(Graph *g, int from, int to) {
    if (g->edge_count[from] == MAX_EDGES) {
        printf("Error: Edge limit for node %d reached\n", from);
        return;
    }
    g->edges[from][g->edge_count[from]] = to;
    g->edge_count[from]++;
}

// Function to print the dependency graph
void print_dependency_graph(const Graph *g) {
    char buffer[BUFFER_SIZE] = "";
    
    printf("Dependency Graph:\n");
    
    // Iterate over each node
    for (int i = 0; i < g->node_count; ++i) {
        int has_edges = 0;

        // Check if this node has outgoing edges
        for (int j = 0; j < g->edge_count[i]; ++j) {
            has_edges = 1;
            char edge_str[64];
            sprintf(edge_str, "%s -> %s\n", g->nodes[i].name, g->nodes[g->edges[i][j]].name);
            str_append(buffer, edge_str);
        }
        
        // If the node has no outgoing edges, just print the node name
        if (!has_edges) {
            str_append(buffer, g->nodes[i].name);
            str_append(buffer, "\n");
        }
    }

    printf("%s", buffer);
}

// Example usage
int main() {
    Graph g;
    init_graph(&g);
    
    add_node(&g, 0, "NodeA");
    add_node(&g, 1, "NodeB");
    add_node(&g, 2, "NodeC");
    
    add_edge(&g, 0, 1);
    add_edge(&g, 1, 2);
   
    print_dependency_graph(&g);
    return 0;
}
