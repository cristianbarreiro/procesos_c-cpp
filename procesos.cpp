#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  pid_t pid = fork(); // Crear un nuevo proceso

  if (pid < 0)
  {
    // Error al crear proceso
    perror("fork");
    return 1;
  }
  else if (pid == 0)
  {
    // Código que ejecuta el proceso hijo
    printf("Soy el hijo %d, mi PID es %d\n", pid, getpid());
  }
  else
  {
    // Código que ejecuta el proceso padre
    printf("Soy el padre, mi PID es %d y cree un hijo con PID %d\n",
           getpid(), pid);
  }

  return 0;
}