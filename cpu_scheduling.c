#include <stdio.h>
#include <limits.h>

struct process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int priority;
    int waiting;
    int turnaround;
    int completed;
};

/* ================= FCFS ================= */
void fcfs(struct process p[], int n) {
    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    printf("\nExecution Order: ");

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival)
            current_time = p[i].arrival;

        printf("P%d ", p[i].pid);

        p[i].waiting = current_time - p[i].arrival;
        current_time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;

        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    printf("\n\nProcess\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\n", p[i].pid, p[i].waiting, p[i].turnaround);

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

/* ================= SJF (Non-Preemptive) ================= */
void sjf(struct process p[], int n) {
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("\nExecution Order: ");

    while (completed < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= current_time) {
                if (p[i].burst < min_bt) {
                    min_bt = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        printf("P%d ", p[idx].pid);

        p[idx].waiting = current_time - p[idx].arrival;
        current_time += p[idx].burst;
        p[idx].turnaround = p[idx].waiting + p[idx].burst;
        p[idx].completed = 1;

        total_wt += p[idx].waiting;
        total_tat += p[idx].turnaround;
        completed++;
    }

    printf("\n\nProcess\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\n", p[i].pid, p[i].waiting, p[i].turnaround);

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

/* ================= Priority Scheduling ================= */
void priority_scheduling(struct process p[], int n) {
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("\nExecution Order: ");

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= current_time) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        printf("P%d ", p[idx].pid);

        p[idx].waiting = current_time - p[idx].arrival;
        current_time += p[idx].burst;
        p[idx].turnaround = p[idx].waiting + p[idx].burst;
        p[idx].completed = 1;

        total_wt += p[idx].waiting;
        total_tat += p[idx].turnaround;
        completed++;
    }

    printf("\n\nProcess\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\n", p[i].pid, p[i].waiting, p[i].turnaround);

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

/* ================= Round Robin ================= */
void round_robin(struct process p[], int n, int quantum) {
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("\nExecution Order: ");

    while (completed < n) {
        int idle = 1;

        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].arrival <= current_time) {
                idle = 0;
                printf("P%d ", p[i].pid);

                if (p[i].remaining > quantum) {
                    p[i].remaining -= quantum;
                    current_time += quantum;
                } else {
                    current_time += p[i].remaining;
                    p[i].waiting = current_time - p[i].arrival - p[i].burst;
                    p[i].turnaround = p[i].waiting + p[i].burst;
                    p[i].remaining = 0;
                    completed++;

                    total_wt += p[i].waiting;
                    total_tat += p[i].turnaround;
                }
            }
        }

        if (idle)
            current_time++;
    }

    printf("\n\nProcess\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\n", p[i].pid, p[i].waiting, p[i].turnaround);

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

/* ================= MAIN ================= */
int main() {
    int n, choice, quantum;
    struct process p[20];

    printf("\nCPU Scheduling Simulator");
    printf("\n1. FCFS");
    printf("\n2. SJF (Non-Preemptive)");
    printf("\n3. Round Robin");
    printf("\n4. Priority Scheduling");
    printf("\nChoose Algorithm: ");
    scanf("%d", &choice);

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].completed = 0;

        printf("Enter arrival time, burst time and priority for P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);

        p[i].remaining = p[i].burst;
    }

    switch (choice) {
        case 1: fcfs(p, n); break;
        case 2: sjf(p, n); break;
        case 3:
            printf("Enter time quantum: ");
            scanf("%d", &quantum);
            round_robin(p, n, quantum);
            break;
        case 4: priority_scheduling(p, n); break;
        default: printf("Invalid choice!");
    }

    return 0;
}
