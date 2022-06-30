// 5   1 1 0 1  2 0 0 1  3 2 0 1  4 1 1 1  5 1 1 1
#include <stdio.h>
#include <stdlib.h>
// To use time library of C
#include <time.h>
  
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
typedef struct {
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
    int remainingBurstTime;
    int waitTime;
    int turnAroundTime;
} process;

process processList[100];

// This will store process data at the end of the schedule loop,
// once the process is removed from the readyQueue
process processDump[100];

int processDumpIndex = -1;
void pushIntoDump(process a) {
    processDumpIndex++;
    processDump[processDumpIndex] = a;
}

void printProcessDump() {
    if(processDumpIndex == -1) {
        printf("\nProcessDump empty\n");
        return;
    }
    printf("\n****ProcessDump****");
    float totalTurnAround = 0;
    float totalWait = 0;
    printf("\n\nPID\tPriority\tArrival\tBurst\tWait\tTurnaround");
    for(int i=0; i<=processDumpIndex; i++) {
        // printf("\n Pid: %d", processDump[i].pid);
        // printf("\n Priority: %d", processDump[i].priority);;
        // printf("\n ArrivalTime: %d", processDump[i].arrivalTime);
        // printf("\n BurstTime: %d", processDump[i].burstTime);
        // printf("\n Wait Time: %d", processDump[i].waitTime);
        // printf("\n Turnaround Time: %d", processDump[i].turnAroundTime);

        printf("\n");
        printf("%d\t%d\t\t%d\t%d\t%d\t%d",
            processDump[i].pid,
            processDump[i].priority,
            processDump[i].arrivalTime,
            processDump[i].burstTime,
            processDump[i].waitTime,
            processDump[i].turnAroundTime
        );
        totalTurnAround += processDump[i].turnAroundTime;
        totalWait += processDump[i].waitTime;
    }

    printf("\n\n Avg Turaround time: %f", (float)totalTurnAround/(processDumpIndex+1));
    printf("\n Avg Wait time: %f \n", (float)totalWait/(processDumpIndex+1));
}

int processCount = 0;
int currentTime = 0;

void removeProcess(int pid) {
    int i;
    for(i=0; i<processCount && processList[i].pid == pid; i++);
    i--;
    if(i < processCount) {
        for(int j=i; j< (processCount-1); j++) {
            processList[j] = processList[j+1];
        }
        processCount--;
    }
}

process readyQueue[200];
int readyQueueStart = -1, readyQueueEnd = -1;

void pushQ(process a) {
    if(readyQueueEnd == -1) {
        readyQueueEnd = 0;
        readyQueueStart = 0;
        readyQueue[readyQueueEnd] = a;
    } else {
        readyQueueEnd++;
        readyQueue[readyQueueEnd] = a;
    }
}

void printReadyQueue() {
    if(readyQueueStart == -1) {
        printf("\nReady Queue empty\n");
        return;
    }
    printf("\n****Ready Processes****");
    for(int i=readyQueueStart; i<=readyQueueEnd; i++) {
        printf("\nPid: %d", readyQueue[i].pid);
        printf("\npriority: %d", readyQueue[i].priority);;
        printf("\narrivalTime: %d", readyQueue[i].arrivalTime);
        printf("\nburstTime: %d", readyQueue[i].burstTime);
        printf("\nRemaining burstTime: %d", readyQueue[i].remainingBurstTime);
    }
}

process popQ() {
    //printf("\n\nBefore Popping \n");
    //printReadyQueue();
    if(readyQueueEnd == -1) {
        printf("Invalid pop");
    } else {
        process popped = readyQueue[0];
        for(int i=0; i<readyQueueEnd; i++) {
            readyQueue[i] = readyQueue[i+1];
            //printf("\n\n\n %d, %d", i, i+1);
        }
        readyQueueEnd--;
        if(readyQueueEnd == -1) {
            readyQueueStart = -1;
        }
        //printf("\n\n After Popping \n");
        //printReadyQueue();
        return popped;
    }
}


void getProcess() {
    printf("Enter process count: ");
    scanf("%d", &processCount);

    for(int i=0; i<processCount; i++) {
        printf("Pid: ");
        scanf("%d", &processList[i].pid);
        printf("priority: ");
        scanf("%d", &processList[i].priority);
        printf("arrivalTime: ");
        scanf("%d", &processList[i].arrivalTime);
        printf("burstTime: ");
        scanf("%d", &processList[i].burstTime);
        processList[i].remainingBurstTime = processList[i].burstTime;
        //printf("\n%d,   %d", processList[i].remainingBurstTime,  processList[i].burstTime );
        processList[i].waitTime = 0;
        processList[i].turnAroundTime = 0;
        printf("\n");
    }
 
}

void printProcess() {
    printf("\n****Processes****");
    for(int i=0; i<processCount; i++) {
        printf("\nPid: %d", processList[i].pid);
        printf("\npriority: %d", processList[i].priority);;
        printf("\narrivalTime: %d", processList[i].arrivalTime);
        printf("\nburstTime: %d", processList[i].burstTime);
    }
}



int compareProcessArrival(const void* argA, const void* argB)
{
    process a = *(const process*) argA;
    process b = *(const process*) argB;
    if (a.arrivalTime < b.arrivalTime) return -1;
    if (a.arrivalTime > b.arrivalTime) return 1;
    return 0;
}
int compareProcessPriority(const void* argA, const void* argB)
{
    process a = *(const process*) argA;
    process b = *(const process*) argB;
    if (a.priority < b.priority) return -1;
    if (a.priority > b.priority) return 1;
    return 0;
}

void insertNewProcessIntoQueue() {
    int i=0;
    while( i < processCount && processList[i].arrivalTime <= currentTime) {
        pushQ(processList[i]);
        i++;
    }
    for (int j=0; j<i; j++) {
        removeProcess(processList[j].pid);
    }
    qsort(readyQueue, readyQueueEnd-readyQueueStart, sizeof(process), compareProcessPriority);
}
void scheduler() {
    //printf("\nInitial\n");
    //printProcess();
    qsort(processList, processCount, sizeof(process), compareProcessArrival);
    insertNewProcessIntoQueue();
    //printProcess();
    //printReadyQueue();
    while(readyQueueStart != -1) {
        qsort(readyQueue, readyQueueEnd-readyQueueStart, sizeof(process), compareProcessPriority);
        //printf("\nRemaining of %d: %d",readyQueue[0].pid,readyQueue[0].remainingBurstTime);
        readyQueue[0].remainingBurstTime--;
        //printf("\nRemaining of %d: %d",readyQueue[0].pid, readyQueue[0].remainingBurstTime);
        if(readyQueue[0].remainingBurstTime == 0) {
            process popped = popQ();
            //printf("\nPopped  %d: %d",popped.pid,popped.remainingBurstTime);
            popped.turnAroundTime = popped.burstTime + popped.waitTime;
            pushIntoDump(popped);
            //printReadyQueue();
            for(int i=0; i<=readyQueueEnd; i++) {
                readyQueue[i].waitTime++;
            }
        } else {
            for(int i=1; i<=readyQueueEnd; i++) {
                readyQueue[i].waitTime++;
            }
        }
        //printProcess();
        //printProcessDump();
        //delay(100);
        currentTime ++;
        insertNewProcessIntoQueue();
    }
    //printf("\n\nSCHEDULING OVER\n\n!");
    printProcessDump();
}

int  main() {
    getProcess();
    scheduler();
    return 0;
}