#include <stdio.h>
void sortProcess_burstTime(int processes[],int burstTime[],int n){
        // Sort processes based on burst time
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (burstTime[j] > burstTime[j + 1]) {
                // Swap burst time
                int tempBurst = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = tempBurst;

                // Swap process ID
                int tempProcess = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempProcess;
            }
        }
    }
}
// Function to calculate turnaround time, waiting time
void calculateTimes(int processes[], int n, int burstTime[],int arrivalTime[], int completionTime[], int turnaroundTime[], int waitingTime[]) {
    int currentTime = 0;
    sortProcess_burstTime(processes,burstTime,n);
    for (int i = 0; i < n; ++i) {
        // Calculate completion time
        completionTime[i] = currentTime + burstTime[i];

        // Calculate turnaround time
        turnaroundTime[i] = completionTime[i]-arrivalTime[i];

        // Calculate waiting time
        waitingTime[i] = currentTime;

        currentTime = completionTime[i];
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
    // Number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Arrays to store process details
    int processes[n];
    int arrivaTime[n];
    int burstTime[n];
    int completionTime[n];
    int turnaroundTime[n];
    int waitingTime[n];

    // Input process details
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; ++i) {
        processes[i] = i + 1;
        arrivaTime[i]=0;
        printf("Process %d:\n", processes[i]);
        printf("Burst Time: ");
        scanf("%d", &burstTime[i]);
    }

    // Calculate times
    calculateTimes(processes, n, burstTime,arrivaTime, completionTime, turnaroundTime, waitingTime);

    // Display process details
    displayProcesses(processes, n, burstTime,arrivaTime, completionTime, turnaroundTime, waitingTime);

    return 0;
}
