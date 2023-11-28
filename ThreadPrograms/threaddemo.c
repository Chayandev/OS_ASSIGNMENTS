#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thread_function(void *arg);
int i,j,n;

int main(){

pthread_t a_thread; //thread deeclaration
pthread_create(&a_thread,NULL,thread_function,NULL); //thread is created
//pthread_join(a_thread,NULL);//process waits for thread to finish.

printf("Inside the main Program\n");
for(int i=10;i<15;i++){
printf("%d\n",i);
sleep(1);
}

}

void *thread_function(void *arg){ //the work to be done  by the thread is deifned in this function

printf("Inside thread\n");
    for(int i=0;i<5;i++){ 
        printf("%d\n",i);
        sleep(1);
 }
 pthread_exit(NULL);
}


//note:- to compile the thread program comand "gcc filename.c -lpthread"
