#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *factorial_thread_function(void *arg);//thread for factorial calc
void *reverseNum_thread_function(void *arg); //thread for reverse number calc

int main(){
int n1=5,n2=6895;
void *fact_res,*reverse_res;
pthread_t fact_thread,revnum_thread;

pthread_create(&fact_thread,NULL,factorial_thread_function,(void *)&n1);
pthread_create(&revnum_thread,NULL,reverseNum_thread_function,(void *)&n2);

pthread_join(fact_thread,&fact_res);
pthread_join(revnum_thread,&reverse_res);

printf("Factorial of %d is %ld\n",n1,(intptr_t)fact_res);
printf("Reverse of %d is %ld\n",n2,(intptr_t)reverse_res);

return 0;
}
void *factorial_thread_function(void *arg){ //the work to be done  by the thread is deifned in this function
 int *x=(int *)arg;
 int n=*x;
 int res=1;
 if(n<=1){
  pthread_exit((void*)(intptr_t)1);
 }else{
   while(n!=0){
     res*=n;
     n--;
   }
 }
pthread_exit((void*)(intptr_t)res);
}
void *reverseNum_thread_function(void *arg){ //the work to be done  by the thread is deifned in this function
 int *x=(int *)arg;
 int n=*x;
 int res=0;
   while(n!=0){
     res=(res*10)+(n%10);
     n=n/10;
   }
pthread_exit((void*)(intptr_t)res);
}
