/***************************************************************************//**
 * DerekProcessor.cpp
 *
 * Author - Derek Stotz
 *
 * Date - January 30, 2015
 *
 * Point process functions implemented by Derek Stotz.  These functions are
 * named for easy addition into the image app created in prog1.cpp.
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
