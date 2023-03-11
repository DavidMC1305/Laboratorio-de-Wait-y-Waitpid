#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid_A, pid_B, pid_C, pid_D;
    int status_A, status_B, status_C;

    //Proceso D
    pid_D = fork();
    if (pid_D == 0) {
        printf("Proceso D, PID: %d, PPID: %d\n", getpid(), getppid());
        execl("/bin/ls", "ls", NULL);
        exit(0);
    } else {
        wait(&status_C);
        printf("\n");
    }

    //Proceso A
    pid_A = fork();
    if (pid_A == 0) {
        printf("Proceso A, PID: %d, PPID: %d\n", getpid(), getppid());
        execl("/bin/rm", "rm", "-r", "new_folder", NULL);
        exit(0);
    } else {
        wait(&status_A);
        printf("\n");
    }

    //Proceso C
    pid_C = fork();
    if (pid_C == 0) {
        printf("Proceso C, PID: %d, PPID: %d\n", getpid(), getppid());
        execl("/bin/ls", "ls", NULL);
        exit(0);
    } else {
        wait(&status_C);
        printf("\n");
    }

    //Proceso M
    if (pid_A > 0 && pid_C > 0) {
        printf("Soy M y mi PID es %d\n", getpid());
        pid_B = fork();
        if (pid_B == 0) { // Proceso B
            printf("Proceso B, PID: %d, PPID: %d\n", getpid(), getppid());
            execl("/bin/mkdir", "mkdir", "new_folder", NULL);
            exit(0);
        } else {
            wait(&status_B);
            execl("/bin/ls", "ls", NULL);
        }
    }
    return 0;
}
