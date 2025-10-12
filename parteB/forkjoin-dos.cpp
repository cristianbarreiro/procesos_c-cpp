#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2, pid3, pid4, pid5;

    //--s1--
    printf("Ejecutando S1(PID %d)\n", getpid());
    sleep(1);

    //--s2--
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("Error al crear S2");
        return 1;
    }
    else if (pid1 == 0)
    {
        printf("Ejecutando S2(PID %d)\n", getpid());
        sleep(1);
        return 0;
    }

    //--s3--
    pid2 = fork();
    if (pid2 < 0)
    {
        perror("Error al crear S3");
        return 1;
    }
    else if (pid2 == 0)
    {
        printf("Ejecutando S3(PID %d)\n", getpid());
        sleep(1);
        return 0;
    }

    //--s4--
    pid3 = fork();
    if (pid3 < 0)
    {
        perror("Error al crear S4");
        return 1;
    }
    else if (pid3 == 0)
    {
        printf("Ejecutando S4(PID %d)\n", getpid());
        sleep(1);
        return 0;
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    //--s5--
    pid4 = fork();
    if (pid4 < 0)
    {
        perror("Error al crear S5");
        return 1;
    }
    else if (pid4 == 0)
    {
        printf("Ejecutando S5(PID %d)\n", getpid());
        sleep(1);
        return 0;
    }

    waitpid(pid3, NULL, 0);
    waitpid(pid4, NULL, 0);

    //--s6--
    pid5 = fork();
    if (pid5 < 0)
    {
        perror("Error al crear S6");
        return 1;
    }
    else if (pid5 == 0)
    {
        printf("Ejecutando S6(PID %d)\n", getpid());
        sleep(1);
        return 0;
    }

    waitpid(pid5, NULL, 0);

    printf("Todos los procesos han terminado. (PID %d)\n", getpid());

    return 0;
}