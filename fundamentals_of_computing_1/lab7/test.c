/* Author: Nick Palutsis
   Class: CSE 20211
   Lab 7
   Date: October 30, 2015 */
   
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "gfx.h"

int main(void)
{
   int x;
   int y;
   int i;
   int r = 40;
   int wd = 1000;
   int ht = 1000;
   char c;
   
   gfx_open(wd, ht, "Bounce");
  
   x = wd / 2;
   y = ht / 2 - 100;
   
   srand(time(NULL));
   gfx_color(rand() % 255, rand() % 255, rand() % 255);
   
   while(1) { 
      gfx_clear();
      gfx_flush;
      
      for(i = 0; i <= r; i++){
         gfx_color(255, 0, 0);
         gfx_line(x - r, y + r, x - 2 * r + i, y - r);
         gfx_line(x + r, y + r, x + 2 * r - i, y - r);
         gfx_line(x - r, y - i, x + r, y - i);
         gfx_line(x - r, y + i, x + r, y + i);
      }
      
      for(i = 0; i <= 80; i++){
         gfx_color(0, 255, 0);
         gfx_line(0, ht - i, wd, ht - i);
      }
      
      gfx_flush;
      usleep(8000);      // pause for set number of seconds
      if(gfx_event_waiting()) { 
         c = gfx_wait();
         if(c == 'q')		// Quits program
            break;
      }
   }
   return 0;
}
