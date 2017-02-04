// example to test a key press; the key will be displayed at the terminal
#include <stdio.h>
#include "gfx.h"

int main()
{
  int wd = 500;  // window width
  int ht = 400;  // window height
  char c; 

  // Open a new window for drawing.
  gfx_open(wd, ht, "My window");

  while(1) {
    c = gfx_wait();       // wait for the user to hit a key
    printf("%c\n", c);    // display the key's character
    if (c == 'q') break;  // quit when a 'q' is pressed
  }

  return 0;
}

