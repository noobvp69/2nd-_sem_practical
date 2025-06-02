#include<stdio.h>

struct process {
    int id, at, bt, wt, tat, ct;
};

void main() {
    int i, n;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter arrival time for process %d (at): ", p[i].id);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d (bt): ", p[i].id);
        scanf("%d", &p[i].bt);
    }

    // First process
    p[0].ct = p[0].at + p[0].bt;
    p[0].tat = p[0].ct - p[0].at;
    p[0].wt = p[0].tat - p[0].bt;

    for(i = 1; i < n; i++) {
        if(p[i].at > p[i-1].ct)
            p[i].ct = p[i].at + p[i].bt;
        else
            p[i].ct = p[i-1].ct + p[i].bt;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    for(i = 0; i < n; i++) {
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nProcess ID\tArrival Time (at)\tBurst Time (bt)\tWaiting Time (wt)\tTurnaround Time (tat)\tCompletion Time (ct)\n");
    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t\t%d\t\t%d\t\t\t%d\t\t\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);
    }

    

    printf("\nAverage Waiting Time (wt): %.2f\n", avg_wt);
    printf("\nAverage Turnaround Time (tat): %.2f\n", avg_tat);
}
