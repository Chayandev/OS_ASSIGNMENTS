
#include<stdio.h>
// Function to perform Round Robin scheduling
void roundRobin(int process[],int n,int burstTime[],int waitingTime[],int completionTime[],int turnarroundTime[],int timeQuantum) {
    int remainingTime[n]; // Array to store remaining time for each process

    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
    }

    int currentTime = 0; // Current time
    int remainingProcesses = n; // Number of remaining processes

    // Iterate until all processes are completed
    while (remainingProcesses > 0) {
        for (int i = 0; i < n; i++) {
            // If the process is not completed
            if (remainingTime[i] > 0) {
                // Execute the process for the time quantum or until completion
                if (remainingTime[i] <= timeQuantum) {
                    // Process completes within the time quantum
                    currentTime += remainingTime[i];
                    remainingTime[i] = 0;
                } else {
                    // Process still has remaining time
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                }
                if(remainingTime[i]==0){
                // Update remainingProcesses
                remainingProcesses--;
                completionTime[i]=currentTime;
                }
            }
        }
    }
    
    for(int i=0;i<n;i++){
        turnarroundTime[i]=completionTime[i];
        waitingTime[i]=turnarroundTime[i]-burstTime[i];
    }
}

// Function to display the process details
void displayProcesses(int processes[], int n, int burstTime[],int arrivaTime[], int completionTime[], int turnaroundTime[], int waitingTime[]) {
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; ++i) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i],arrivaTime[i],burstTime[i],completionTime[i], turnaroundTime[i],waitingTime[i]);
    }
}
int main() {
    int n, timeQuantum;

    // Get the number of processes and time quantum from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    int burstTime[n];
    int process[n];
    int completionTime[n];
    int waitingTime[n];
    int turnarroundTime[n];
    int arrivaTime[n];
   // int responseTime[n];
    
    // Get burst time for each process from the user
    for (int i = 0; i < n; i++) {
        process[i]=i+1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        arrivaTime[i]=0;
    }

    // Perform Round Robin scheduling
    roundRobin(process,n, burstTime,waitingTime,completionTime,turnarroundTime, timeQuantum);

   // Display process details
    displayProcesses(process, n, burstTime,arrivaTime, completionTime, turnarroundTime, waitingTime);

// Calculate and display average turnaround time and average waiting time
    float avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (int i = 0; i < n; ++i) {
        avgTurnaroundTime += turnarroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime /= n;
    avgWaitingTime /= n;

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}

