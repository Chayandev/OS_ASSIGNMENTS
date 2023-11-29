#include <stdio.h>
// Function to calculate turnaround time, waiting time, and response time
void calculateTimes(int processes[], int n, int arrivalTime[], int burstTime[], int completionTime[], int turnaroundTime[], int waitingTime[], int responseTime[]) {
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        // Calculate completion time
        completionTime[i] = currentTime + burstTime[i];

        // Calculate turnaround time
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];

        // Calculate waiting time
        waitingTime[i] = turnaroundTime[i] - burstTime[i];

        // Calculate response time (for the first process, response time is the same as waiting time)
        responseTime[i] = (i == 0) ? waitingTime[i] : completionTime[i-1];

        currentTime = completionTime[i];
    }
}

// Function to display the process details
void displayProcesses(int processes[], int n, int arrivalTime[], int burstTime[], int completionTime[], int turnaroundTime[], int waitingTime[], int responseTime[]) {
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");

    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrivalTime[i],
               burstTime[i], completionTime[i], turnaroundTime[i],
               waitingTime[i], responseTime[i]);
    }
}

int main() {
    // Number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Arrays to store process details
    int processes[n];
    int arrivalTime[n];
    int burstTime[n];
    int completionTime[n];
    int turnaroundTime[n];
    int waitingTime[n];
    int responseTime[n];

    // Input process details
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; ++i) {
        processes[i] = i + 1;
        arrivalTime[i] = 0; // Arrival time is set to 0
        printf("Process %d:\n", processes[i]);
        printf("Burst Time: ");
        scanf("%d", &burstTime[i]);
    }

    // Calculate times
    calculateTimes(processes, n, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime, responseTime);

    // Display process details
    displayProcesses(processes, n, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime, responseTime);

    // Calculate and display average turnaround time and average waiting time
    float avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (int i = 0; i < n; ++i) {
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime /= n;
    avgWaitingTime /= n;

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}
