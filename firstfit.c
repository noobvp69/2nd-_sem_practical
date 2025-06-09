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
    for (int i = 0; i <nh; i++) {
        
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

    for (int i = 0; i < np; i++)
        for (int j = 0; j < nh; j++)
            if (!p[i].flag && p[i].size <= h[j].size) {
                p[i].flag = 1;
                p[i].holeId = j;
                h[j].size -= p[i].size;
                break;
            }

printf("\n\tFirst Fit Allocation\n");
printf("Process\tSize\tHole\n");

for (int i = 0; i < np; i++) {
    if (p[i].flag)
        printf("P%d\t%d\tH%d\n", i, p[i].size, p[i].holeId);
    else
        printf("P%d\t%d\tNot allocated\n", i, p[i].size);
}

printf("\nHole\tActual\tAvailable\n");
for (int i = 0; i < nh; i++)
    printf("H%d\t%d\t%d\n", i, h[i].actual, h[i].size);

    return 0;
}
