#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int B() {
    sleep(3);
    return 1;
}

int C() {
    sleep(1);
    return 2;
}

int E() {
    return 3;
}

int main() {
    pid_t pidB, pidC, pidE;

    // Crea el proceso B
    pidB = fork();

    if (pidB == 0) {  // Proceso hijo B
        int retB = B();
        exit(retB);
    } else {  // Proceso padre
        // Crea el proceso C
        pidC = fork();

        if (pidC == 0) {  // Proceso hijo C
            int retC = C();
            exit(retC);
        } else {  // Proceso padre
            // Espera a que el proceso B termine y obtiene su valor de retorno
            int statusB;
            waitpid(pidB, &statusB, 0);
            int retB = WEXITSTATUS(statusB);
            printf("Valor de retorno de B: %d\n", retB);

            // Espera a que el proceso C termine y obtiene su valor de retorno
            int statusC;
            waitpid(pidC, &statusC, 0);
            int retC = WEXITSTATUS(statusC);
            printf("Valor de retorno de C: %d\n", retC);

            // Crea el proceso E
            pidE = fork();

            if (pidE == 0) {  // Proceso hijo E
                int retE = E();
                exit(retE);
            } else {  // Proceso padre
                // Espera a que el proceso E termine y obtiene su valor de retorno
                int statusE;
                waitpid(pidE, &statusE, 0);
                int retE = WEXITSTATUS(statusE);
                printf("Valor de retorno de E: %d\n", retE);
            }
        }
    }

    return 0;
}

    
