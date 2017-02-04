/* Author: Nick Palutsis
   Class: CSE 20211
   Lab 7
   Date: October 30, 2015 */
   
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "gfx.h"

void polygon(int r, int nsides, int x, int y, double startTheta);
void seat(int r, int xCenter, int yCenter);

int main()
{
   int wd = 1000;  // window width
   int ht = 1000;  // window height
   int dx;
   int dy;    // basic increment for animation
   int waittime = 20000;
   int r = 40;
   int big_r = 300;
   int nseats = 6;
   int x, x1, x2, x3, x4, x5;
   int y, y1, y2, y3, y4, y5;
   int i;
   double startTheta = 0.0;
   double dtheta = .01;
   char c;

   gfx_open(wd, ht, "Bounce");  // Open a new window for drawing.
  
   x = wd / 2;	// Starts ball in center of the screen
   y = ht / 2 - 100;

   srand(time(NULL));
   gfx_color(rand() % 255, rand() % 255, rand() % 255);      // Set the current drawing color randomly
   
   while(1) { 
      gfx_clear();
      gfx_flush;
    
      // Draw Shape
      polygon(big_r, nseats, x, y, startTheta);
      polygon(big_r * 4 / 5, 3, x, y + big_r * 4 / 5, M_PI / 6);
      for(i = 0; i < nseats; i++){
         seat(x, y, r);
         gfx_line(x, y, big_r * cos(startTheta + 2 * i * M_PI / nseats) + x, big_r * sin(startTheta + 2 * i * M_PI / nseats) + y);
      }
      gfx_circle(x, y, 20);
      gfx_circle(x, y, big_r);
      startTheta = startTheta + dtheta;
    
      gfx_flush;
      usleep(waittime);      // pause for set number of seconds
      if(gfx_event_waiting()) { 
         c = gfx_wait();
         if(c == 'q')		// Quits program
            break;
         
      }
   }
   return 0;
}


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

void seat(int r, int xCenter, int yCenter)
{
   int x;
   int y;
   int i;
   
   for(i = 0; i <= r; i++){
      gfx_line(x - r - i, y - i, x + r + i, y - i);
      gfx_line(x - r + i, y + i, x + r - i, y + i);
   }
}
