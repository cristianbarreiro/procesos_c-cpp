#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  pid_t pid;
  for (int i = 0; i < 4; i++)
  {
    pid = fork();
    if (pid < 0)
    {
      // Error al crear proceso
      perror("fork");
      printf("Error al crear proceso %d", pid);
      return 1;
    }
    else if (pid == 0)
    {
      // Código que ejecuta el proceso hijo
      printf("Soy el hijo, mi PID es %d\n", getpid());
    }
    else
    {
      // Código que ejecuta el proceso padre
      printf("Soy el padre, mi PID es %d y cree un hijo con PID %d\n",
             getpid(), pid);
      break;
    }
  }

  return 0;
}