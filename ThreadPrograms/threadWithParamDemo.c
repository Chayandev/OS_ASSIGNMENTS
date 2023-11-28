#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thread_function(void *arg);
int i,j,n;
int arr[2]={6,7};
int main(){

void *result;

pthread_t a_thread; //thread deeclaration
pthread_create(&a_thread,NULL,thread_function,(void*)arr); //thread is created
pthread_join(a_thread, &result);//process waits for thread to finish.

printf("Inside Main Program\n");
printf("Thread returned : %ld",(intptr_t)result);

}

void *thread_function(void *arg){ //the work to be done  by the thread is deifned in this function

printf("Inside thread\n");
 int *x=arg;
 int sum=x[0]+x[1];
 printf("Sum is %d\n",sum);
// pthread_exit("Sum calculated");
   pthread_exit((void*)(intptr_t)sum);
}
