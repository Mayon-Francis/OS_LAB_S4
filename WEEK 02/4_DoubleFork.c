// C program to demonstrate
// the above concept
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

// Driver code
int main()
{
    printf("Before Forking\n");

    // On the success of a fork() system call:
    //   The Process ID (PID) of the child process is returned to the parent process.
    //   0 is returned to the child process.
    fork();
    // All statements below the (fork) are executed in both parent and child process
    printf("After 1st Forking\n");

    fork();
    // Total four processes are now created
    printf("PID: %d\n", getpid());
    printf("After Second Forking\n");
}
