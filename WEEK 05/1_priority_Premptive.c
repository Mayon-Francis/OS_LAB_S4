// 5   1 1 0 1  2 0 0 1  3 2 0 1  4 1 1 1  5 1 1 1
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
    int waitTime;
    int turnAroundTime;
} process;

process processList[100];
int processCount = 0;
int currentTime = 0;

void removeProcess(int pid) {
    int i;
    for(i=0; i<processCount && processList[i].pid == pid; i++);
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
void popQ(process a) {
    if(readyQueueEnd == -1) {
        printf("Invalid pop");
    } else {
        for(int i=0; i<readyQueueEnd-1; i++) {
            readyQueue[i] = readyQueue[i+1];
        }
        readyQueueEnd--;
        if(readyQueueEnd == -1) {
            readyQueueStart = -1;
        }
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
    printf("\nInitial\n");
    printProcess();
    qsort(processList, processCount, sizeof(process), compareProcessArrival);
    insertNewProcessIntoQueue();
    printProcess();
    printReadyQueue();
    while(readyQueueStart != -1) {
        qsort(readyQueue, readyQueueEnd-readyQueueStart, sizeof(process), compareProcessPriority);
        // TODO: Execute a process and pop from Q
        currentTime ++;
        insertNewProcessIntoQueue();
        printProcess();
        printReadyQueue();
    }
}

int  main() {
    getProcess();
    scheduler();
    return 0;
}