#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_STOP_VAL 1000000
typedef struct {
    int stop;
    int bus_count;
} QueueNode;
int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    if (source == target) {
        return 0;
    }
    int total_elements = 0;
    for (int i = 0; i < routesSize; i++) {
        total_elements += routesColSize[i];
    }
    int* head_route = (int*)malloc(MAX_STOP_VAL * sizeof(int));
    memset(head_route, -1, MAX_STOP_VAL * sizeof(int));
    int* next_route = (int*)malloc(total_elements * sizeof(int));
    int* route_indices = (int*)malloc(total_elements * sizeof(int));
    int edge_cnt = 0;
    for (int i = 0; i < routesSize; i++) {
        for (int j = 0; j < routesColSize[i]; j++) {
            int stop = routes[i][j];
            route_indices[edge_cnt] = i;
            next_route[edge_cnt] = head_route[stop];
            head_route[stop] = edge_cnt;
            edge_cnt++;
        }
    }
    bool* visited_stops = (bool*)calloc(MAX_STOP_VAL, sizeof(bool));
    bool* visited_routes = (bool*)calloc(routesSize, sizeof(bool));
    QueueNode* queue = (QueueNode*)malloc((total_elements + 2) * sizeof(QueueNode));
    int q_head = 0, q_tail = 0;
    queue[q_tail++] = (QueueNode){source, 0};
    visited_stops[source] = true;
    int final_result = -1;
    while (q_head < q_tail) {
        QueueNode curr = queue[q_head++];
        int curr_stop = curr.stop;
        int curr_count = curr.bus_count;
        for (int e = head_route[curr_stop]; e != -1; e = next_route[e]) {
            int r_idx = route_indices[e];
            if (visited_routes[r_idx]) {
                continue;
            }
            visited_routes[r_idx] = true;
            int* current_route = routes[r_idx];
            int route_len = routesColSize[r_idx];            
            for (int i = 0; i < route_len; i++) {
                int next_stop = current_route[i];
                if (next_stop == target) {
                    final_result = curr_count + 1;
                    goto cleanup;
                }
                if (!visited_stops[next_stop]) {
                    visited_stops[next_stop] = true;
                    queue[q_tail++] = (QueueNode){next_stop, curr_count + 1};
                }
            }
        }
    }
cleanup:
    free(head_route);
    free(next_route);
    free(route_indices);
    free(visited_stops);
    free(visited_routes);
    free(queue);
    return final_result;
}
