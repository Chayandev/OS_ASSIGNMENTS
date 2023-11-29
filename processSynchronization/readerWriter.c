#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h> // Include for intptr_t

#define READER_SIZE 3
#define WRITER_SIZE 2

sem_t mutex, database;
int data = 0, rc = 0;

void *writer(void *arg) {
    while (1) {
        intptr_t nw = (intptr_t)arg;
        if (sem_wait(&database) != 0) {
            printf("Writer %ld is waiting to write\n", nw);
        }
        // Writing to the shared data
        data++;
        printf("Writer %ld writing data: %d\n", nw, data);
        sleep(2);

        printf("Writer %ld stops writing data: %d\n", nw, data);
        // Release the database semaphore after writing is done
        sem_post(&database);

        // Sleep to simulate other work
        sleep(2);
    }
    return NULL;
}

void *reader(void *arg) {
    while (1) {
        intptr_t rn = (intptr_t)arg;
        if (sem_wait(&mutex) != 0);
        printf("Reader %ld is waiting for reading.\n", rn);
        rc++;
        if (rc == 1)
            sem_wait(&database);
        sem_post(&mutex);
        // Reading the shared data
        printf("Reader %ld is reading data: %d\n", rn, data);
        sleep(1);
        sem_wait(&mutex);
        rc--;
        printf("Reader %ld stops reading data: %d\n", rn, data);
        if (rc == 0)
            sem_post(&database);
        sem_post(&mutex);

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t readerThreads[READER_SIZE], writerThreads[WRITER_SIZE];

    // initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&database, 0, 1);

    // create writerThreads
    for (int i = 0; i < WRITER_SIZE; i++) {
        pthread_create(&writerThreads[i], NULL, writer, (void *)(intptr_t)(i + 1));
    }
    // create readerThreads
    for (int i = 0; i < READER_SIZE; i++) {
        pthread_create(&readerThreads[i], NULL, reader, (void *)(intptr_t)(i + 1));
    }

    for (int i = 0; i < WRITER_SIZE; ++i) {
        pthread_join(writerThreads[i], NULL);
    }

    for (int i = 0; i < READER_SIZE; ++i) {
        pthread_join(readerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&database);

    return 0;
}
