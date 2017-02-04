/* Author: Nick Palutsis */

#include <stdio.h>
#include <math.h>
#include <string.h>

int printpoint(double x, double y, double r, double theta) //prints coordinates
{
    printf("\nThe polar coordinates for the point (%.2lf, %.2lf) are (%.2lf, %.2lf).\n", x, y, r, theta); /* displays polar coordinate for point */
}
int printq(char *quadrant) /* function to print quadrant of the point */
{
   printf("The point is in quadrant %s.\n\n", quadrant);
}
int printa(char *axis) /* function to print which axis the point is on */
{
   printf("The point is on the %s.\n\n", axis);
}

int main(void)
{
   double x;
   double y;
   double r;
   double theta;
   char quadrant[50];
   char axis[50];
   
   
   printf("What is the x coordinate of the point?\n"); /* prompts user for the x coordinate */
   scanf("%lf", &x); /* reads input from user */
   
   printf("What is the y coordinate of the point?\n"); /* prompts user for the y coordinate */
   scanf("%lf", &y); /* reads input from user */
   
   r = sqrt(x * x + y * y); /* calculates the r value for the polar coordinate */
   theta = atan(y / x) * 180 / 3.1416; /* calculates the angle for the polar coordinate */
   
   if(x > 0 && y > 0)
   {
      printpoint(x, y, r, theta);
      strcpy(quadrant, "I"); /* point is in quadrant I */
      printq(quadrant); /* inputs to quadrant function to print to the user */
   }
   else if(x < 0 && y > 0)
   {
      theta = 180 + theta;
      printpoint(x, y, r, theta);
      strcpy(quadrant, "II"); /* point is in quadrant II */
      printq(quadrant); /* inputs to quadrant function to print to the user */
   }
   else if(x < 0 && y < 0)
   {
      theta = -180 + theta;
      printpoint(x, y, r, theta);
      strcpy(quadrant, "III"); /* point is in quadrant III */
      printq(quadrant); /* inputs to quadrant function to print to the user */
   }
   else if(x > 0 && y < 0)
   {
      //theta = 360 - theta;
      printpoint(x, y, r, theta);
      strcpy(quadrant, "IV"); /* point is in quadrant IV */
      printq(quadrant); /* inputs to quadrant function to print to the user */
   }
   else if (x == 0 && y > 0)
   {
      strcpy(axis, "positive y axis"); /* point is on an axis, not a quadrant */
      printa(axis); /* inputs to axis function to print to the user */
   }
   else if(x == 0 && y < 0)
   {
      strcpy(axis, "negative y axis"); /* point is on an axis, not a quadrant */
      printa(axis); /* inputs to axis function to print to the user */
   }
   else if(x > 0 && y == 0)
   {
      strcpy(axis, "positive x axis"); /* point is on an axis, not a quadrant */
      printa(axis); /* inputs to axis function to print to the user */
   }
   else if(x < 0 && y == 0)
   {
      strcpy(axis, "negative x axis"); /* point is on an axis, not a quadrant */
      printa(axis); /* inputs to axis function to print to the user */
   }
   else if(x == 0 && y == 0)
   {
      printf("The point is located at the origin.\n\n"); /* point is at the origin, not a quadrant or axis */
   }
   
   return 0; /* signifies successful run of program */
}
