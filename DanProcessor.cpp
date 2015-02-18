/***************************************************************************//**
 * DanProcessor.cpp
 *
 * Author - Dan Andrus
 *
 * Date - January 30, 2015
 *
 * Details - Defines some basic point processes that can be applied to images.
 * To be used with QT image library, or QT for short.
 *
 ******************************************************************************/


#include "DanProcessor.h"


/***************************************************************************//**
 * Menu_DanFunctions_Negate
 * Author - Dan Andrus
 *
 * Negates both color and grayscale images.
 *
 * Parameters - 
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DanProcessor::Menu_DanFunctions_Negate(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  unsigned char lutable[256] = {0};
  
  // Build lookup table
  for (int i = 0; i < 256; i++)
    lutable[i] = 255-i;
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Negate each pixel
      image[i][j].SetRGB((lutable[image[i][j].Red()]),
                         (lutable[image[i][j].Green()]),
                         (lutable[image[i][j].Blue()]));
    }
  }
  
  return true;
}
