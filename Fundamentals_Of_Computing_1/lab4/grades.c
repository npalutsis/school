/* Author: Nick Palutsis 
   Class: CSE 20211
   Lab: 4 */
/* Calculates the average and standard deviation from a set of grades */

#include <stdio.h>
#include <math.h>

double standard_deviation(double grade[], double avg, int n);

int main(void){
   double grade[50];
   int i;
   int n = 0;
   double sum;
   double avg;
      
   scanf("%lf", &grade[n]); /* reads input as an array from a file */
   
   while(grade[n] >= 0){ /* loop will run until the negative sentinal value */
      n++;
      scanf("%lf", &grade[n]);
   }
   
   /* find the sum of the grades */
   for(i = 0; i < n; i++){
      printf("%.lf ", grade[i]);
      sum = sum + grade[i];
   }
   
   /* find the average of the grades */
   avg = sum / n;
   
   printf("\nThe average is %.2lf\n", avg);
   printf("The standard deviation is %.2lf\n", standard_deviation(grade, avg, n));
   
   return 0;
}

/* function to calculate standard deviation */
double standard_deviation(double grade[], double avg, int n){
   double sum;
   double dev_sum;
   double dev;
   int i;
   
   for(i = 0; i < n; i++){
      dev_sum = pow((grade[i] - avg), 2);
   }
   
   dev = sqrt(dev_sum / n);
   
   return dev;
}
