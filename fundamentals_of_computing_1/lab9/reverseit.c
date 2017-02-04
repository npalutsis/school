// example to use recursion to display a string backwards
#include <stdio.h>

void reverse(char *p);

int main()
{
  char line[80];

  printf("enter a line: ");
  fgets(line, 80, stdin);
  reverse(line);
  printf("\n");
}

void reverse(char *p)
{
  if (*p == '\n') return;  // base case

  reverse(p+1);            // recursive call

  printf("%c", *p);        // starting printing, as the program backtracks
}

