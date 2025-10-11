#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//esta version es incorrecta necesita corregirse
int main()
{
    pid_t pid;
    
    // Primer nivel: Padre crea 2 hijos
    for (int i = 0; i < 2; i++) 
    {
        pid = fork();
        
        if (pid < 0) {
            perror("Error al crear hijo");
            return 1;
        }
        
        if (pid == 0) {
            // Soy un hijo
            printf("Soy el Hijo %d (PID: %d), hijo de (PID: %d)\n", 
                   i+1, getpid(), getppid());
            
            // Segundo nivel: Cada hijo crea 2 nietos
            for (int j = 0; j < 2; j++) 
            {
                pid = fork();
                
                if (pid == 0) {
                    // Soy un nieto
                    printf("  Soy el Nieto %d.%d (PID: %d), hijo de (PID: %d)\n", 
                           i+1, j+1, getpid(), getppid());
                } else {
                    // El hijo continúa creando más nietos
                    continue;
                }
                break; // El nieto sale del bucle
            }
            break; // El hijo sale del bucle principal
        }
        // El padre continúa creando más hijos
    }
    
    // Solo el padre llega aquí
    if (pid > 0) {
        printf("Soy el Padre (PID: %d)\n", getpid());
    }
    
    return 0;
}