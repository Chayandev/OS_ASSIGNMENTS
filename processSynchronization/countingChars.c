#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>
#define MAX_INPUT 100

//sahred resources
char input[MAX_INPUT];
int charCount=0;
sem_t mutex;
void *countCharacters(void *arg);

int main(){
 pthread_t counterThread;
// Initialize semaphore
    sem_init(&mutex, 0, 1);

 pthread_create(&counterThread,NULL,countCharacters,NULL);
 sem_wait(&mutex); 
 printf("Enter a string (up to %d characters): ",MAX_INPUT-1);
 fgets(input,MAX_INPUT,stdin);
  sem_post(&mutex); 
  pthread_join(counterThread,NULL);
 //Print
  sem_wait(&mutex);
  printf("Number of characters : %d\n",charCount);
  sem_post(&mutex);
  sem_destroy(&mutex);

 return 0;
}


// Thread function to count characters
void* countCharacters(void* arg) {
 sem_wait(&mutex);
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '\n') {
               sleep(2);
               charCount++;
        }
    }
  sem_post(&mutex);
    pthread_exit(NULL);
}
