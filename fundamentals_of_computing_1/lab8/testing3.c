#include <stdio.h>
#include "gfx3.h"

int main()
{
  // initialize a point (using X11's Xpoint struct)
  XPoint xp = {300,450};

  // set up 3 arrays of points
  XPoint mypts1[] = { {50,60},{400,120},{200,150},{100,100} };
  XPoint mypts2[] = { {550,160},{330,220},{500,450},{650,300},{550,160} };
  XPoint mypts3[] = { {150,160},{300,350},{200,400},{220,350},{100,300} };
  // determine their sizes
  int sz1 = sizeof(mypts1)/sizeof(XPoint);
  int sz2 = sizeof(mypts2)/sizeof(XPoint);
  int sz3 = sizeof(mypts3)/sizeof(XPoint);

  // get the screen's dimensions, and open a window about 2/3 its size
  int wd = gfx_screenwidth();
  int ht = gfx_screenheight(); 
  gfx_open(wd*0.65, ht*0.65, "My window"); 

  char c = 1;
  while(c != 'q') { 
    gfx_clear(); 

    gfx_color(255,255,255);
    gfx_point(xp.x,xp.y);           // plot the point
    gfx_circle(xp.x,xp.y,10);       // draw a small cirecle around it

    gfx_changefont("-misc-fixed-bold-r-normal--13-120-75-75-c-70-iso8859-1");
    gfx_text(250,500,"  notice the point");
    gfx_changefont("6x10");
    gfx_text(250,520,"  (inside the circle)");

    gfx_color(255,255,0);
    gfx_polygon(mypts1, sz1);       // draw the open polygon
    gfx_polygon(mypts2, sz2);       // draw the closed polygon

    gfx_color(0,255,255);
    gfx_fill_polygon(mypts3, sz3);  // draw the filled polygon

    gfx_flush();
    c = gfx_wait();
  }
}

