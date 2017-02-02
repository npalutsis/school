/* Fibonacci with a recursive function */

#include <stdio.h>

int fib(int);

int main()
{
  int n;

  printf("Enter a number: ");
  scanf("%d", &n);
  printf("fibonacci of %d is %i\n", n, fib(n));

  return 0;
}

int fib(int n)
{
  int f;

  if(n == 0 || n == 1) return n;  // base case

  f = fib(n-1) + fib(n-2);        // recursive call

  return f;
}

