#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thread_function(void *arg);

int main(){

pthread_t new_thread; //thread deeclaration
pthread_create(&new_thread,NULL,thread_function,NULL); //thread is created
  
// Print thread and process IDs of the main thread
printf("Main Thread ID: %lu\n", pthread_self());
printf("Main Process ID: %d\n", getpid());

pthread_join(new_thread,NULL);//process waits for thread to finish.

return 0;

}

void *thread_function(void *arg){ //the work to be done  by the thread is deifned in this function
  // Print thread and process IDs of the new thread
    printf("New Thread ID: %lu\n", pthread_self());
    printf("New Process ID: %d\n", getpid());

    pthread_exit(NULL);
}
