#include <stdio.h>
#include <limits.h>

// Function to calculate waiting time for Non-Preemptive Priority Scheduling
void findWaitingTimeNonPreemptive(int processes[], int n, int bt[], int wt[], int priority[]) {
    int i, j;
    int total_bt = 0;

    // Find total burst time of all processes
    for (i = 0; i < n; i++) {
        total_bt += bt[i];
    }

    int completed = 0;
    int remaining_bt[n];

    // Initialize remaining burst times
    for (i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    // Process execution order
    while (completed < n) {
        int min_priority = 9999;
        int index = -1;

        // Select the process with the smallest priority number
        for (i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && priority[i] < min_priority) {
                min_priority = priority[i];
                index = i;
            }
        }

        // Decrement the remaining burst time of the selected process
        remaining_bt[index]--;
        if (remaining_bt[index] == 0) {
            completed++;
            wt[index] = total_bt - bt[index];
        }
    }
}

// Function to calculate turnaround time for Non-Preemptive Priority Scheduling
void findTurnaroundTimeNonPreemptive(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // Turnaround time = Burst time + Waiting time
    }
}

// Function to calculate average waiting time and turnaround time for Non-Preemptive
void findAvgTimeNonPreemptive(int processes[], int n, int bt[], int priority[]) {
    int wt[n], tat[n];

    findWaitingTimeNonPreemptive(processes, n, bt, wt, priority);
    findTurnaroundTimeNonPreemptive(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;

    printf("\nPriority Scheduling (Non-Preemptive)\n");
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], priority[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

// Function to calculate waiting time for Preemptive Priority Scheduling
void findWaitingTimePreemptive(int processes[], int n, int bt[], int wt[], int priority[]) {
    int remaining_bt[n];

    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i]; // Initialize remaining burst times
    }

    int completed = 0, t = 0;
    while (completed < n) {
        int min_priority = INT_MAX, index = -1;

        // Find the process with the smallest priority number
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && priority[i] < min_priority) {
                min_priority = priority[i];
                index = i;
            }
        }

        if (index != -1) {
            remaining_bt[index]--;
            if (remaining_bt[index] == 0) {
                completed++;
                wt[index] = t + 1 - bt[index];
            }
        }
        t++;
    }
}

// Function to calculate turnaround time for Preemptive Priority Scheduling
void findTurnaroundTimePreemptive(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround time = Burst time + Waiting time
    }
}

// Function to calculate average waiting time and turnaround time for Preemptive
void findAvgTimePreemptive(int processes[], int n, int bt[], int priority[]) {
    int wt[n], tat[n];

    findWaitingTimePreemptive(processes, n, bt, wt, priority);
    findTurnaroundTimePreemptive(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;

    printf("\nPriority Scheduling (Preemptive)\n");
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], priority[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], priority[n];

    // Get user input for process IDs, burst times, and priorities
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;  // Process IDs (1-based)
        printf("Enter burst time for process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
        printf("Enter priority for process %d: ", processes[i]);
        scanf("%d", &priority[i]);
    }

    // Calculate and display results for Non-Preemptive Priority Scheduling
    findAvgTimeNonPreemptive(processes, n, burst_time, priority);

    // Calculate and display results for Preemptive Priority Scheduling
    int burst_time_copy[n];  // Copy of burst times for preemptive scheduling
    for (int i = 0; i < n; i++) {
        burst_time_copy[i] = burst_time[i];
    }
    findAvgTimePreemptive(processes, n, burst_time_copy, priority);

    return 0;
}
