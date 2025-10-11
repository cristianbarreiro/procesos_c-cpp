#include <stdio.h>
#include <pthread.h>

#define NUM_HILOS 5

int cont = 0;
pthread_mutex_t mutex;

void *funcion_hilos(void *arg)
{
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&mutex);
        cont++;
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    // Utilizar mutex para asegurar la sección crítica
    pthread_t hilos[NUM_HILOS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_HILOS; i++)
    {
        pthread_create(&hilos[i], NULL, funcion_hilos, NULL);
    }

    for (int i = 0; i < NUM_HILOS; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    printf("Valor final del contador: %d\n", cont);

    pthread_mutex_destroy(&mutex);

    return 0;
}