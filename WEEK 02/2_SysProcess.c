#include <stdio.h>
#include <unistd.h>
main()
{
    int pid, pid1, pid2;

    // On the success of a fork() system call:
    //   The Process ID (PID) of the child process is returned to the parent process.
    //   0 is returned to the child process.
    pid = fork();
    // All statements below the (fork) are executed in both parent and child process

    if (pid == -1)
    {
        printf("ERROR IN PROCESS CREATION \n");
        exit(1);
    }
    if (pid != 0) // parent
    {
        pid1 = getpid();
        printf("\n the parent process ID is % d\n", pid1);
    }
    else // child
    {
        pid2 = getpid();
        printf("\n the child process ID is % d\n", pid2);
    }
}