// downrec.c
// simple recursion demonstration for a countdown

#include <stdio.h>

void countdown(int);

int main()
{
  int n;

  printf("Enter a number: ");
  scanf("%d", &n);
  countdown(n);         // main call

  return 0;
}

void countdown(int n)
{
  printf("-> %d\n", n);
  if(n == 0)            // base case
    return;
  else 
    countdown(n-1);     // recursive call
}

