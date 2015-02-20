/***************************************************************************//**
 * DerekProcessor.cpp
 *
 * Author - Derek Stotz
 *
 * Date - February 26, 2015
 *
 * Neighborhood process functions implemented by Derek Stotz.  These functions are
 * named for easy addition into the image app created in prog2.cpp.
 ******************************************************************************/

#include "DerekProcessor.h"
#include <cmath>
#include <string>
#include <qfiledialog.h>
#include <stdlib.h>


/***************************************************************************//**
 * Menu_DerekFunctions_ApplyGamma
 * Author - Derek Stotz
 *
 * Applies a gamma transform to an image.  The gamma is requested as input.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DerekProcessor::Menu_DerekFunctions_ApplyGamma(Image& image)
{
  static unsigned char memory[3][256] = {{0},{0},{0}};

  double gamma = 0.0;

  // prompt the user for the gamma

  // Propt user for threshold value
  if (!Dialog("Gamma Correction").Add(gamma, "Gamma Value").Show())
    return false;

  // build a lookup table

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 256; j++)
      memory[i][j] = (char)(pow((j/255.0), gamma)*255.0);

  if (image.IsNull()) return false;

  int rows = image.Height();
  int cols = image.Width();

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      image[i][j].SetRed(memory[0][image[i][j].Red()]);
      image[i][j].SetGreen(memory[1][image[i][j].Green()]);
      image[i][j].SetBlue(memory[2][image[i][j].Blue()]);
    }
  }
  return true;
}

/***************************************************************************//**
 * Menu_DerekFunctions_MinMaxStandardDeviationEdgeDetection
 * Author - Derek Stotz
 *
 * Applies a so-called "Min-Max Standard Deviation" edge detection filter to the image.
 * this is based on the filter invented for a senior design project in 2014, and is being
 * implemented out of curiosity.  Each pixel is shaded with an intensity proportional to the
 * size of the maximum standard deviation between any two sides of any of 8 regional bifurcations.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DerekProcessor::Menu_DerekFunctions_MinMaxStandardDeviationEdgeDetection(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_NoiseCleanFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_MeanFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_KirschEdgeDetection(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_MedianFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_KirschEdgeMagnitude(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_MinimumFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_StandardDeviationEdgeDetection(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_MaximumFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_RangeFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

