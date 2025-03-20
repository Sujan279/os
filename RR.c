#include <stdio.h>

void findWaitingTime(int n, int bt[], int wt[], int quantum) {
    int rem_bt[n];
    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
    }

    int time = 0;
    int completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                if (rem_bt[i] <= quantum) {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                    completed++;
                } else {
                    rem_bt[i] -= quantum;
                    time += quantum;
                }
            }
        }
    }
}

void findTurnaroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}



int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n];
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time of process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);



    return 0;
}

