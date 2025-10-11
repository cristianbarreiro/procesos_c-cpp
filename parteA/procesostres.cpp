#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid1, pid2, pid3;

    // Primer fork - Hijo 1
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("Error al crear el primer hijo");
        return 1;
    }
    else if (pid1 == 0)
    {
        // Estamos en el Hijo 1
        printf("Soy el Hijo 1 (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());

        // El Hijo 1 crea a su propio hijo (Nieto del proceso original)
        pid3 = fork();

        if (pid3 < 0)
        {
            perror("Error al crear el nieto");
            return 1;
        }

        if (pid3 == 0)
        {
            // Nieto
            printf("  Soy el Nieto (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());
        }
    }
    else
    {
        // Estamos todavía en el Padre
        // Segundo fork - Hijo 2
        pid2 = fork();

        if (pid2 < 0)
        {
            perror("Error al crear el segundo hijo");
            return 1;
        }
        else if (pid2 == 0)
        {
            // Hijo 2
            printf("Soy el Hijo 2 (PID: %d), hijo de (PID: %d)\n", getpid(), getppid());
        }
        else
        {
            // Padre
            printf("Soy el Padre (PID: %d), creé al Hijo 1 (PID: %d) y al Hijo 2 (PID: %d)\n",
                   getpid(), pid1, pid2);
        }
    }

    return 0;
}
