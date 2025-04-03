#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10
#define MAX_TIME 100

// Structure to represent each task
typedef struct {
    int id;              // Task ID
    int period;          // Period of the task
    int execution_time;  // Time required to execute the task
    int remaining_time;  // Remaining execution time
    int next_deadline;   // Next deadline of the task
} Task;

// Function to compare tasks based on their periods (for Rate Monotonic Scheduling)
int compare(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskA->period - taskB->period;
}

// Function to simulate Rate-Monotonic Scheduling
void rateMonotonicScheduling(Task tasks[], int num_tasks) {
    int time = 0;
    int completed_tasks = 0;

    // Initialize tasks
    for (int i = 0; i < num_tasks; i++) {
        tasks[i].remaining_time = tasks[i].execution_time;
        tasks[i].next_deadline = tasks[i].period;
    }

    // Sort tasks by period (Rate Monotonic)
    qsort(tasks, num_tasks, sizeof(Task), compare);

    // Simulate the scheduling
    printf("Time\tTask Executing\n");
    while (completed_tasks < num_tasks) {
        // Find the task with the highest priority (shortest period)
        for (int i = 0; i < num_tasks; i++) {
            // Check if the task is ready to run (its remaining time > 0)
            if (tasks[i].remaining_time > 0 && time % tasks[i].period == 0) {
                // Execute the task for one time unit
                printf("%d\tTask %d\n", time, tasks[i].id);
                tasks[i].remaining_time--;
                // If the task is completed, increment the completed task count
                if (tasks[i].remaining_time == 0) {
                    completed_tasks++;
                }
                break;
            }
        }
        time++;
    }
}

int main() {
    // Declare an array of tasks
    Task tasks[MAX_TASKS];
    int num_tasks;

    // Input the number of tasks
    printf("Enter the number of tasks (up to %d): ", MAX_TASKS);
    scanf("%d", &num_tasks);

    // Input details for each task (Period and Execution time)
    for (int i = 0; i < num_tasks; i++) {
        tasks[i].id = i + 1; // Task ID starts from 1
        printf("\nEnter details for Task %d:\n", i + 1);
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        printf("Execution time: ");
        scanf("%d", &tasks[i].execution_time);
    }

    // Simulate Rate-Monotonic Scheduling
    rateMonotonicScheduling(tasks, num_tasks);

    return 0;
}
