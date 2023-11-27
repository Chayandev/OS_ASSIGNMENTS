#include <stdio.h>
#include <stdlib.h>
int mutex = 1;
int full = 0;
int empty = 3;
int x = 0;

int wait(int s)
{
    return (--s);
}
int signal(int s)
{
    return (++s);
}

void producer()
{
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    x++;
    printf("\n producer produces the item %d", x);
    mutex = signal(mutex);
}

void consumer()
{
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("\n Consumer cunsumes item %d", x);
    x--;
    mutex = signal(mutex);
}

int main()
{
    int n;
    printf("Press any one ");
    printf("\n 1.PRODUCER \n 2.CONSUMER \n 3.EXIT \n");
    while (1)
    {
        printf("\n Enter your choice : \n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            if (mutex == 1 && empty != 0)
                producer();
            else
                printf("Buffer Is FULL");
            break;
        case 2:
            if (mutex == 1 && full != 0)
                consumer();
            else
                printf("BUFFER IS EMPTY");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
