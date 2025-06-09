#include <stdio.h>

// Define a structure for process
struct process {
    int id, bt, at, priority; // ID, Burst Time, Arrival Time, Priority
    int wt, tat, ct,done; // Waiting Time, Turnaround Time, Completion Time
     ; // Whether process is completed
};

int main() {
    int n, i, time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    // Input process details
    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: "); scanf("%d", &p[i].at);
        printf("Burst Time: "); scanf("%d", &p[i].bt);
        printf("Priority (lower number = higher priority): "); scanf("%d", &p[i].priority);
        p[i].done = 0;
    }

    // Scheduling logic
    while (completed < n) {
        int idx = -1, minPriority = 9999;

        // Find the highest priority (lowest number) process that has arrived
        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].priority < minPriority) {
                minPriority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
            completed++;
        } else {
            time++; // No process is ready, move forward in time
        }
    }

    // Output
    printf("\nID\tAT\tBT\tPriority\tCT\tTAT\tWT");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t\t%d\t%d\t%d", 
            p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\n\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
