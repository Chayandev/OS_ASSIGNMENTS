#include <stdio.h>
#include <stdlib.h>
int findSafeSequence(int allocation[100][100],int need[100][100],int available[1][100],int np,int nr){
    int state[100];
    for (int i = 0; i < np; i++) {
        state[i] = 0; // Initialize state array
    }

    int temp = np;
    int safeSequence[100]; // To store the safe sequence
    int k = 0; // To keep track of the safe sequence index

    // Safety algorithm to find a safe sequence
    while (temp) {
        int found = 0; // Flag to indicate if a safe sequence is found in this iteration
        
        for (int i = 0; i < np; i++) {
            if (state[i] == 0) {
                int flag = 1;
                
                for (int j = 0; j < nr; j++) {
                    if (need[i][j] > available[0][j]) {
                        flag = 0;
                        break;
                    }
                }
                
                if (flag == 1) {
                    // Allocate resources
                    for (int j = 0; j < nr; j++) {
                        available[0][j] += allocation[i][j];
                    }
                    state[i] = 1; // Mark process as completed
                    safeSequence[k++] = i; // Add process to the safe sequence
                    temp--;
                    found = 1; // A safe sequence was found in this iteration
                }
            }
        }
        
        if (found == 0) {
            // If no safe sequence is found in this iteration, break to avoid an infinite loop
            printf("No safe sequence found. The system is in an unsafe state.\n");
            return 0;
        }
    }
    
    if (temp == 0) {
        // If all processes are in the safe sequence, print it
        printf("Safe Sequence: ");
        for (int i = 0; i < np; i++) {
            printf("%d", safeSequence[i]);
            if (i < np - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
        return 1;
    }
    return 0;
}
void resourceRequest(int allocation[100][100], int need[100][100], int available[1][100], int np, int nr, int process) {
    int request[100];
    
    printf("Enter the resource request for process %d: ", process);
    for (int i = 0; i < nr; i++) {
        scanf("%d", &request[i]);
    }
    
    // Check if the request is valid
    for (int i = 0; i < nr; i++) {
        if (request[i] > need[process][i] || request[i] > available[0][i]) {
            printf("Invalid request. Process %d is requesting more resources than needed or available.\n", process);
            return;
        }
    }
    
    // Temporarily allocate the resources
    for (int i = 0; i < nr; i++) {
        available[0][i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    
    if(findSafeSequence(allocation,need,available,np,nr)==0){
        for (int i = 0; i < nr; i++){
        available[0][i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }
   }else{
       printf("Hence the new system state is safe, so we can immediately grant the request for process  %d.",process);
   }
   
}

int main() {
    int allocation[100][100], maxNeed[100][100], available[1][100], need[100][100];
    
    printf("Enter the number of processes: ");
    int np;
    scanf("%d", &np);
    
    printf("Enter the number of resources: ");
    int nr;
    scanf("%d", &nr);
    
    printf("Enter the allocations...\n");
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max needs...\n");
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            scanf("%d", &maxNeed[i][j]);
        }
    }

    printf("Enter the Available counts...\n");
    for (int i = 0; i < nr; i++) {
        scanf("%d", &available[0][i]);
    }

    //store the initial avialable
    int initalAvailabe[1][100];
    for(int i=0;i<nr;i++){
        initalAvailabe[0][i]=available[0][i];
    }
    // Calculate the need matrix
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nr; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }
    findSafeSequence(allocation,need,available,np,nr);
    
    //new request
    int process;
    printf("Enter the process requesting resources: ");
    scanf("%d", &process);
    resourceRequest(allocation, need, initalAvailabe, np, nr, process);

    return 0;
}
