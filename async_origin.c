#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define thread_count 10
#define ASCIIs 127
#define atmost 1000

char letters[atmost + 1];
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
    fgets(letters, 100, stdin);

    // if length is less than
    int strLength = strlen(letters);
    if (strLength % thread_count != 0)
    {

        int lessNum = thread_count - (strLength % thread_count);

        for (int k = 0; k < lessNum; k++)
        {
            strcat(letters, " ");
        }
    }

    h = strlen(letters) / thread_count;

    thread_handles = malloc(h * sizeof(pthread_t));
    printf("Going to create threads");
    /* Creating the threads */
    for (long thread = 0; thread < thread_count; thread++)
    {
        pthread_mutex_init(&mutex[thread], NULL);
        pthread_create(&thread_handles[thread], NULL, task, (void *)thread);
        pthread_join(thread_handles[thread], NULL);
        pthread_mutex_destroy(&mutex[thread]);
    }

    for (int i = 33; i < ASCIIs; i++)
        if (count[i] != 0)
            printf("Number of %c is: %d \n", i, count[i] / thread_count);
    pthread_exit(NULL);

    free(thread_handles);
    return 0;
}

void *task(void *rank)
{

    pthread_mutex_lock(mutex);
    for (int i = 0; i < strlen(letters); i++)
    {
        int index = (int)letters[i];
        (count[index])++;
    }
    pthread_mutex_unlock(mutex);

    return NULL;
}