#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT_SIZE 100
#define MAX_STRINGS 10

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_TEXT_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
    char strings[MAX_STRINGS][MAX_TEXT_SIZE] = {"Hello", "World", "This", "Is", "Sambit", "Sarkar", "Student", "Of", "RCC", "Beleghata"};

    // Generate a unique key
    key = ftok("sender.c", 'a');

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;

    // Send strings to the message queue
    for (int i = 0; i < MAX_STRINGS; ++i) {
        strcpy(message.msg_text, strings[i]);
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    printf("Strings sent to receiver.\n");

    // Receive vowel counts from the receiver
    for (int i = 0; i < MAX_STRINGS; ++i) {
        msgrcv(msgid, &message, sizeof(message), 2, 0);
        printf("Vowels count in string %d: %s\n", i+1, message.msg_text);
    }

    // Close the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}