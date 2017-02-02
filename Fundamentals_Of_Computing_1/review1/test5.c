#include <stdio.h>
#include <math.h>

double myexp(double);

int main()
{
  double x;
  printf("enter a real number x: ");
  scanf("%lf", &x);
  printf("e^%lf is %lf\n", x, myexp(x));
  printf("using math\'s exp, it is %lf\n", exp(x));
 
  return 0;
}
double myexp(double x)
{
  int i, num = 12;
  double val = 0 , term = 1;

  for (i = 1; i <= num; i++ ) {
    val = val + term;
    term = term * x/i;
  }

  return val;
}
