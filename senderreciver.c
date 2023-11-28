#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>

struct messageQueue
{
    long messageType;
    char messageText[50];
};

struct sharedMemory
{
    int vowelCounts[5];
};

void sender(int msgqid, int shmid)
{
    struct messageQueue message;
    struct sharedMemory *sharedMemory;
    
    printf("\nEnter strings:\n");
    for (int i = 0; i < 5; i++)
    {
        scanf("%s", message.messageText);
        message.messageType = i + 1;

        msgsnd(msgqid, &message, sizeof(message.messageText), 0);
    }
    sharedMemory = (struct sharedMemory *)shmat(shmid, NULL, 0);

    printf("\nThe vowel counts are:");
    for (int i = 0; i < 5; i++)
    {
        printf(" %d", sharedMemory->vowelCounts[i]);
    }

    shmdt(sharedMemory);
}

void receiver(int msgqid, int shmid)
{
    struct messageQueue message;
    struct sharedMemory *sharedMemory;

    sharedMemory = (struct sharedMemory *)shmat(shmid, NULL, 0);

    for (int i = 0; i < 5; i++)
    {
        msgrcv(msgqid, &message, sizeof(message.messageText), i + 1, 0);

        int vowels = 0;
        for (int j = 0; j < strlen(message.messageText); j++)
        {
            char c = message.messageText[j];
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            {
                vowels++;
            }
        }

        sharedMemory->vowelCounts[i] = vowels;
    }

    shmdt(sharedMemory);
}

int main()
{
    key_t key = ftok(".", 'a');

    int msgqid = msgget(key, 0666 | IPC_CREAT);
    if (msgqid == -1)
    {
        printf("\nMessage queue creation failed");
        return 1;
    }

    int shmid = shmget(key, sizeof(struct sharedMemory), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        printf("\nShared memory creation failed");
        return 1;
    }

    int pid = fork();

    if (pid > 0)
    {
        sleep(2);
        sender(msgqid, shmid);
    }
    else if (pid == 0)
    {
        receiver(msgqid, shmid);
    }
    else
    {
        printf("\nFork failed");
        return 1;
    }

    msgctl(msgqid, IPC_RMID, NULL);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
