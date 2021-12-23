#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int *a, *b, *c;
int n;

// Filling the Arrays.
void Fill(int x[], int n)
{
    for (int i = 0; i < n; i++)
        x[i] = rand() % 100;
}

//Printing the Array
void Print(int x[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d, ", x[i]);
    printf("\n--------------------------------\n");
}

int findIndexOfSmallest(int a[], int n, int from)
{
    int indexOfSmallest = from;
    int i;

    for (i = from; i < n; i++)
        if (a[i] < a[indexOfSmallest])
            indexOfSmallest = i;
    return indexOfSmallest;
}

//Sorting the Arrays

void *Sort(void *input)
{
    int *x = input;
    int i, indexOfSmallest, t;
    for (i = 0; i < n; i++)
    {
        indexOfSmallest = findIndexOfSmallest(x, n, i);
        t = x[i];
        x[i] = x[indexOfSmallest];
        x[indexOfSmallest] = t;
    }
    return NULL;
}

void Merge(int a[], int b[], int c[], int n)
{
    int aIndex = 0, bIndex = 0, cIndex = 0;
    while (aIndex < n && bIndex < n)
        if (a[aIndex] < b[bIndex])
            c[cIndex++] = a[aIndex++];
        else
            c[cIndex++] = b[bIndex++];
    while (aIndex < n)
        c[cIndex++] = a[aIndex++];
    while (bIndex < n)
        c[cIndex++] = b[bIndex++];
}

int main()
{

    srand(time(NULL));
    // generating a random number for n
    n = rand() % 10;
    printf("a) Generating Random integer : %d \n", n);

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    printf("b) Created two arrays a and b with size %d \n", n);

    c = (int *)malloc(2 * n * sizeof(int));
    printf("c) Created array C with size 2 * %d \n", n);

    Fill(a, n);
    Fill(b, n);
    printf("d) Filled the arrays with random number of range 0 to 99 \n");
    printf("Printing Array a : ");
    Print(a, n);
    printf("Printing Array b : ");
    Print(b, n);

    pthread_t *thread;
    thread = malloc(2 * sizeof(pthread_t));
    pthread_mutex_t mutex[2];

    pthread_mutex_init(&mutex[0], NULL);
    pthread_create(&thread[0], NULL, Sort, a);

    pthread_mutex_init(&mutex[1], NULL);
    pthread_create(&thread[1], NULL, Sort, b);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_mutex_destroy(&mutex[0]);
    pthread_mutex_destroy(&mutex[1]);

    printf("e) Used Pthread to sort  \n");
    printf("Printing Array a : ");
    Print(a, n);
    printf("Printing Array b : ");
    Print(b, n);

    //You need to create two threads, pass the function: Sort.
    //The argument of Sort is an array.
    // Call join for both threads.
    printf("f) Merging Array a,b into array c : ");
    Merge(a, b, c, n);
    printf("Array: c\n");
    Print(c, 2 * n);

    free(thread);
    return 0;
}

// compile : gcc -g -Wall fileName.c -lpthread