// a simple animation program
// ( demonstrates the need for gfx_event_waiting() )
#include <stdio.h>
#include <unistd.h>
#include "gfx.h"

int main()
{
  int wd = 500;  // window width
  int ht = 400;  // window height
  int dx = 0;    // basic increment for animation
  char c;

  gfx_open(wd, ht, "My window");  // Open a new window for drawing.

  gfx_color(0,255,0);      // Set the current drawing color.

  while(1) { 
    gfx_clear();
    gfx_line(100+dx,100,150+dx,150);
    gfx_flush;
    dx++;
    usleep(8000);      // pause for 8 millisecons
    if(gfx_event_waiting()) { 
      c = gfx_wait();
      if (c == 'q')  break;
    }
  }

  return 0;
}

