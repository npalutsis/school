/* Author: Nick Palutsis
   Class: CSE 20211
   Lab 7 
   Date: October 30, 2015 */

#include <stdio.h>
#include <math.h>
#include "gfx.h"

void polygon(int r, int nsides);

int main(void)
{
   int xsize = 600;
   int ysize = 600;
   int loop = 1;
   int x, y;
   int x1, y1;
   int x2, y2;
   int r = 25;
   int i;
   double theta;
   int nsides;
   char c;
   
   //Open a new window for drawing
   gfx_open(xsize, ysize, "Symbol Drawing Program");

   // Clear the background.
   gfx_clear();
   
   while(loop){
      if(gfx_event_waiting()){
         c = gfx_wait();
         switch(c){
            case 1:
               x = gfx_xpos();
               y = gfx_ypos();
               gfx_color(0, 0, 200);
               gfx_line(x - 25, y + 25, x + 25, y + 25);
               gfx_line(x - 25, y - 25, x + 25, y - 25);
               gfx_line(x - 25, y - 25, x - 25, y + 25);
               gfx_line(x + 25, y - 25, x + 25, y + 25);
               break;
            case 't':
               x = gfx_xpos();
               y = gfx_ypos();
               gfx_color(0, 200, 0);
               gfx_line(x - 25, y - (50 * sin(-M_PI / 6)), x + 25, y - (50 * sin(-M_PI / 6)));
               gfx_line(x - 25, y - (50 * sin(-M_PI / 6)), x, y + (50 * sin(-M_PI / 6)));
               gfx_line(x, y + (50 * sin(-M_PI / 6)), x + 25, y - (50 * sin(-M_PI / 6)));
               break;
            case 'c':
               x = gfx_xpos();
               y = gfx_ypos();
               gfx_color(255, 255, 255);
               gfx_circle(x, y, 25);
               break;
            case '3':
               polygon(r, 3);
               break;
            case '4':
               polygon(r, 4);
               break;
            case '5':
               polygon(r, 5);
               break;
            case '6':
               polygon(r, 6);
               break;
            case '7':
               polygon(r, 7);
               break;
            case '8':
               polygon(r, 8);
               break;
            case '9':
               polygon(r, 9);
               break;
            case 'q':
               loop = 0;
               break;
         }
      }
   }

   return 0;
}

void polygon(int r, int nsides)
{
   int x, y;
   int x1, y1;
   int x2, y2;
   int i;
   double theta;
   
   x = gfx_xpos();
   y = gfx_ypos();
   x1 = x + r;
   y1 = y;
   gfx_color(200, 25, 240);
   theta = 2 * M_PI / nsides;

   for(i = 1; i <= nsides; i++){
      x2 = r * cos(i * theta) + x;
      y2 = r * sin(i * theta) + y;
      gfx_line(x1, y1, x2, y2);
      x1 = x2;
      y1 = y2;
   }
}
