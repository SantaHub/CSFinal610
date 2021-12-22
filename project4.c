#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define thread_count 20
#define ASCIIs 127 //ASCII characters from 0 to 127
#define atmost 1000

char letters[atmost + 1]; //extra location for '\0'. atmost must be divisible by thread_count
int count[ASCIIs], h;     //h holds the length of the segment
pthread_mutex_t mutex[ASCIIs];
void *task(void *rank);

int main()
{
    pthread_t *thread_handles;
    int i;
    long thread;
    for (i = 0; i < ASCIIs; i++)
    {
        count[i] = 0;
    }

    printf("Enter a line not larger than 100 characters.\n");
    fgets(letters, atmost, stdin);

    int len, append;

    len = strlen(letters);
    append = len % thread_count;

    if (append != 0)
    {
        append = thread_count - append;
    }

    for (i = 0; i < append; i++)
    {
        strcat(letters, " ");
    }

    h = strlen(letters) / thread_count;
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (i = 0; i < ASCIIs; i++)
    {
        pthread_mutex_init(&mutex[i], NULL);
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, task, (void *)thread);
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    for (i = 0; i < ASCIIs; i++)
    {
        pthread_mutex_destroy(&mutex[i]);
    }

    free(thread_handles);

    for (i = 33; i < ASCIIs; i++)
    {
        if (count[i] != 0)
            printf("Number of %c is: %d\n", i, count[i]);
    }
    return 0;
}

void *task(void *rank)
{
    int newRank = (long)rank;
    int strt = newRank * h;
    int end = strt + h;
    int i, index;
    for (i = strt; i < end; i++)
    {
        pthread_mutex_lock(&mutex[i]);
        index = (int)letters[i];
        (count[index])++;
        pthread_mutex_unlock(&mutex[i]);
    }

    return NULL;
}

// Compile : gcc -g -Wall -lpthread