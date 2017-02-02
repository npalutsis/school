/* Author: Nick Palutsis
   Date: October 14, 2015 */

// Use Euclidean Algorithm to find greatest common denominator

#include <stdio.h>

int main(void){
   int x, y, a, b, r, d;
   
   printf("Enter two numbers: ");
   scanf("%d %d", &x, &y);
   
   if(x <= y){
      b = x;
      x = y;
      y = b;
   }
   
   while(y != 0){
      d = x / y;
      r = x % y;
      x = y;
      printf("Divisor = %d\n"
         "Quotient = %d\n"
         "Remainder = %d\n\n", d, x, r);
      
      y = r;
   }
   
   printf("The greatest common denominator is %d\n", x);
   
   return 0;
}
