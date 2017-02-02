/* Author: Nick Palutsis */
#include <stdio.h>
#include <math.h>

int main(void)
{
   double a; /* start of range */
   double b; /* end of range */
   double x; /* x value to graph */
   double y; /* y value to graph */
   double xmin; /* x coordinate of lowest point */
   double xmax; /* x coordinat of highest point */
   double ymin; /* lowest point */
   double ymax; /* highest point */
   int i; /* counter to print graph */
   
   a = -15; /* start of range */
   b = 15; /* end of range */
   
   printf("A plot of y = 15 + 10 * sin(.1 * x^2) from x = %lf to %lf\n", a, b); /* Display purpose of program to the user */
   printf("     X      Y\n"); /* Labels for the table of x and y coordinates */
   
   y = 15 + 10 * sin(.1 *a * a); /* first y coordinate */
   ymax = y; /* establish minimum y */
   ymin = y; /* establish maximum y */
   
   for(x = a; x < b; x+=.1) /* counts for x coordinates */
   {
      y = 15 + 10 * sin(.1 * x * x); /* plugs current x coordinate in for current y value */
      
      if(y < ymin){ /* reevaluate new minimums */
         ymin = y;
         xmin = x;
      }
      if(y > ymax){ /* reevaluate new maximums */
         ymax = y;
         xmax = x;
      }
      
      printf("%6.2lf %6.2lf  ", x, y); /* print table for x and y values */
      y = round(y); /* rounds y value to nearest integer */
      for(i = 1; i <= y; i++){ /* print character y number of times */
      printf("#");
      }
      printf("\n");
     
   }
   
   printf("The maximum of %.2lf was at x = %.2lf\n", b, xmax); /* display maximum to user */
   printf("The minimum of %.2lf was at x = %.2lf\n", a, xmin); /* display minimum to user */
   
   return 0; /* indicate a successful program run */
}
