// a simple event-driven program
// the line color changes for certain key presses
#include <stdio.h>
#include "gfx.h"

int main()
{
  int wd = 500;  // window width
  int ht = 400;  // window height
  int loop = 1;
  char c;

  gfx_open(wd, ht, "My window");  // Open a new window for drawing.

  gfx_color(0,0,255);      // Set the current drawing color (blue)

  while(loop) {
    gfx_clear();                 // clear the window 
    gfx_line(150,300,350,100);   // draw a line
    gfx_flush();                 // flush all output to the window

    c = gfx_wait();              // wait for user input
    switch(c) {
      case 'r':
        gfx_color(255,0,0);      // change to red if 'r' is pressed
        break;
      case 'g':
        gfx_color(0,255,0);      // change to green if 'g' is pressed
        break;
      case 'b':
        gfx_color(0,0,255);      // change to blue if 'b' is pressed
        break;
      case 'y':
        gfx_color(255,255,0);    // change to blue if 'b' is pressed
        break;
      case 'q':                  // quit if 'q' is pressed
        loop = 0;
    }
  }

  return 0;
}

