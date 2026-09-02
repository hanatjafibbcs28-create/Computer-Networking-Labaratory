#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
    int to;
    int cost; 
    int next;
} Edge;
int minReorder(int n, int** connections, int connectionsSize, int* connectionsColSize) {
    int* head = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) head[i] = -1;
    Edge* edges = (Edge*)malloc(2 * (n - 1) * sizeof(Edge));
    int edge_idx = 0;
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        edges[edge_idx].to = v;
        edges[edge_idx].cost = 1;
        edges[edge_idx].next = head[u];
        head[u] = edge_idx++;
        edges[edge_idx].to = u;
        edges[edge_idx].cost = 0;
        edges[edge_idx].next = head[v];
        head[v] = edge_idx++;
    }
    int* queue = (int*)malloc(n * sizeof(int));
    bool* visited = (bool*)calloc(n, sizeof(bool));
    int head_q = 0, tail_q = 0;
    queue[tail_q++] = 0;
    visited[0] = true;
    int total_reversals = 0;
    while (head_q < tail_q) {
        int curr = queue[head_q++];
        int e = head[curr];
        while (e != -1) {
            int neighbor = edges[e].to;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                total_reversals += edges[e].cost;
                queue[tail_q++] = neighbor;
            }
            e = edges[e].next;
        }
    }
    free(head);
    free(edges);
    free(queue);
    free(visited);
    return total_reversals;
}
