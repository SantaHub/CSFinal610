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

void *Sort(int x[])
{
    int i, indexOfSmallest, t;
    for (i = 0; i < n; i++)
    {
        indexOfSmallest = findIndexOfSmallest(x, n, i);
        t = x[i];
        x[i] = x[indexOfSmallest];
        x[indexOfSmallest] = t;
    }
}

void finalMerge(int a[], int b[], int d[], int n)
{

    int j = n;
    int k = n;
    int l = j + k;
    int c[j + k];
    int e[j + k + n];

    for (int i = 0; i < j + k; i++)
    {
        if (i < j)
            c[i] = a[i];
        else
            c[i] = b[i - j];
    }

    for (int i = 0; i < l + n; i++)
    {
        if (i < l)
            e[i] = c[i];
        else
            e[i] = d[i - l];
    }
    printf("Merged array is :\n");
    for (int i = 0; i < l + n; i++)
    {
        printf("c[%d]=%d\n", i, e[i]);
    }
}

int main()
{

    srand(time(NULL));
    // generating a random number for n
    n = rand() % 10;
    printf("a) Generating Random integer : %d \n", n);

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    printf("b) Created two arrays a and b with size %d", n);

    c = (int *)malloc(2 * n * sizeof(int));
    printf("c) Created array C with size 2 * %d", n);

    Fill(a, n);
    Fill(b, n);
    printf("d) Filled the arrays with random number of range 0 to 99");
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
    printf("e) Used Pthread to sort arrays");
    printf("Printing Array a : ");
    Print(a, n);
    printf("Printing Array b : ");
    Print(b, n);

    //You need to create two threads, pass the function: Sort.
    //The argument of Sort is an array.
    // Call join for both threads.
    printf("Array: b after sorting\n");
    Print(b, n);
    printf("Array: c\n");
    Print(c, n);
    //mergeTwo(a,b,n)
    finalMerge(a, b, c, n);
    return 0;
    free(thread);
    return 0;
}

// compile : gcc -g -Wall fileName.c -lpthread