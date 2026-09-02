#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int rows = heightsSize;
    int cols = heightsColSize[0];
    int** effort = (int**)malloc(rows * sizeof(int*));
    bool** visited = (bool**)malloc(rows * sizeof(bool*));
    for (int i = 0; i < rows; i++) {
        effort[i] = (int*)malloc(cols * sizeof(int));
        visited[i] = (bool*)calloc(cols, sizeof(bool));
        for (int j = 0; j < cols; j++) effort[i][j] = 1e9;
    }
    effort[0][0] = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int count = 0; count < rows * cols; count++) {
        int min_val = 1e9, r = -1, c = -1;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!visited[i][j] && effort[i][j] < min_val) {
                    min_val = effort[i][j];
                    r = i;
                    c = j;
                }
            }
        }
        if (r == -1 || (r == rows - 1 && c == cols - 1)) break;
        visited[r][c] = true;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                int current_diff = abs(heights[r][c] - heights[nr][nc]);
                int max_effort = (effort[r][c] > current_diff) ? effort[r][c] : current_diff;

                if (max_effort < effort[nr][nc]) {
                    effort[nr][nc] = max_effort;
                }
            }
        }
    }
    int result = effort[rows - 1][cols - 1];
    for (int i = 0; i < rows; i++) {
        free(effort[i]);
        free(visited[i]);
    }
    free(effort);
    free(visited);
    return result;
}
