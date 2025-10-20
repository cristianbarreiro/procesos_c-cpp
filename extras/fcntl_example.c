#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // Abre el archivo en modo escritura (crea el archivo si no existe)
    int fd = open("mi_archivo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Escribe un mensaje en el archivo
    const char *mensaje = "Hola, este es un archivo de prueba.\n";
    if (write(fd, mensaje, 36) == -1) {
        perror("Error al escribir en el archivo");
        close(fd);
        return 1;
    }

    // Cierra el archivo
    close(fd);

    return 0;
}
