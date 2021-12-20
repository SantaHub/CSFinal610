#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define thread_count 10
#define ASCIIs 127
#define atmost 1000

char stringInput[atmost + 1];
int count[ASCIIs], h;
pthread_mutex_t mutex[ASCIIs];

void *task(void *rank);

int main()
{
    pthread_t *thread_handles;
    int i;

    // Assign count by 0
    for (i = 0; i < ASCIIs; i++)
    {
        count[i] = 0;
    }

    // prompt user to enter a line
    printf("Please enter a line not larger than 100 characters. \n");
    fgets(stringInput, 100, stdin);
    printf("Thread creating");

    // if length is less than process, add more space to string to match thread count divisor.
    int stringLength = strlen(stringInput);
    if (stringLength % thread_count != 0)
    {

        int extraSpaceNeeded = thread_count - (stringLength % thread_count);

        for (int charIndex = 0; charIndex < extraSpaceNeeded; charIndex++)
        {
            strcat(stringInput, " ");
        }
    }

    h = strlen(stringInput) / thread_count;

    thread_handles = malloc(h * sizeof(pthread_t));
    printf("Creating Threading");

    /* Creating the threads */
    for (long threadIndex = 0; threadIndex < thread_count; threadIndex++)
    {
        pthread_mutex_init(&mutex[threadIndex], NULL);
        pthread_create(&thread_handles[threadIndex], NULL, task, (void *)threadIndex);

        pthread_join(thread_handles[threadIndex], NULL);
        pthread_mutex_destroy(&mutex[threadIndex]);
    }

    printf("Threads joined and destroyed");

    for (int i = 33; i < ASCIIs; i++)
    {
        if (count[i] != 0)
            printf("Number of %c is: %d \n", i, count[i] / thread_count);
    }

    free(thread_handles);
    pthread_exit(NULL);

    return 0;
}

void *task(void *rank)
{
    pthread_mutex_lock(mutex);
    for (int index = 0; index < strlen(stringInput); index++)
    {
        int position = (int)stringInput[index];
        count[position]++;
    }
    pthread_mutex_unlock(mutex);

    return NULL;
}