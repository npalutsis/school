/*Author: Nick Palutsis*/

#include <stdio.h>
/*Calculates output for x = x0 + v0 * t + .5 * a * t * t*/

float main(void)
{
   float x0; /*initial position*/
   float x; /*final position*/
   float v0; /*initial velocity*/
   float a; /*acceleration*/
   float t; /*duration of motion*/

   printf( "This program calculates an objects final position based off of basic kinematics.\n" );
   /*Displays the purpose of the program to the user*/
   
   printf( "Enter the initial position (m): " ); /*prompt user for input*/
   scanf("%f", &x0); /*read value for initial position*/

   printf( "Enter the initial velocity (m/s): " ); /*prompt user for input*/
   scanf("%f", &v0); /*read value for initial velocity*/

   printf( "Enter the acceleration (m/s^2): " ); /*prompt user for input*/
   scanf("%f", &a); /*read value for acceleration*/

   printf( "Enter the duration of the motion (s): " ); /*prompt user for input*/
   scanf("%f", &t); /*read value for the time of motion*/

   if(t < 0){
      printf( "Sorry, the duration of the motion must be a value greater than or equal to zero.\n");
      /*Error message for an invalid input*/
      
      return 0;
   } /*Ends program if there is an invalid input*/

   x = x0 + v0 * t + .5 * a * t * t; /*calculate the final position of the object*/

   printf("The final position is at %.3f meters.\n", x); /*display final position*/

   return 0; /*indicate a successful run*/
} /*ends program*/
