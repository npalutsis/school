/* Author: Nick Palutsis */

#include <stdio.h>

int getgcd(int num1, int num2) /* function to calculate the greatest common denominator of two numbers */
{
   int r; /* remainder after the division of the two numbers */
   int gcd; /* greatest common denominator */
   
   while(gcd != num1 && gcd != num2) /* loop will stop when the gcd is found */
   {
      if(num2 <= num1) /* if number 1 is bigger */
      {
         r = num1 % num2; /* calculates remainder */
         if(r == 0) /* greatest common denominator is found */
         {
            gcd = num2;
         }
         else /* reassigns variables and repeats loop */
         {
            num1 = num2;
            num2 = r;
         }
      }
      else /* if number 2 is bigger */
      {
         r = num2 % num1; /* calculates remainder */
         if(r == 0) /* greatest common denominator is found */
         {
            gcd = num1;
         }
         else /* reassigns variables and repeats loop */
         {
            num2 = num1;
            num1 = r;
         }
      }
   }
   
   return gcd; /* returns gcd as output of the function */
}

int main(void)
{
   int a, b, gcd;
   
   printf("Enter two numbers to find the greatest common denominator: \n"); /* prompts user for two numbers to find gcd for */
   scanf("%d %d", &a, &b); /* reads inputs from the user */

   gcd = getgcd(a, b); /* sends numbers to function to calculate gcd */
   
   printf("The greatest common denominator of %d and %d is %d.\n", a, b, gcd); /* displays answer to the user */
   
   return 0; /* signifies successful run of program */
}
