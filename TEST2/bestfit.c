#include <stdio.h>

struct Process {
    int size, flag, holeId;
} p[10];

struct Hole {
    int size, actual;
} h[10];

int main() {
    int np, nh;
    printf("Enter number of Holes: ");
    scanf("%d", &nh);
    for (int i = 0; i < nh; i++) {
        printf("Size of hole H%d: ", i);
        scanf("%d", &h[i].size);
        h[i].actual = h[i].size;
    }

    printf("\nEnter number of Processes: ");
    scanf("%d", &np);
    for (int i = 0; i < np; i++) {
        printf("Size of process P%d: ", i);
        scanf("%d", &p[i].size);
        p[i].flag = 0;
    }

    // Best Fit Allocation
    for (int i = 0; i < np; i++) {
        int bestIdx = -1;
        for (int j = 0; j < nh; j++) {
            if (p[i].size <= h[j].size) {
                if (bestIdx == -1 || h[j].size < h[bestIdx].size)
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            p[i].flag = 1;
            p[i].holeId = bestIdx;
            h[bestIdx].size -= p[i].size;
        }
    }

    printf("\n\tBest Fit Allocation\n");
 
    printf("Process\tSize\tAllocated Hole\n");
   
    for (int i = 0; i < np; i++) {
        if (p[i].flag)
            printf("P%d\t%d\tH%d\n", i, p[i].size, p[i].holeId);
        else
            printf("P%d\t%d\tNot allocated\n", i, p[i].size);
    }


    printf("Hole\tActual\tAvailable\n");
   
    for (int i = 0; i < nh; i++)
        printf("H%d\t%d\t%d\n", i, h[i].actual, h[i].size);

    return 0;
}
