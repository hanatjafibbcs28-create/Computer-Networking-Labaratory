#include <stdlib.h>
#include <stdbool.h>
int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    int dist[101];
    for (int i = 1; i <= n; i++) dist[i] = 1e9;
    dist[k] = 0;
    for (int i = 1; i < n; i++) {
        bool updated = false;
        for (int j = 0; j < timesSize; j++) {
            int u = times[j][0], v = times[j][1], w = times[j][2];
            if (dist[u] != 1e9 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if (!updated) break; 
    }
    int max_time = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == 1e9) return -1; 
        if (dist[i] > max_time) max_time = dist[i];
    }
    return max_time;
}
