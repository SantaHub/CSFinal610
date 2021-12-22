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
    printf("Enter a line not larger than 1000 characters.\n");
    fgets(letters, atmost, stdin);
    printf("How many threads?: ");
    scanf("%d", &thread_count);
    while (strlen(letters) % thread_count != 0)
        strcat(letters, " ");
    n = strlen(letters);
    for (i = 0; i < ASCIIs; i++)
        total_count[i] = 0;
#pragma omp parallel num_threads(thread_count)
    find(total_count, start, end);

    for (i = 33; i < ASCIIs; i++)
    {
        printf("am printing the frequence of : " + i);
        if (total_count[i] != 0)
            printf("Number of %c is: %d\n", i, total_count[i]);
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