/* Author: Nick Palutsis
   Class: CSE 20211
   Lab 7
   Date: October 30, 2015 */

// Draws a rotating ferris wheel that allows the user to interact with it via certain key commands

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "gfx.h"

void polygon(int r, int nsides, int x, int y, double startTheta);

void seat(int x, int y, int r);

int main()
{
   int wd = 1000;
   int ht = 1000;
   int dx;
   int dy;
   int waittime = 40000;
   int r = 20;
   int big_r = 300;
   int nseats = 8;
   int x, x1, x2, x3, x4, x5;
   int y, y1, y2, y3, y4, y5;
   int i;
   double startTheta = 0.0;
   double dtheta = .05;
   char c;

   gfx_open(wd, ht, "Ferris Wheel");  // Open a new window for drawing.
  
   x = wd / 2;
   y = ht / 2 - 30;
   
   while(1) { 
      gfx_clear();
      gfx_flush;

      gfx_color(255, 255, 255);
      polygon(big_r, nseats, x, y, startTheta);    // Draws rotating polygon as support beams
      polygon(big_r * 4 / 5, 3, x, y + big_r * 4 / 5, M_PI / 6);     // Draws stationary triangle as support beams

      gfx_color(255, 255, 255);
      gfx_circle(x, y, big_r);      // Draws big circle
      
      for(i = 0; i < nseats; i++){
         gfx_color(255, 255, 255);
         gfx_line(x, y, big_r * cos(startTheta + 2 * i * M_PI / nseats) + x, big_r * sin(startTheta + 2 * i * M_PI / nseats) + y);     // Connecting lines from center to seats
         gfx_color(255, 0, 0);
         seat(big_r * cos(startTheta + 2 * i * M_PI / nseats) + x, big_r * sin(startTheta + 2 * i * M_PI / nseats) + y, r);      // Draws solid trapezoids for seats
      }
      
      gfx_circle(x, y, big_r / 18);    // Draws inner circles
      gfx_circle(x, y, big_r / 13);
      
      for(i = 0; i <= ht - (big_r * 33 / 48 * tan(M_PI / 3) + y); i++){    // Fills in grass below ferris wheel
         gfx_color(0, 255, 0);
         gfx_line(0, big_r * 33 / 48 * tan(M_PI / 3) + y + i, wd, big_r * 33 / 48 * tan(M_PI / 3) + y + i);
      }
      
      gfx_color(0, 0, 0);
      gfx_text(290, big_r * 33 / 48 * tan(M_PI / 3) + y + 20, "j: Shift to the left");
      gfx_text(290, big_r * 33 / 48 * tan(M_PI / 3) + y + 40, "l: Shift to the right");
      gfx_text(290, big_r * 33 / 48 * tan(M_PI / 3) + y + 60, "i: Shift upward");
      gfx_text(290, big_r * 33 / 48 * tan(M_PI / 3) + y + 80, "k: Shift downward");
      gfx_text(290, big_r * 33 / 48 * tan(M_PI / 3) + y + 100, "h: Increase the number of seats");
      gfx_text(290, big_r * 33 / 48 * tan(M_PI / 3) + y + 120, "g: Decrease the number of seats");
      
      gfx_text(525, big_r * 33 / 48 * tan(M_PI / 3) + y + 20, "r: Speed up ferris wheel");
      gfx_text(525, big_r * 33 / 48 * tan(M_PI / 3) + y + 40, "f: Slow down ferris wheel");
      gfx_text(525, big_r * 33 / 48 * tan(M_PI / 3) + y + 60, "e: Increase the size of the wheel");
      gfx_text(525, big_r * 33 / 48 * tan(M_PI / 3) + y + 80, "d: Decrease the size of the wheel");
      gfx_text(525, big_r * 33 / 48 * tan(M_PI / 3) + y + 100, "w: Increase the size of the seats");
      gfx_text(525, big_r * 33 / 48 * tan(M_PI / 3) + y + 120, "s: Decrease the size of the seats");
      gfx_text(480, big_r * 33 / 48 * tan(M_PI / 3) + y + 140, "q: Quit");

      startTheta = startTheta + dtheta;      // Incremented variable to rotate shapes by
    
      gfx_flush;
      usleep(waittime);      // Pause for set number of seconds
      
      if(gfx_event_waiting()) { 
         c = gfx_wait();
         if(c == 'q')		// Quits program
            break;
         else if(c == 'f')    // Slows down rotation by increasing wait time
            waittime = waittime + 1000;
         else if(c == 'r'){      // Speeds up rotation by decreasing wait time
            if(waittime > 3000)
            waittime = waittime - 1000;
         }
         else if(c == 'w')    // Increases the size of the seats
            r = r + 5;
         else if(c == 's'){      // Decreases the size of the seats
            if(r > 5)
               r = r - 5;
         }
         else if(c == 'e')       // Increases the size of ferris wheel radius
            big_r = big_r + 5;
         else if(c == 'd'){      // Decreases the size of ferris wheel radius
            if(big_r > r)
               big_r = big_r - 5;
         }
         else if(c == 'l')       // Shifts ferris wheel to the right
            x = x + 5;
         else if(c == 'j')       // Shifts ferris wheel to the left
            x = x - 5;
         else if(c == 'k')       // Shifts ferris wheel and grass downwards
            y = y + 5;
         else if(c == 'i')       // Shifts ferris wheel and grass upwards
            y = y - 5;
         else if(c == 'h')       // Increases the number of seats and support beams
            nseats++;
         else if(c == 'g')       // Decreases the number of seats and support beams
            nseats--;
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

// Draws solid trapezoidal seats for ferris wheel
void seat(int x, int y, int r)
{
   int i;
   
   for(i = 0; i <= r; i++){
      gfx_line(x - r, y + r, x - 2 * r + i, y - r);
      gfx_line(x + r, y + r, x + 2 * r - i, y - r);
      gfx_line(x - r, y - i, x + r, y - i);
      gfx_line(x - r, y + i, x + r, y + i);
   }
}
