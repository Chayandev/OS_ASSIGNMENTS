#include<stdio.h>
#include<limits.h>

int main(){
    int p, arrival[50], priority[50], burst[50], turnaround[50], waiting[50], clock = 0, bt[50];
    float avgta, avgwt;

    printf("\nEnter no of process: ");
    scanf("%d", &p);

    printf("\nEnter arrival times: ");
    for(int i = 0; i < p; i++) scanf("%d", &arrival[i]);
    
    printf("\nEnter priorities: ");
    for(int i = 0; i < p; i++) scanf("%d", &priority[i]);

    printf("\nEnter burst time: ");
    for(int i = 0; i < p; i++){
        scanf("%d", &burst[i]);
        bt[i] = burst[i];
    }

    int flag = 0;
    while(flag < p){
        int pid = -1;
        int pr = INT_MAX;

        for(int i = 0; i < p; i++){
            if(arrival[i] <= clock && priority[i] < pr && bt[i] != 0){
                pid = i;
                pr = priority[i];
            }
        }

        clock = clock + bt[pid];
        bt[pid] = 0;
        turnaround[pid] = clock - arrival[pid];
        waiting[pid] = turnaround[pid] - burst[pid];
        flag++;
    }

    int totaltt = 0;
    int totalwt = 0;
    for(int i = 0; i < p; i++){
        totaltt += turnaround[i];
        totalwt += waiting[i];
    }

    avgta = totaltt * 1.0/p;
    avgwt = totalwt * 1.0/p;

    printf("\nProcess\tArrival\tPriority\tBurst\tTurnaround\tWaiting\n");
    for(int i = 0; i < p; i++) printf("%d\t%d\t%d\t\t%d\t%d\t\t%d\n", i, arrival[i], priority[i], burst[i], turnaround[i], waiting[i]);

    printf("\nAverage turn around time: %.2f", avgta);
    printf("\nAverage waiting time: %.2f", avgwt);

    return 0;
}
