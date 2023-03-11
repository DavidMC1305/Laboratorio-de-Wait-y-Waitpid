#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void D() {
    sleep(1);
    printf("Terminé mi ejecución, mi PID es %d y el de mi padre es %d\n", getpid(), getppid());
}

void L() {
    sleep(3);
    printf("Terminé mi ejecución, mi PID es %d y el de mi padre es %d\n", getpid(), getppid());
}

int main() {
    pid_t pidL, pidD;

    pidL = fork();
    if (pidL == 0) { // Proceso hijo L
        L();
        exit(0);
    } else if (pidL > 0) { // Proceso padre
        pidD = fork();
        if (pidD == 0) { // Proceso hijo D
            D();
            exit(0);
        } else if (pidD > 0) { // Proceso padre
            int status;
            pid_t pidTerminado = wait(&status);
            printf("Uno de mis hijos ha terminado su ejecución\n");
            exit(0);
        } else {
            perror("Error al crear el proceso hijo D");
            exit(1);
        }
    } else {
        perror("Error al crear el proceso hijo L");
        exit(1);
    }

    return 0;
}

