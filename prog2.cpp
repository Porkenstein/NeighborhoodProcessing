/*****************************************************************

Program: Prog2 (Neighborhood Processes)

Class: CSC 442, Introduction to Image Processing

Professor: Dr. John Weiss

Meeting Time & Place: 9:00 am M-W-F in McLaury 305

Authors: Derek Stotz, Dan Andrus (QtImageLib by Dr. John Weiss)

Last Modified: Feb 26, 2015

Compiling: Run qmake to build make file, then run make to compile program.

Usage:   ./prog2

Details - The purpose of this assignment was to implement most of the neighborhood
 *         processess described in class.  While the GUI elements were provided
 *         by Qt and QtImageLib, the only code we had to implement was for
 *         modifying the images themselves.  Each function of ours was passed
 *         a QtImageLib image, which acted as a 2 dimensional array of pixel
 *         information.  We were able to push the images through filters and masks
 *         to complte our neighborhood processes (this was done largely through
 *         brute force.)
 *
 *         Our rank order processes had specificable filter sizes and used an enum
 *         and a switch statement for code reuse.  The traversal through the image
 *         was done in one function, and a switch statement in the nested loop
 *         determined which filter was applied to each pixel neighborhood.
 *
 *         The masks used for edge detection were created and handled largeley the
 *         same, but the unique nature of each edge detection process required us to
 *         have a different function for each edge operator type (one for sobel, one
 *         for kirsch, etc).  However, the distinction between setting the new image
 *         intensities to values corresponding to edge magnitudes and setting
 *         the new image intensities to values corresponding to edge directions was
 *         done in the sobel and kirsch functions.

 *         We split our work roughly in half, as before.   Derek did most of the
 *         Rank order filters, while Dan did most of the Edge detection.  The
 *         rest of the work was done together.  Extensive refactoring was done near
 *         the end to improve the coding style.


 Recommended Usage -
 *           Simply open an image using the open icon and modify it using the functions
 *           found under the menus.  To reset the image, press the back arrow in the
 *           image window.

 Issues and Bugs - None to speak of.  The filters are not terribly optimized, and may
            be slow when applied to larger images.

            One coding style issue which still remains is the inclusion of "EdgeDetectionMenu.cpp"
            rather than "EdgeDetectionMenu.h" in prog2.cpp.  This is due to a qt error which
            we could not resolve which popped up when including the latter instead of the former.
 *****************************************************************/

#include "RankOrderFilterMenu.h"
#include "NoiseToolMenu.h"
#include "PointProcessor.h"
#include "EdgeDetectionMenu.cpp"
#include "SmoothingMenu.h"

/***************************************************************************//**
 * main
 * Author - Derek Stotz, Dan Andrus
 *
 * Sets up the image app, adds the menu classes and starts the GUI.
 *
 * Parameters -
            argc - the number of command line arguments (unused)
            argv - the command line arguments (unused)
 *
 * Returns
 *          an error code returned by app.Start();
 ******************************************************************************/
int main(int argc, char** argv)
{
  NoiseToolMenu ntm;
  RankOrderFilterMenu rofm;
  PointProcessor ilp;
  EdgeDetectionMenu edm;
  SmoothingMenu sm;

  ImageApp app(argc, argv);

  app.AddActions(&ntm);
  app.AddActions(&rofm);
  app.AddActions(&ilp);
  app.AddActions(&edm);\
  app.AddActions(&sm);
  return app.Start();
}

