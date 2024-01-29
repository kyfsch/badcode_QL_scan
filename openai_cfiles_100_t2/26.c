#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 100

void str_append(char *str1, const char *str2);

void print_dependency_graph(const char *nodes[], int num_nodes, const int edges[][2], int num_edges) {
    char output[MAX_STR_LEN] = {0};

    // Append node names to output
    for (int i = 0; i < num_nodes; i++) {
        str_append(output, nodes[i]);
        str_append(output, " -> ");
    }

    // Append edges to output
    for (int i = 0; i < num_edges; i++) {
        char edge[MAX_STR_LEN];
        sprintf(edge, "%s -> %s", nodes[edges[i][0]], nodes[edges[i][1]]);
        str_append(output, edge);
    }

    printf("%s\n", output);
}

void str_append(char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    strncpy(str1 + len1, str2, MAX_STR_LEN - len1 - 1);
    str1[MAX_STR_LEN - 1] = '\0';
}


To use this function, you can define an array of node names and an array of edges, and pass them to the function:
c
int main() {
    const char *nodes[] = { "A", "B", "C", "D", "E" };
    int num_nodes = sizeof(nodes) / sizeof(nodes[0]);

    const int edges[][2] = { {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0} };
    int num_edges = sizeof(edges) / sizeof(edges[0]);

    print_dependency_graph(nodes, num_nodes, edges, num_edges);

    return 0;
}
