#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // Abre el archivo para mapeo
    int fd = open("archivo.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir archivo");
        return 1;
    }

    // Obtiene el tamaño del archivo
    off_t file_size = lseek(fd, 0, SEEK_END);

    // Mapea el archivo a la memoria
    char *map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        perror("Error al mapear archivo a memoria");
        return 1;
    }

    // Ahora 'map' es un puntero a la memoria mapeada, que contiene los datos del archivo
    for (off_t i = 0; i < file_size; i++) {
        putchar(map[i]); // Accediendo al contenido del archivo mapeado
    }

    // Desmapea la memoria cuando ya no sea necesaria
    munmap(map, file_size);

    // Cierra el archivo
    close(fd);

    return 0;
}
