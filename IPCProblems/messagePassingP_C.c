#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 100

int main(){
  int fd[2],n;
  char buffer[BUFFER_SIZE];
  pid_t newP;

  if(pipe(fd)==-1){
    printf("Pipe creation failed\n");
  }
  
  newP=fork();

  if(newP<0){
    printf("Fork creation failed\n");
  }else if(newP==0){
    printf("Inside child process\n");
    close(fd[1]); // child read from the pipe , close the write end
    
    n=read(fd[0],buffer,BUFFER_SIZE);
    write(1,buffer,n);

    close(fd[0]);
  }else{
    close(fd[0]); // Close the read end of the pipe (parent writes to the pipe)
      
     const char* parentMessage = "Hello from Parent!";
     write(fd[1], parentMessage, strlen(parentMessage) + 1);

     // Close the write end of the pipe
      close(fd[1]);

     // Wait for the child to finish
      wait(NULL);

      printf("\nParent Process: Message Sent to Child.\n");

  }

  return 0;
}
