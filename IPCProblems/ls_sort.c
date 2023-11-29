#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
int fd[2];
if(pipe(fd) == -1) {
perror("ERROR creating a pipe\n");
exit(1);
}
if (!fork()) {
close(1); // close the standard output file
dup(fd[1]); // now fd[1] (the writing end of the pipe) is the standard output
close(fd[0]); // I am the writer. So, I don’t need this fd
execlp("ls", "ls", NULL);
}
else {
close(0); // close the standard input file
dup(fd[0]);
close(fd[1]);
execlp("sort", "sort", NULL);
}
return(0);
}
