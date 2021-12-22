#include <stdio.h>
#include <string.h>
#include <time.h>

int main(){
   char str[1000], ch;
   int i, frequency = 0;
   clock_t t;
struct timespec ts, ts2;
  

   printf("Enter a string: ");
   gets(str);

   int len = strlen(str);

   printf("Enter a character to find the frequency: ");
   scanf("%c",&ch);

   t = clock();
   timespec_get(&ts, TIME_UTC);

   for(i = 0; i < len; ++i)
   {
   if(ch == str[i])
   frequency += 1;
   }

   t = clock() - t;
   timespec_get(&ts2, TIME_UTC);
double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
   printf("Frequency of %c = %d\n", ch, frequency);
   printf("Time required = %ld \n",(ts2.tv_nsec - ts.tv_nsec));

   return 0;
}

Parallel Program using OpenMP directives

#include <omp.h>
#include <string.h>

int main(){
   char str[1000], ch;
   int i, frequency = 0;

   printf("Enter a string: ");
   gets(str);

   int len = strlen(str);

   printf("Enter a character to find the frequency: ");
   scanf("%c",&ch);

   double start = omp_get_wtime();

   #pragma omp parallel for reduction(+ : frequency)
   for(i = 0; i < len; ++i)
   {
      if(ch == str[i])
   frequency += 1;
   }

   double end = omp_get_wtime();
   printf("Frequency of %c = %d\n", ch, frequency);
   printf("Time required = %lf \n", end - start);

   return 0;
}