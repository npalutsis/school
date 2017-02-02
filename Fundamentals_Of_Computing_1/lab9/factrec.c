/* factorial with a recursive function */

#include <stdio.h>

int fact(int);

int main()
{
  int n;

  printf("Enter a number: ");
  scanf("%d", &n);
  printf("the factorial of %d is %i\n", n, fact(n));

  return 0;
}

int fact(int n)
{
  int f;

  if(n == 1 || n == 0) return 1;  // base case

  f = n * fact(n-1);   // recursive call

  return f;
}

