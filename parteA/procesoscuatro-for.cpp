#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    pid_t hijo1_pid, hijo2_pid;

    printf("Soy el Padre (PID: %d)", getpid());

    // Primer nivel: Padre crea 2 hijos
    for (int i = 0; i < 2; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("Error al crear hijo");
            return 1;
        }
        else if (pid == 0)
        {
            // Soy un hijo
            printf("Soy el Hijo %d (PID: %d), hijo de (PID: %d)\n",
                   i + 1, getpid(), getppid());

            // Segundo nivel: Cada hijo crea 2 nietos
            for (int j = 0; j < 2; j++)
            {
                pid = fork();

                if (pid < 0)
                {
                    perror("Error al crear nieto");
                    return 1;
                }
                else if (pid == 0)
                {
                    // Soy un nieto
                    printf("  Soy el Nieto %d.%d (PID: %d), hijo de (PID: %d)\n",
                           i + 1, j + 1, getpid(), getppid());
                    return 0; // ← NIETO TERMINA AQUÍ
                }
                // El hijo continúa creando más nietos
            }
            return 0; // ← HIJO TERMINA AQUÍ después de crear todos sus nietos
        }
        else
        {
            // Guardar PIDs de los hijos
            if (i == 0) hijo1_pid = pid;
            else hijo2_pid = pid;
        }
    }

    // Solo el padre llega aquí
    printf(", creé al Hijo 1 (PID: %d) y al Hijo 2 (PID: %d)\n", 
           hijo1_pid, hijo2_pid);

    return 0;
}