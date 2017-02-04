#include <stdio.h>

int getgcd(int num1, int num2)
{
   int r;
   int gcd;
   int num;
   
   r = 1;
   
   while(r != 0)
   {
      if(num1 <= num2)
      {
         num = num1;
         num1 = num2;
         num2 = num;
      }
      
      r = num1 % num2;
      
      if(r == 0)
      {
         gcd = num2;
      }
      else
      {
         num1 = num2;
         num2 = r;
      }
   }
   
   return gcd;
}

int main(void)
{
   int a;
   int b;
   int gcd;
   
   printf("Enter two numbers to find the greatest common denominator:\n");
   scanf("%d %d", &a, &b);
   
   gcd = getgcd(a, b);
   
   printf("The greatest common denominator of %d and %d is %d\n", a, b, gcd);
   
   return 0;
}
