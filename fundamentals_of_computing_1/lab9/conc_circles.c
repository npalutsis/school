// conc_circles.c
// draws concentric circles centered at the mouse click location

#include <stdio.h>
#include "gfx3.h"

void circles( int x, int y, float r );

int main()
{
   char c;
   int wd = 600, ht = 600;

   gfx_open(wd, ht, "concentric circles");
   while(1) {
      gfx_text(100, 20, "click anywhere to see circles; hit 'q' to quit");
      if ((c = gfx_wait()) == 'q') break;
      gfx_clear();
      circles(gfx_xpos(), gfx_ypos(), 200);  // first (outside) circle
   }
}

void circles( int x, int y, float r )
{
   gfx_circle(x, y, r);      // draw a circle
   usleep(10000); gfx_flush();
   if(r < 2) return;         // base case
   circles(x, y, r*0.75);    // recursive step
}

