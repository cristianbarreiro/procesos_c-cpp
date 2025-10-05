#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2, pid3, pid4;

    // Padre crea primer hijo
    pid1 = fork();

    if (pid1 < 0) {
        perror("Error al crear el primer hijo");
        return 1;
    }

    if (pid1 == 0) {
        // Estamos en el Hijo 1
        printf("Soy el Hijo 1 (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());

        // Hijo 1 crea dos nietos
        pid3 = fork();
        if (pid3 == 0) {
            printf("  Soy el Nieto 1.1 (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());
        } else {
            pid4 = fork();
            if (pid4 == 0) {
                printf("  Soy el Nieto 1.2 (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());
            }
        }

    } else {
        // Solo el padre crea el segundo hijo
        pid2 = fork();

        if (pid2 < 0) {
            perror("Error al crear el segundo hijo");
            return 1;
        }

        if (pid2 == 0) {
            // Estamos en el Hijo 2
            printf("Soy el Hijo 2 (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());

            // Hijo 2 crea dos nietos
            pid3 = fork();
            if (pid3 == 0) {
                printf("  Soy el Nieto 2.1 (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());
            } else {
                pid4 = fork();
                if (pid4 == 0) {
                    printf("  Soy el Nieto 2.2 (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());
                }
            }

        } else {
            // Estamos en el padre
            printf("Soy el Padre (PID: %d), creé al Hijo 1 (PID: %d) y al Hijo 2 (PID: %d)\n", getpid(), pid1, pid2);
        }
    }

    return 0;
}
