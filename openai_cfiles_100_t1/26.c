#include <stdio.h>
#include <string.h>

void print_dependency_graph(const char* nodes[], int num_nodes, const char* edges[], int num_edges) {
    // Create a string to store the graph
    char graph[1000];
    strcpy(graph, "");

    // Add nodes to the graph
    for (int i = 0; i < num_nodes; i++) {
        str_append(graph, nodes[i]);
        str_append(graph, "\n");
    }

    // Add arrows between the nodes
    for (int i = 0; i < num_edges; i++) {
        str_append(graph, edges[i]);
        str_append(graph, "\n");
    }

    // Print the graph
    printf("%s", graph);
}


You can call this function by passing an array of node names and an array of edge strings, like this:

c
const char* nodes[] = {"A", "B", "C", "D"};
int num_nodes = 4;

const char* edges[] = {"A -> B", "A -> C", "B -> D", "C -> D"};
int num_edges = 4;

print_dependency_graph(nodes, num_nodes, edges, num_edges);


This will output the following graph: