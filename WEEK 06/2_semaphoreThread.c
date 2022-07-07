// gcc 2_semaphoreThread.c -pthread

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int mutex = 1, full = 0, empty = 3, x = 0;
int main()
{
    int n;
    void *producer(void *arg);
    void *consumer(void *arg);
    int wait(int);
    int signal(int);

    pthread_t producer_id;
    pthread_create(&producer_id, NULL, producer, NULL);

    pthread_t consumer_id;
    pthread_create(&consumer_id, NULL, consumer, NULL);
    pthread_join(producer_id, NULL);
    pthread_join(consumer_id, NULL);
}

int wait(int s)
{
    return (--s);
}
int signal(int s)
{
    return (++s);
}
void *producer(void *arg)
{
    while (1)
    {
        if (mutex == 0)
        {
            printf("\nWaiting for other process");
        }
        else if (empty == 0)
        {
            printf("\nBuffer full");
        }
        else
        {
            mutex = wait(mutex);
            full = signal(full);
            empty = wait(empty);
            x++;
            printf("\nproducer produces the item%d", x);
            mutex = signal(mutex);
        }
        sleep(1);
    }
}

void *consumer(void *arg)
{
    while (1)
    {
        if (mutex == 0)
        {
            printf("\nWaiting for other process");
        }
        else if (full == 0)
        {
            printf("\nBuffer empty");
        }
        else
        {
            mutex = wait(mutex);
            full = wait(full);
            empty = signal(empty);
            printf("\n consumer consumes item%d", x);
            x--;
            mutex = signal(mutex);
        }
        sleep(2);
    }
}