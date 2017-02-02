/* Author: Nick Palutsis
   Class: CSE 20211
   Lab 7
   Date: October 30, 2015 */
   
#include <stdio.h>
#include <unistd.h>
#include "gfx.h"

int main()
{
  int wd = 1000;  // window width
  int ht = 1000;  // window height
  int dx;
  int dy;    // basic increment for animation
  int waittime;
  int x;
  int y;
  char c;

  gfx_open(wd, ht, "Bounce");  // Open a new window for drawing.
  
  x = wd / 2;	// Starts ball in center of the screen
  y = ht / 2;
  
  srand(time(NULL));
  dx = rand() % 4;	// Randomizes the direction
  dy = rand() % 4;
  waittime = (((rand() % 20) + 5) * 1000);	// Randomizes the sleep time
  gfx_color(rand() % 255, rand() % 255, rand() % 255);      // Set the current drawing color randomly

  while(1) { 
    gfx_clear();
    gfx_circle(x, y, 40);
    gfx_flush;
    x = x + dx;
    y = y + dy;
    usleep(waittime);      // pause for set number of seconds
    if(gfx_event_waiting()) { 
       c = gfx_wait();
       if(c == 'q')		// Quits program
          break;
       else if(c == 1){		// Randomizes everything on mouse click
          x = gfx_xpos();
          y = gfx_ypos();
          dx = (rand() % 10) - 5;
          dy = (rand() % 10) - 5;
          waittime = (((rand() % 20) + 5) * 1000);
          gfx_color(rand() % 255, rand() % 255, rand() % 255);
       }
    }
    if((x <= 25 || x >= (wd - 25)) && (y <= 25 || y >= (ht - 25))){		// Changes direction if ball hits corner
       dx = -dx;
       dy = -dy;
    }
    else if(x <= 25 || x >= (wd - 25))		// Changes direction if ball hits left or right wall
       dx = -dx;
    else if(y <= 25 || y >= (ht - 25))		// Changes direction if ball hits top or bottom wall
       dy = -dy;
  }

  return 0;
}
