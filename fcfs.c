#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void calculateTimes(struct Process proc[], int n) {
    int total_turnaround_time = 0, total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;

        total_turnaround_time += proc[i].turnaround_time;
        total_waiting_time += proc[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

void fcfs(struct Process proc[], int n) {
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < proc[i].arrival_time) {
            time = proc[i].arrival_time;
        }

        proc[i].completion_time = time + proc[i].burst_time;
        proc[i].waiting_time = time - proc[i].arrival_time;
        time = proc[i].completion_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }

    calculateTimes(proc, n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].completion_time = 0;
    }

    fcfs(proc, n);

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time, proc[i].completion_time);
    }

    return 0;
}
