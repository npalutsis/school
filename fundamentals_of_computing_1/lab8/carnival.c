// Author: Nick Palutsis
   // Class: CSE 20211
   // Lab 8
   // Date: November 8, 2015
   
// Carnival Ride with at least four axis of motion

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "gfx.h"
#include "gfx3.h"

void polygon(int r, int nsides, int xCenter, int yCenter, double startTheta);

int main(void)
{
   int wd = 1000;
   int ht = 1000;
   int xorigin = wd / 2;
   int yorigin = ht / 2;
   int x1, x2, x3;
   int y1, y2, y3;
   int dx = 2;
   int R = 500;
   int r = 200;
   int dR = 2;
   int dr = 1;
   int a = 300;
   int b = wd - 300;
   int i, j;
   double theta1 = 3 * M_PI / 2;
   double dtheta1 = .01;
   double theta2 = M_PI / 2;
   double dtheta2 = .02;
   double theta3 = 0;
   double dtheta3 = -.03;
   double theta4 = 0;
   char c;
   
   gfx_open(wd, ht, "Carnival Ride");
   x1 = xorigin;
   y1 = ht - 125;
   x2 = xorigin;
   y2 = yorigin;
   
   while(1) { 
      gfx_clear();
      gfx_flush;
      
      x2 = R * cos(theta1) + x1;
      y2 = R * sin(theta1) + y1;
      x3 = r * cos(theta2) + x2;
      y3 = r * sin(theta2) + y2;      
      
      // White
      gfx_color(255, 255, 255);
      gfx_line(300, ht - 100, wd - 300, ht - 100);
      gfx_line(x1, ht - 100, x2, y2);
      gfx_line(x2, y2, x3, y3);
      for(i = 1; i <= 5; i++)
         gfx_line(x3, y3, 100 * cos(theta3 + 2 * i * M_PI / 5) + x3, 100 * sin(theta3 + 2 * i * M_PI / 5) + y3);
      
      // Blue
      gfx_color(0, 150, 255);
      for(i = 1; i <= 5; i++){
         for(j = 1; j <= 15; j++)
            polygon(j, 4, 100 * cos(theta3 + 2 * i * M_PI / 5) + x3, 100 * sin(theta3 + 2 * i * M_PI / 5) + y3, theta4);}
            
      // Red
      gfx_color(255, 0, 0);
      for(i = 1; i <= 25; i++)
         polygon(i, 5, x3, y3, theta3);
      for(i = 1; i <= 15; i++)
         gfx_circle(x1, ht - 100, i);
      for(i = 1; i <= 10; i++)
         gfx_circle(x2, y2, i);
      
      if(x1 + dx > wd - 300 || x1 + dx < 300){     // Changes left-right direction of base
         dx = -dx;}
      
      if(theta1 <= (5 * M_PI / 4) || theta1 >= (7 * M_PI / 4)){   // Change rotation direction
         dtheta1 = -dtheta1;
         dtheta2 = -dtheta2;}
      
      // Change direction of growth
      if(R <= 400 || R >= 800)
         dR = -dR;
      if(r <= 50 || r >= 400)
         dr = -dr;
      
      // Increment angles and lengths  
      theta1 = theta1 + dtheta1;
      theta2 = theta2 + dtheta2;
      theta3 = theta3 + dtheta3;
      theta4 = theta4 - dtheta3;
      x1 = x1 + dx;
      R = R + dR;
      r = r + dr;
      
      usleep(20000);
      
      if(gfx_event_waiting()) { 
         c = gfx_wait();      // User input
            if(c == 'q')		// Quits program
               break;
      }
   }
   
   return 0;
}



// Draws a regular polygon with a set center, set number of sides, set radius, and set orientation
void polygon(int r, int nsides, int xCenter, int yCenter, double startTheta)
{
   int x1, y1;
   int x2, y2;
   int i;
   double theta;

   theta = 2 * M_PI / nsides;
   x1 = r * cos(startTheta) + xCenter;
   y1 = r * sin(startTheta) + yCenter;

   for(i = 1; i <= nsides; i++){
      x2 = r * cos(i * theta + startTheta) + xCenter;
      y2 = r * sin(i * theta + startTheta) + yCenter;
      gfx_line(x1, y1, x2, y2);
      x1 = x2;
      y1 = y2;
   }
}

