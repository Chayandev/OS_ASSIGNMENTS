#include <stdio.h>
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
    int vowelsCount;
    char vowels[] = "aeiouAEIOU";

    // Generate a unique key
    key = ftok("sender.c", 'a');

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    for (int i = 0; i < MAX_STRINGS; ++i) {
        // Receive strings from the message queue
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        vowelsCount = 0;

        // Count vowels in the received string
        for (int j = 0; j < strlen(message.msg_text); ++j) {
            if (strchr(vowels, message.msg_text[j])) {
                vowelsCount++;
            }
        }

        // Convert vowel count to string and send back to sender
        sprintf(message.msg_text, "%d", vowelsCount);
        message.msg_type = 2;
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    return 0;
}