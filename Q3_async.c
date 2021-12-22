#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#define ASCIIs 127 //ASCII characters from 0 to 127
#define atmost 1000
char letters[atmost + 1]; //Extra location for the string
// terminator '\0'
int total_count[ASCIIs];
void find(int count[], int start, int end);

int main()
{
    int i, thread_count, n, start, end;
    int count[ASCIIs], my_rank, segment, p;
    printf("Enter a line not larger than 1000 characters.\n");
    fgets(letters, atmost, stdin);
    printf("How many threads?: ");
    scanf("%d", &thread_count);
    while (strlen(letters) % thread_count != 0)
        strcat(letters, " ");
    n = strlen(letters);
    for (i = 0; i < ASCIIs; i++)
        total_count[i] = 0;

    double startTime = omp_get_wtime();

#pragma omp parallel num_threads(thread_count)
    {
        my_rank = p;
        segment = n / thread_count;
        start = my_rank * segment;
        end = start + segment;
        find(count, start, end);
        for (i = 0; i <= ASCIIs; i++)
            total_count[i] += count[i];
    }
    double endTime = omp_get_wtime();
    printf("Time required = %lf \n", endTime - startTime);

    for (i = 33; i < ASCIIs; i++)
    {
        int frequency = total_count[i];
        if (total_count[i] != 0)
            printf("Number of %c is: %d ", i, frequency);
    }
    return 0;
}
void find(int count[], int start, int end)
{
    int i;
    for (i = 0; i < ASCIIs; i++)
        count[i] = 0;
    for (i = start; i < end; i++)
        count[(int)letters[i]]++;
}

// gcc -fopenmp Q3_async.