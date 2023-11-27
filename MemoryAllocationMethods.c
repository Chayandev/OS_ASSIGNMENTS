#include <stdio.h>
void printAllocation(int allocation[100], int process[100], int np)
{
    printf("\nProcess No.\tProcess size\tAllocation block no\n");
    for (int i = 0; i < np; i++)
    {
        printf("%d\t\t", i);
        printf("%d\t\t", process[i]);
        if (allocation[i] == -1)
        {
            printf("Not allowed");
        }
        else
        {
            printf("%d", allocation[i]);
        }

        printf("\n");
    }
}
void firstFitAllocation(int process[100], int mblocks[100], int np, int nb)
{
    int allocation[100];
    int p = 0, flag = 0;
    for (int p = 0; p < np; p++)
    {
        flag = 0;
        for (int b = 0; b < nb; b++)
        {
            if (process[p] <= mblocks[b])
            {
                allocation[p] = b;
                mblocks[b] -= process[p];
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            allocation[p] = -1;
        }
    }

    // printitng
    printAllocation(allocation, process, np);
}
void bestFitAllocation(int process[100], int mblocks[100], int np, int nb)
{
    int allocation[100];
    int fitLoc, flag;
    for (int p = 0; p < np; p++)
    {
        fitLoc = -1;
        flag = 0;
        for (int b = 0; b < nb; b++)
        {
            if (process[p] <= mblocks[b])
            {
                if (fitLoc == -1)
                    fitLoc = b;
                else
                {
                    if (mblocks[b] < mblocks[fitLoc])
                        fitLoc = b;
                }
            }
        }
        allocation[p] = fitLoc;
        if (fitLoc != -1)
        {
            mblocks[fitLoc] -= process[p];
        }
    }

    printAllocation(allocation, process, np);
}
void worstFitAllocation(int process[100], int mblocks[100], int np, int nb)
{
    int allocation[100];
    int fitLoc, flag;
    for (int p = 0; p < np; p++)
    {
        fitLoc = -1;
        flag = 0;
        for (int b = 0; b < nb; b++)
        {
            if (process[p] <= mblocks[b])
            {
                if (fitLoc == -1)
                    fitLoc = b;
                else
                {
                    if (mblocks[b] > mblocks[fitLoc])
                        fitLoc = b;
                }
            }
        }
        allocation[p] = fitLoc;
        if (fitLoc != -1)
        {
            mblocks[fitLoc] -= process[p];
        }
    }

    printAllocation(allocation, process, np);
}
int main()
{
    int np, nb, process[100], mblocks[100];
    printf("Enter the number of memory blocks:");
    scanf("%d", &nb);
    for (int i = 0; i < nb; i++)
    {
        printf("Enter the size of the memory block %d:", i);
        scanf("%d", &mblocks[i]);
    }
    printf("Enter the number of process:");
    scanf("%d", &np);
    for (int i = 0; i < np; i++)
    {
        printf("Enter the size of the process %d:", i);
        scanf("%d", &process[i]);
    }

    // copy of memory

    int copy1P[100], copy1MB[100], copy2P[100], copy2MB[100];
    for (int i = 0; i < np; i++)
    {
        copy1P[i] = process[i];
        copy2P[i] = process[i];
    }
    for (int i = 0; i < nb; i++)
    {
        copy1MB[i] = mblocks[i];
        copy2MB[i] = mblocks[i];
    }
    firstFitAllocation(process, mblocks, np, nb);
    bestFitAllocation(copy1P, copy1MB, np, nb);
    worstFitAllocation(copy2P, copy2MB, np, nb);
    return 0;
}