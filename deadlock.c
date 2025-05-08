#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    bool finish[P];
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allot[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    int avail[] = {3, 3, 2};

    int max[][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int allot[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    if (isSafe(processes, avail, max, allot)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}
