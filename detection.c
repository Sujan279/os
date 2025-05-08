#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

bool is_deadlock(int allocation[MAX_PROCESSES][MAX_RESOURCES], int request[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES], int num_processes, int num_resources) {
    bool finish[MAX_PROCESSES] = {0};
    int work[MAX_RESOURCES];

    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    while (1) {
        bool progress_made = false;

        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_execute = 1;
                for (int j = 0; j < num_resources; j++) {
                    if (request[i][j] > work[j]) {
                        can_execute = 0;
                        break;
                    }
                }

                if (can_execute) {
                    finish[i] = 1;
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    progress_made = true;
                }
            }
        }

        if (!progress_made) break;
    }

    for (int i = 0; i < num_processes; i++) {
        if (!finish[i]) return true;
    }
    return false;
}

int main() {
    int allocation[MAX_PROCESSES][MAX_RESOURCES], request[MAX_PROCESSES][MAX_RESOURCES], available[MAX_RESOURCES];
    int num_processes = 3, num_resources = 3;

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    if (is_deadlock(allocation, request, available, num_processes, num_resources)) {
        printf("Deadlock detected!\n");
    } else {
        printf("No deadlock detected.\n");
    }

    return 0;
}
