#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Added for sleep function
#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5

void dine(void *ptr);
pthread_t philosopher[NUM_PHILOSOPHERS];
pthread_mutex_t chopstick[NUM_CHOPSTICKS];

int main()
{
  // Define counter var i and status_message
  int i, status_message;
  void *msg;

  // Initialise the semaphore array
  for (i = 0; i < NUM_CHOPSTICKS; i++) // Changed initialization loop
  {
    status_message = pthread_mutex_init(&chopstick[i], NULL);
    // Check if the mutex is initialised successfully
    if (status_message != 0) // Changed condition
    {
      printf("\n Mutex initialization failed");
      exit(1);
    }
  }

  // Run the philosopher Threads using *dine() function
  for (i = 0; i < NUM_PHILOSOPHERS; i++) // Changed loop condition
  {
    status_message = pthread_create(&philosopher[i], NULL, (void *)dine, (void *)(intptr_t)i); // Cast i to void pointer
    if (status_message != 0)
    {
      printf("\n Thread creation error \n");
      exit(1);
    }
  }

  // Wait for all philosophers threads to complete executing (finish dining) before closing the program
  for (i = 0; i < NUM_PHILOSOPHERS; i++) // Changed loop condition
  {
    status_message = pthread_join(philosopher[i], &msg);
    if (status_message != 0)
    {
      printf("\n Thread join failed \n");
      exit(1);
    }
  }

  // Destroy the chopstick Mutex array
  for (i = 0; i < NUM_CHOPSTICKS; i++) // Changed loop condition
  {
    status_message = pthread_mutex_destroy(&chopstick[i]);
    if (status_message != 0)
    {
      printf("\n Mutex Destroyed \n");
      exit(1);
    }
  }
  return 0;
}

void dine(void *ptr) // Changed function signature
{
  int n = (intptr_t)ptr; // Cast back to int

  printf("\nPhilosopher %d is thinking ", n);

  // Philosopher picks up the left chopstick (wait)
  pthread_mutex_lock(&chopstick[n]);

  // Philosopher picks up the right chopstick (wait)
  pthread_mutex_lock(&chopstick[(n + 1) % NUM_CHOPSTICKS]);

  // After picking up both the chopsticks, the philosopher starts eating
  printf("\nPhilosopher %d is eating ", n);
  sleep(3);

  // Philosopher places down the left chopstick (signal)
  pthread_mutex_unlock(&chopstick[n]);

  // Philosopher places down the right chopstick (signal)
  pthread_mutex_unlock(&chopstick[(n + 1) % NUM_CHOPSTICKS]);

  // Philosopher finishes eating
  printf("\nPhilosopher %d Finished eating ", n);
}


