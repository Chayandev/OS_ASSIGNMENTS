#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
int main()
{
pid_t q;
printf("before fork\n");
q=fork();

if(q<0){
printf("Child process creation failed");
}
else if(q==0){
/*
pid_t p=fork();
printf("I'm in first fork\n");
if(p==0){
  printf("i'm 2nd child having id %d\n",getpid());
  printf("My parent's id is %d\n",getppid());
}else{
*/
 //sleep(3); //go sleep for 3 sec
 printf("Im child having id %d\n",getpid());
 printf("My parent's Id %d\n",getppid());
//}

}else{
 wait(NULL); //use this wait inside parent process to wait for the execution of it's child first dont't
// use this in child , it will wait  for its own child.
 printf("My child's id is %d\n",q);
 printf("I'm parent having id %d\n",getpid());

}

return 0;

}
