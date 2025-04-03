#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turn_around_time;
} Process;

void calculateTimes(Process processes[], int num_processes) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    int current_time = 0;
    for (int i = 0; i < num_processes; i++) {
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        if (processes[i].waiting_time < 0)
            processes[i].waiting_time = 0;

        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;

        current_time = processes[i].completion_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turn_around_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / num_processes);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / num_processes);
}

void FCFS(Process processes[], int num_processes) {
    printf("\nProcess Scheduling Order (FCFS):\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d -> Arrival Time: %d, Burst Time: %d\n",
               processes[i].id, processes[i].arrival_time, processes[i].burst_time);
    }

    calculateTimes(processes, num_processes);
}

void multiLevelQueueScheduling(Process system_processes[], int num_system_processes,
                               Process user_processes[], int num_user_processes) {
    printf("\n--- Scheduling System Processes (High Priority) ---\n");
    FCFS(system_processes, num_system_processes);

    printf("\n--- Scheduling User Processes (Low Priority) ---\n");
    FCFS(user_processes, num_user_processes);
}

int main() {
    Process system_processes[MAX_PROCESSES], user_processes[MAX_PROCESSES];
    int num_system_processes, num_user_processes;

    printf("Enter the number of system processes: ");
    scanf("%d", &num_system_processes);
    for (int i = 0; i < num_system_processes; i++) {
        system_processes[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for System Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &system_processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &system_processes[i].burst_time);
    }

    printf("\nEnter the number of user processes: ");
    scanf("%d", &num_user_processes);
    for (int i = 0; i < num_user_processes; i++) {
        user_processes[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for User Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &user_processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &user_processes[i].burst_time);
    }

    multiLevelQueueScheduling(system_processes, num_system_processes,
                              user_processes, num_user_processes);

    return 0;
}
