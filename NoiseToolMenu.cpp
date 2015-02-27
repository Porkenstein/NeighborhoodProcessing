#include "NoiseToolMenu.h"


/***************************************************************************//**
 * Menu_NoiseTools_NoiseCleanFilter
 * Author - Derek Stotz
 *
 * Applies an out-of-range noise cleaning filter which requests high and low thresholds
 * from the user.  If a pixel is found to be out of range, its value is replaced with
 * the median neigbor pixel value.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool NoiseToolMenu::Menu_NoiseTools_NoiseCleanFilter(Image& image)
{
  return filterStatistic(image, NoiseClean);
}

/***************************************************************************//**
 * Menu_NoiseTools_AddGaussianNoise
 * Author - Derek Stotz
 *
 * Adds Gaussian Noise to an image.  Asks the user for a standard devaition.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool NoiseToolMenu::Menu_NoiseTools_AddGaussianNoise(Image &image)
{
    double stddev = 0.0;

    // Propt user for standard deviation
    if (!Dialog("Gaussian Noise").Add(stddev, "Standard Deviation").Show())
      return false;

   gaussianNoise(image, stddev);
   return true;
}

/***************************************************************************//**
 * Menu_PointProcesses_ModifiedContrastStretch
 * Author - Derek Stotz
 *
 * Adds Impulse Noise to an image.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool NoiseToolMenu::Menu_NoiseTools_AddImpulseNoise(Image &image)
{
    int probability = 0;

    // Propt user for standard deviation
    if (!Dialog("Impulse Noise").Add(probability, "Standard Deviation", 0, 100).Show())
      return false;

    return impulseNoise(image, 100 - probability);
}
