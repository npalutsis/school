/* Author: Nick Palutsis 
   Class: CSE 20211
   Lab: 4*/
/* Use the sieve or Eratosthenes algorithm to find the prime numbers */

#include <stdio.h>

int main(void){
   int column = 0;
   int numbers = 1000;
   int A[numbers];
   int n = 1;
   int i, x;
   
   /* create an array with elements 1 - 1000 */
   for(i = 0; i < numbers; i++){
      A[i] = 1;
   }
   
   A[0] = 0; /* set first element (1) to false */
   
   while(n < numbers){
      for(i = n; i < numbers; i++){
         if(A[i] == 1){ /* find an element that is true */
            for(x = n + 1; x < numbers; x++){
               if(((x + 1) % (n + 1)) == 0){ /* change multiples to false */
                  A[x] = 0;
               }
            }
         }
      }
      n++;
   }
   /* prints prime numbers */
   for(i = 0; i < numbers; i++){ 
      if(A[i] == 1){
         printf("%5d ", (i + 1));
         column++;
      }
      /* prints the array with 10 columns */
      if(column >= 10){
         printf("\n");
         column = 0;
      }
   }
   
   printf("\n");
   
   return 0;
}

