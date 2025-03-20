#include <stdio.h>
#include <limits.h>

// Function to find waiting time for Non-Preemptive SJF
void findWaitingTimeNonPreemptive(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;  // Waiting time for the first process is 0

    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1]; // Waiting time of current process
    }
}

// Function to find turn around time for Non-Preemptive SJF
void findTurnAroundTimeNonPreemptive(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time = Burst time + Waiting time
    }
}

// Function to find average time for Non-Preemptive SJF
void findAvgTimeNonPreemptive(int processes[], int n, int bt[]) {
    int wt[n], tat[n];

    findWaitingTimeNonPreemptive(processes, n, bt, wt);
    findTurnAroundTimeNonPreemptive(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;

    printf("\nNon-Preemptive SJF\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

// Function to sort processes by burst time for Non-Preemptive SJF
void sortProcessesNonPreemptive(int processes[], int bt[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Preemptive SJF
void findWaitingTimePreemptive(int processes[], int n, int bt[], int wt[]) {
    int remaining_bt[n];

    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i]; // Initialize remaining burst times
    }


    int completed = 0, t = 0;
    while (completed < n) {
        int min_bt = INT_MAX, min_index = -1;

        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
                min_bt = remaining_bt[i];
                min_index = i;
            }
        }

        if (min_index != -1) {
            remaining_bt[min_index]--;
            if (remaining_bt[min_index] == 0) {
                completed++;
                wt[min_index] = t + 1 - bt[min_index];
            }
        }
        t++;
    }
}

// Function to find turn around time for Preemptive SJF
void findTurnAroundTimePreemptive(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time = Burst time + Waiting time
    }
}

// Function to find average time for Preemptive SJF
void findAvgTimePreemptive(int processes[], int n, int bt[]) {
    int wt[n], tat[n];

    findWaitingTimePreemptive(processes, n, bt, wt);
    findTurnAroundTimePreemptive(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;

    printf("\nPreemptive SJF\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n];

    // Get user input for process IDs and burst times
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;  // Process IDs (1-based)
        printf("Enter burst time for process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
    }

    // Non-Preemptive SJF
    sortProcessesNonPreemptive(processes, burst_time, n);
    findAvgTimeNonPreemptive(processes, n, burst_time);

    // Preemptive SJF
    int burst_time_copy[n];  // Copy of burst times for preemptive SJF
    for (int i = 0; i < n; i++) {
        burst_time_copy[i] = burst_time[i];
    }
    findAvgTimePreemptive(processes, n, burst_time_copy);

    return 0;
}
