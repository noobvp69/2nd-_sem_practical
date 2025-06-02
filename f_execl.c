#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    
    if (pid > 0) {
        // Parent process
        wait(NULL);
        printf("Process creation completed.\n");
        exit(EXIT_SUCCESS);
    } 
    else if (pid == 0) {
        // Child process
        if (argc < 3) {
            fprintf(stderr, "Usage: %s <program> <arg1>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        execl(argv[1], argv[1], argv[2], NULL);
        perror("execl failed");
        exit(EXIT_FAILURE);
    } 
    else {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}
