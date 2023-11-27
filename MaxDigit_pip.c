#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// some macros to make the code more understandable
//  regarding which pipe to use to a read/write operation
//
//  Parent: reads from P1_READ, writes on P1_WRITE
//  Child:  reads from P2_READ, writes on P2_WRITE
#define P1_READ 0
#define P2_WRITE 1
#define P2_READ 2
#define P1_WRITE 3

// the total number of pipe pairs we need
#define NUM_PIPES 2

#define SIZE 10

int main(int argc, char *argv[])
{
    int fd[2 * NUM_PIPES];
    int val[SIZE];
    int len, highest = 0;
    pid_t pid;

    // create all the descriptor pairs we need
    for (int i = 0; i < NUM_PIPES; ++i)
    {
        if (pipe(fd + (i * 2)) < 0)
        {
            perror("Failed to allocate pipes");
            exit(EXIT_FAILURE);
        }
    }

    // fork() returns 0 for child process, child-pid for parent process.
    if ((pid = fork()) < 0)
    {
        perror("Failed to fork process");
        return EXIT_FAILURE;
    }

    // if the pid is zero, this is the child process
    if (pid == 0)
    {
        // Child. Start by closing descriptors we
        //  don't need in this process
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);

        // used for output
        pid = getpid();

        // wait for parent to send us a value
        len = read(fd[P2_READ], &val, sizeof(val));
        if (len < 0)
        {
            perror("Child: Failed to read data from pipe");
            exit(EXIT_FAILURE);
        }
        else if (len == 0)
        {
            // not an error, but certainly unexpected
            fprintf(stderr, "Child: Read EOF from pipe");
        }
        else
        {
            // report what we received
            //printf("Child(%d): Received \n", pid);

            // now double it and send it back
            // val *= 2;

            for (int i = 0; i < SIZE; i++)
            {
                if (val[i] > highest)
                {
                    highest = val[i];
                }
            }
            //printf("Child(%d): Sending %dback\n", pid, highest);
            if (write(fd[P2_WRITE], &highest, sizeof(highest)) < 0)
            {
                perror("Child: Failed to write response value");
                exit(EXIT_FAILURE);
            }
        }

        // finished. close remaining descriptors.
        close(fd[P2_READ]);
        close(fd[P2_WRITE]);

        return EXIT_SUCCESS;
    }

    // Parent. close unneeded descriptors
    close(fd[P2_READ]);
    close(fd[P2_WRITE]);

    // used for output
    pid = getpid();

    // send a value to the child
    // val = 42;
    printf("Sending 10 numbers: \n");
    for (int i = 0; i < SIZE; i++)
    {
        val[i] = (rand() % 100) + (rand() % 100);
        printf("%d ", val[i]);
    }
    // printf("Parent(%d): Sending %d to child\n", pid, val);
    if (write(fd[P1_WRITE], &val, sizeof(val)) != sizeof(val))
    {
        perror("Parent: Failed to send value to child ");
        exit(EXIT_FAILURE);
    }

    // now wait for a response
    len = read(fd[P1_READ], &highest, sizeof(highest));
    if (len < 0)
    {
        perror("Parent: failed to read value from pipe");
        exit(EXIT_FAILURE);
    }
    else if (len == 0)
    {
        // not an error, but certainly unexpected
        fprintf(stderr, "Parent(%d): Read EOF from pipe", pid);
    }
    else
    {
        // report what we received
        printf("Parent(%d): Received %d\n", pid, highest);
    }

    // close down remaining descriptors
    close(fd[P1_READ]);
    close(fd[P1_WRITE]);

    // wait for child termination
    wait(NULL);

    return EXIT_SUCCESS;
}