#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int i;

    printf("Padre (PID: %d) inicia la creación de procesos\n", getpid());

    // Crear todos los hijos primero
    for (i = 0; i < 3; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("Error al crear proceso");
            return 1;
        }
        else if (pid == 0)
        {
            printf("Soy el hijo %d, mi PID es %d\n", i + 1, getpid());
            sleep(1 + i);
            printf("Hijo %d (PID: %d) terminó su tarea.\n", i + 1, getpid());
            return 0;
        }
    }
    
    // Luego esperar a todos los hijos
    for (i = 0; i < 3; i++)
    {
        wait(NULL);
    }
    
    printf("Padre (PID: %d) ha terminado de esperar a sus hijos.\n", getpid());
    return 0;
}