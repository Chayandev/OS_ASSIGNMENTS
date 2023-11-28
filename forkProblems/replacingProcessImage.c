#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>

int main(){

pid_t p;
p=fork();
if(p<0){
   printf("Fork Faild");
}
else if(p==0){
    printf("I'm child having id %d\n",getpid());
    execl("/bin/ls","ls","-l",NULL); //replace child process with ls 
    perror("execlp failed"); 
    
    //just for  calrification
    printf("This is the child process code,which will not ececute beacuse of replacement\n");
   //sleep(10);

}else{
    printf("I'm Pratent having id %d\n",getpid());
    wait(NULL);  
    printf("Parent process completed");
  
}

return 0;
}
