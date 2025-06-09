#include <stdio.h>
#include <string.h>

char disk[20][4] = {""}, fname[10][4]; // disk blocks and file names
int start[10], length[10], count = 0;

void showDirectory() {
    printf("\nFile\tStart\tLength\n");
    for (int i = 0; i < count; i++) {
        printf("%-4s\t%3d\t%6d\n", fname[i], start[i], length[i]);
    }
}

void showDisk() {
    printf("\nDisk Blocks:\n");
    for (int i = 0; i < 20; i++) {
        printf("%4d", i);
    }
    printf("\n");
    for (int i = 0; i < 20; i++) {
        printf("%4s", disk[i][0] ? disk[i] : ".");
    }
    printf("\n");
}

int main() {
    char id[4]; int st, len, ch;
    showDisk();

    do {
        printf("\nEnter file name, start block, and length: ");
        scanf("%3s %d %d", id, &st, &len);

        if (st < 0 || st + len > 20) {
            printf("Out of bounds.\n");
            continue;
        }

        int free = 1;
        for (int i = st; i < st + len; i++) {
            if (disk[i][0]) {
                free = 0;
                break;
            }
        }

        if (!free) {
            printf("Blocks occupied.\n");
            continue;
        }

        strcpy(fname[count], id); 
        start[count] = st; 
        length[count] = len;
        for (int i = st; i < st + len; i++) {
            strcpy(disk[i], id);
        }
        count++;

        printf("Allocated. More? (1.Yes 2.No): ");
        scanf("%d", &ch);
    } while (ch == 1);

    showDirectory();
    showDisk();
    return 0;
}
