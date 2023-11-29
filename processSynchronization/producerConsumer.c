#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 3

sem_t mutex, empty, full;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void produce(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
}

int consume() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return item;
}

void *producer(void *arg) {
    int item;
    //sleep(5);
    while (1) {
        intptr_t prid = (intptr_t)arg;
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);
        if (sem_wait(&mutex) != 0) {
            printf("Producer %ld is waiting.\n",prid);
        }
        printf("Producer %ld producing item: %d\n", prid,item);
        produce(item);
        sleep(2);
        sem_post(&mutex);
        printf("Producer %ld produced item: %d\n",prid, item);
        sem_post(&full);

        sleep(1);  // Sleep to simulate varying production times
    }

    return NULL;
}

void *consumer(void *arg) {
    int item;

    while (1) {
        intptr_t crid = (intptr_t)arg;
        sem_wait(&full);
        if (sem_wait(&mutex) != 0) {
            printf("Consumer %ld is waiting\n",crid);
        }
        item = consume();
        printf("Consumer %ld consuming item: %d\n",crid,item);
        sleep(2);
        sem_post(&mutex);
        printf("Consumer %ld consumed item: %d\n",crid, item);
        sem_post(&empty);

        sleep(2);  // Sleep to simulate varying consumption times
    }

    return NULL;
}

int main() {
    pthread_t producerThreads[NUM_PRODUCERS], consumerThreads[NUM_CONSUMERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_create(&producerThreads[i], NULL, producer, (void *)(intptr_t)(i + 1));
    }

    // Sleep to allow producers to start producing

    // Create consumer threads after some time
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_create(&consumerThreads[i], NULL, consumer, (void *)(intptr_t)(i + 1));
    }

    // Join threads (not typically done in actual systems)
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producerThreads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
