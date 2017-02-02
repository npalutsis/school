/* Author: Nick Palutsie 
   Class: CSE 20211
   Lab 5
   Date: October 11, 2015 */

#include <stdio.h>
#include <math.h>

int polar_info(double x, double y, double *radius, double *angle)
{
   int quad;
   
   *radius = sqrt(x * x + y * y); /* calculates the r value for the polar coordinate */
   *angle = atan(y / x) * 180 / 3.1416; /* calculates the angle for the polar coordinate */
   
   if(x > 0 && y > 0)
   {
      quad = 1;
   }
   else if(x < 0 && y > 0)
   {
      *angle = 180 + *angle;
      quad = 2;
   }
   else if(x < 0 && y < 0)
   {
      *angle = -180 + *angle;
      quad = 3;
   }
   else if(x > 0 && y < 0)
   {
      quad = 4;
   }
   else if (x == 0 && y != 0)
   {
      quad = -2;
   }
   else if(x != 0 && y == 0)
   {
      quad = -1;
   }
   else if(x == 0 && y == 0)
   {
      quad = 0;
   }
   
   return quad;
}
