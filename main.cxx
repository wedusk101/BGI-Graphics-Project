// File: eyes.cpp
// Written by Grant Macklem
//      Grant.Macklem@Colorado.EDU
//              2:00 PM Recitation
// Last modified Nov 22, 1998
// Flicker-free eyes!

/*******************************************************************************
* eyes.exe  Flicker-free, mouse-following, customizably-colored eyes.
* Copyright (C) 1998 Grant Macklem
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
* You may contact me, the author by emailing Grant.Macklem@Colorado.EDU
*******************************************************************************/

#include "graphics.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>                     // Provides exit
#include <ctype.h>                      // Provides toupper
using namespace std;

const double XBORDER = 150.0;                                                   // X-border of the screen, cartesian
const double YBORDER = 112.5;                                                   // Y-border of the screen, cartesian

const double X_RAD = 2 * XBORDER / 10.0;                        // Width of eye ellipse, cartesian
const double Y_RAD = 2 * YBORDER / 12;                  // Height of eye, cartesian

const double LEFT_X = -1.5 * X_RAD;                     // X Coordinate of left eye, cartesian
const double LEFT_Y = 0;                                                // Y Coordinate of right eye, cartesian
const double RIGHT_X = 1.5 * X_RAD;                     // X Coordinate of left eye, cartesian
const double RIGHT_Y = 0;                                               // Y Coordinate of right eye, cartesian

const double I_RADIUS = X_RAD / 2.8;                                    // Radius of iris in cartesian
const double P_RADIUS = X_RAD / 10;                                             // Radius of pupil, cartesian

// Draws the new irises
void draw_iris(int x, int y);

int ytranslate
        (double y,                                              // Cartesian Coordinate to be translated into pixles
    double yborder);                            // Top and bottom Cartesian coordinate of the screen

int xtranslate
        (double x,                                              // Cartesian Coordinate to be translated into pixles
    double xborder);                            // Left and right Cartesian coordinate of the screen


// Draws the eye initially
void draw_eyes();
void change_left_color(int x, int y);
void change_right_color(int x, int y);
void check_keys();

// Checks to see if the line from the ellipse center to the mouse is vertical
bool check_vertical
        (int x,                                                 // x location of the mouse
    int y,                                                      // y location of the mouse
    int x1,                                                     // x coordinate of ellipse center
    int y1,                                                     // y coordinate of ellispe center
    double& x_intersect,                        // Return value where iris x-intersects smaller ellipse
    double& y_intersect,                        // Return value where iris y-intersects smaller ellipse
    int small_ellipse_x_radius, // x coord of ellipse of center of iris an pupil
    int small_ellipse_y_radius);// y coord of ellipse of center of iris an pupil

// Returns the radius of the eyes in pixel coordinates
void get_radius_eyes(int& tx_rad, int& ty_rad);

void update_graphics
        (int left_x_intersect,          // x intersection of left iris and pupil
    int left_y_intersect,               // y intersection of left iris and pupil
    int right_x_intersect,              // x intersection of right iris and pupil
    int right_y_intersect,              // y intersection of right iris and pupil
    int ti_rad,                                 // Radius, in pixels, of iris
    int tp_rad,                                 // radius, in pixels, of pupil
    int& t);                                            // Graphics page

void get_radius_iris_pupil
        (int& ti_rad,                                   // Radius of iris, in pixels
    int& tp_rad);                                       // Radius of pupil, in pixels

void find_coordinates
        (int x,                                                 // x location of the mouse
    int y,                                                      // y location of the mouse
    int x1,                                                     // x coordinate of ellipse center
    int y1,                                                     // y coordinate of ellispe center
    double& x_intersect,                        // Return value where iris x-intersects smaller ellipse
    double& y_intersect,                        // Return value where iris y-intersects smaller ellipse
    int small_ellipse_x_radius, // x coord of ellipse of center of iris an pupil
    int small_ellipse_y_radius);// y coord of ellipse of center of iris an pupil


int left_color = GREEN;
int right_color = GREEN;


int APIENTRY WinMain
( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

        cout << "Moving Eyes, Copyright (C) 1998 Grant Macklem.\n" << endl;
   cout << "Press 'Q' to quit" << endl;

   initwindow(601, 451);
    registermousehandler(WM_MOUSEMOVE, draw_iris);
    registermousehandler(WM_LBUTTONDOWN, change_left_color);
    registermousehandler(WM_RBUTTONDOWN, change_right_color);

        // Draw the eyes, but must supply an initial position to look at.
   draw_iris(2,2);

        for(;;) // Infinite loop to keep program running... only quits when user
                        // presses the q key to exit.
   {
                check_keys();
                delay(10);
   }

}

void draw_eyes()
{
   int x1 = xtranslate(LEFT_X, XBORDER);
   int y1 = ytranslate(LEFT_Y, YBORDER);
   int x2 = xtranslate(RIGHT_X, XBORDER);
   int y2 = ytranslate(RIGHT_Y, YBORDER);
   int tx_rad = xtranslate(X_RAD, XBORDER) - xtranslate(0, XBORDER);
   int ty_rad = ytranslate(Y_RAD, YBORDER) - ytranslate(0, YBORDER);

        setcolor(WHITE);
        fillellipse (x1, y1, tx_rad, ty_rad);
   fillellipse (x2, y2, tx_rad, ty_rad);
}

void change_left_color(int x, int y)
{
        left_color ++;                  // Increase color by one
        left_color %= 15;                       // Don't allow white as iris color, since that is eye
                                                                // color.  Also makes sure color is between 0 and 15.
        draw_iris(mousex(),mousey());
}

void change_right_color(int x, int y)
{
        right_color ++;                         // Increase color by one
        right_color %= 15;              // Don't allow white as iris color, since that is eye
                                                                // color.  Also makes sure color is between 0 and 15.
        draw_iris(mousex(),mousey());
}

void draw_iris(int x, int y)
{
   int tx_rad, ty_rad, ti_rad, tp_rad;
   static int t = 0;            // Graphics screen
   // The following are in pixel coordinates of the iris ellipse
   double small_ellipse_x_radius;
   double small_ellipse_y_radius;

        // Center of each eye in pixel coordinates.
   int x1 = xtranslate(LEFT_X, XBORDER);
   int y1 = ytranslate(LEFT_Y, YBORDER);
   int x2 = xtranslate(RIGHT_X, XBORDER);
   int y2 = ytranslate(RIGHT_Y, YBORDER);
        // These variables tell where the line from the center of the eye to the mouse
   // intersects the smaller ellipse (where to draw the iris)
   double left_x_intersect, left_y_intersect, right_x_intersect, right_y_intersect;

   get_radius_eyes(tx_rad, ty_rad);
   get_radius_iris_pupil(ti_rad, tp_rad);

        small_ellipse_x_radius = tx_rad - ti_rad;
        small_ellipse_y_radius = ty_rad - ti_rad;

        // Left Iris
        find_coordinates(x, y, x1, y1, left_x_intersect, left_y_intersect,
        small_ellipse_x_radius, small_ellipse_y_radius);
   // Right Iris
        find_coordinates(x, y, x2, y2, right_x_intersect, right_y_intersect,
        small_ellipse_x_radius, small_ellipse_y_radius);

   update_graphics(left_x_intersect, left_y_intersect, right_x_intersect,
                                         right_y_intersect, ti_rad, tp_rad, t);

}


// Checks to see if the line from the ellipse center to the mouse is vertical
bool check_vertical
        (int x,                                                 // x location of the mouse
    int y,                                                      // y location of the mouse
    int x1,                                                     // x coordinate of ellipse center
    int y1,                                                     // y coordinate of ellispe center
    double& x_intersect,                        // Return value where iris x-intersects smaller ellipse
    double& y_intersect,                        // Return value where iris y-intersects smaller ellipse
    int small_ellipse_y_radius) // y coord of ellipse of center of iris an pupil
{
        // Center of each eye in pixel coordinates.
        if (x == x1)
   {
      x_intersect = x;

                if (abs(y1 - y) >= small_ellipse_y_radius)
      { // Pointer is outside the eye
        if ((y1 - y) > 0)
                y_intersect = y1 - small_ellipse_y_radius;
         else
                y_intersect = y1 + small_ellipse_y_radius;
      }
      else      // Pointer is in the eye
        y_intersect = y;

      return true;
   }
   return false;
}

void find_coordinates
        (int x,                                                 // x location of the mouse
    int y,                                                      // y location of the mouse
    int x1,                                                     // x coordinate of ellipse center
    int y1,                                                     // y coordinate of ellispe center
    double& x_intersect,                        // Return value where iris x-intersects smaller ellipse
    double& y_intersect,                        // Return value where iris y-intersects smaller ellipse
    int small_ellipse_x_radius, // x coord of ellipse of center of iris an pupil
    int small_ellipse_y_radius) // y coord of ellipse of center of iris an pupil
{
        bool vertical;
        // Fraction variables to calculate intersection points
   double numerator, denominator, slope;

        vertical = check_vertical(x, y, x1, y1, x_intersect, y_intersect,
        small_ellipse_y_radius);
   if (!vertical)
        {       // Find slope of line from center of eye to mouse pointer, pixel coords
                slope = ((double)(y1 - y)) / ((double)(x - x1));

                // Pixel coords
                numerator = pow(small_ellipse_x_radius, 2.0) * pow(small_ellipse_y_radius, 2.0);
           denominator = pow(small_ellipse_y_radius, 2.0) + pow(small_ellipse_x_radius, 2.0) * pow(slope, 2.0);

                x_intersect = sqrt(numerator / denominator);
           y_intersect = slope * x_intersect;

           if (x < x1)
                x_intersect = -(abs(x_intersect));
           else
                   x_intersect = abs(x_intersect);

           if (y < y1)
                y_intersect = -(abs(y_intersect));
           else
                   y_intersect = abs(y_intersect);

                x_intersect += x1;
                y_intersect += y1;

           if ( (pow(x - x1,2.0) / pow(small_ellipse_x_radius, 2.0) + pow(y1 - y, 2.0) / pow(small_ellipse_y_radius, 2.0)) < 1)
           {    // Point is inside the eye ellipse
                x_intersect = x;
              y_intersect = y;
           }
   }    // end if not vertical
}


void get_radius_eyes(int& tx_rad, int& ty_rad)
{
        // Radii of the eyes in pixel coordinates
   tx_rad = xtranslate(X_RAD, XBORDER) - xtranslate(0, XBORDER);
   ty_rad = ytranslate(0, YBORDER) - ytranslate(Y_RAD, YBORDER);
}

void get_radius_iris_pupil(int& ti_rad, int& tp_rad)
{
        // Radii of the iris and pupil, respectively, in pixel coordinates
   ti_rad = xtranslate(I_RADIUS, XBORDER) - xtranslate(0, XBORDER);
   tp_rad = xtranslate(P_RADIUS, XBORDER) - xtranslate(0, XBORDER);
}


void update_graphics(int left_x_intersect, int left_y_intersect,
        int right_x_intersect, int right_y_intersect, int ti_rad, int tp_rad, int& t)
{
        int active_page = t % 2;

        setactivepage(active_page);
        clearviewport();
        setfillstyle( SOLID_FILL, WHITE );
   draw_eyes();
        // Left Iris
   setcolor (left_color);
   setfillstyle( SOLID_FILL, left_color );
   fillellipse(left_x_intersect, left_y_intersect, ti_rad, ti_rad);

   // Left Pupil
   setcolor (BLACK);
   setfillstyle( SOLID_FILL, BLACK );
   fillellipse(left_x_intersect, left_y_intersect, tp_rad, tp_rad);

        // Right Iris
   setcolor (right_color);
   setfillstyle( SOLID_FILL, right_color );
   fillellipse(right_x_intersect, right_y_intersect, ti_rad, ti_rad);

   // Right Pupil
   setcolor (BLACK);
   setfillstyle( SOLID_FILL, BLACK );
   fillellipse(right_x_intersect, right_y_intersect, tp_rad, tp_rad);

   t++;
   setvisualpage(active_page);
}


void check_keys()
{
        int command;


        if (kbhit()== true)
   {
      command = toupper(getch());
        if (char(command) == 'Q')
        {
        cout << "Exiting..." << endl;
        exit (EXIT_SUCCESS);
      }
   }
}


// ******************** User X-Coordinate Translate Function *******************
// Translate the user inputted x-coordinate to a screen coordinate
int xtranslate (double x, double xborder)
{
        // This function assumes that you want to plot horizontal values that range from
   // -xborder (on the left of the graphics screen) to +xborder (on the right of
   // the graphics screen).
   // The return value of this function tells the x-pixel value that corresponds
   // to the parameter x.

   double percent;              // Percent of x-hemisphere (positive or negative) where
                                                        // user defined coordinate is located
        int maxx = getmaxx();
   int x_value;                 // Corresponding graphical x-value

   percent = x / xborder;       // Finds, percentagewise, how far the user defined
                                                                // coordinate is located from the y-axis.

   // Calculates the graphical x-value by adding to the x-value at the center of
   // the screen the percentage further that the user defined x is located.  Note
   // that if percentage is negative (meaning the user x-coorinate was negative)
   // that the following step will be a subtraction.
   x_value = maxx/2 + percent * (maxx/2);

   return (int)x_value;
}


// ******************** User Y-Coordinate Translate Function *******************
// Translate the user inputted y-coordinate to a screen coordinate
int ytranslate (double y, double yborder)
{
        // This function assumes that you want to plot vertical values that range from
   // -yborder (on the bottom of the graphics screen) to +yborder (on the topof
   // the graphics screen).
   // The return value of this function tells the y-pixel value that corresponds
   // to the parameter y.

   float percent;               // Percent of y-hemisphere (positive or negative) where
                                                // user defined coordinate is located
        int maxy = getmaxy();
   int y_value;         // Corresponding graphical y-value

   percent = -y / yborder;      // Finds, percentagewise, how far the user defined
                                                                // coordinate is located from the x-axis.  Since the
                           // y-values run opposite from expected, the negative
                           // sign is necessary.

   // Calculates the graphical y-value by adding to the y-value at the center of
   // the screen the percentage further that the user defined y is located.  Note
   // that if percentage is negative (meaning the user y-coorinate was negative)
   // that the following step will be a subtraction.
   y_value = maxy/2 + percent * (maxy/2);

   return (int)y_value;
}
