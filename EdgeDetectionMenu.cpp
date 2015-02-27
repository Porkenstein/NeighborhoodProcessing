/***************************************************************************//**
 * EdgeDetectionMenu.cpp
 *
 * Author - Dan Andrus
 *
 * Date - February 26, 2015
 *
 * Details - Defines some basic edge detection neighborhood processes that can
 * be applied to images. To be used with QT image library.
 *
 ******************************************************************************/

#include "EdgeDetectionMenu.h"

/***************************************************************************//**
 * Menu_EdgeDetection_3x3SharpeningFilter
 * Author - Dan Andrus
 *
 * Sharpens an image using a 3x3 mask.
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool EdgeDetectionMenu::Menu_EdgeDetection_3x3SharpeningFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  bool result;
  
  // Build filter mask
  int** mask = alloc2d(3, 3);
  
  // Indendation + brackets for visual reasons
  {
    mask[0][0] = 0;
    mask[0][1] = -1;
    mask[0][2] = 0;
    
    mask[1][0] = -1;
    mask[1][1] = 5;
    mask[1][2] = -1;
    
    mask[2][0] = 0;
    mask[2][1] = -1;
    mask[2][2] = 0;
  }
  
  // Apply filter to image
  result = filterAverage(image, mask, 3, 3);
  
  dealloc2d(mask, 3, 3);
  
  return result;
}

/***************************************************************************//**
 * Menu_EdgeDetection_Emboss
 * Author - Dan Andrus
 *
 * Embosses an image
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool EdgeDetectionMenu::Menu_EdgeDetection_Emboss(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  bool result;
  
  // Build filter mask
  int** mask = alloc2d(3, 3);
  
  // Indendation + brackets for visual reasons
  {
    mask[0][0] = 1;
    mask[0][1] = 0;
    mask[0][2] = 0;
    
    mask[1][0] = 0;
    mask[1][1] = 0;
    mask[1][2] = 0;
    
    mask[2][0] = 0;
    mask[2][1] = 0;
    mask[2][2] = -1;
  }
  
  // Apply filter to image
  result = filterEmboss(image, mask, 3, 3);
  
  dealloc2d(mask, 3, 3);
  
  return result;
}

/***************************************************************************//**
 * Menu_EdgeDetection_Laplacian
 * Author - Dan Andrus
 *
 * Highlights images using a Laplacian filter
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool EdgeDetectionMenu::Menu_EdgeDetection_Laplacian(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  bool result;
  
  // Build filter mask
  int** mask = alloc2d(3, 3);
  
  // Indendation + brackets for visual reasons
  {
    mask[0][0] = -1;
    mask[0][1] = -1;
    mask[0][2] = -1;
    
    mask[1][0] = -1;
    mask[1][1] = 8;
    mask[1][2] = -1;
    
    mask[2][0] = -1;
    mask[2][1] = -1;
    mask[2][2] = -1;
  }
  
  // Apply filter to image
  result = filterAverage(image, mask, 3, 3, true);
  
  dealloc2d(mask, 3, 3);
  
  return result;
}

/***************************************************************************//**
 * Menu_EdgeDetection_SobelMagnitudes
 * Author - Dan Andrus
 *
 * Highlights edges using Sobel edge detection masks
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool EdgeDetectionMenu::Menu_EdgeDetection_SobelMagnitudes(Image& image)
{
  if (image.IsNull()) return false;
  bool result;
  
  result = sobel(image, true);
  
  return result;
}

/***************************************************************************//**
 * Menu_EdgeDetection_SobelDirections
 * Author - Dan Andrus
 *
 * Illustrates edge directions using Sobel edge detection masks.
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool EdgeDetectionMenu::Menu_EdgeDetection_SobelDirections(Image& image)
{
  if (image.IsNull()) return false;
  bool result;
  
  result = sobel(image, false);
  
  return result;
}

/***************************************************************************//**
 * Menu_EdgeDetection_KirschEdgeMagnitude
 * Author - Derek Stotz
 *
 * Applies Kirsch Edge Detection to an image.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DerekProcessor::Menu_EdgeDetection_KirschMagnitude(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;

  // Initialize variables
  Image copy;                           // Copy of original image
  int img_w;                            // Overal image width
  int img_h;                            // Overal image height
  int max;                              // Magnitude of max response
  int sum[8];                           // Sum of responsivenesses
  int center_x;                         // Center of mask
  int center_y;                         // Center of mask
  int i, j, k, l, m, x, y;              // Temporary variables
  int mask[8][3][3] = {{
    {-3, -3,  5},
    {-3,  0,  5},
    {-3, -3,  5}
  }, {
    {-3,  5,  5},
    {-3,  0,  5},
    {-3, -3, -3}
  }, {
    { 5,  5,  5},
    {-3,  0, -3},
    {-3, -3, -3}
  }, {
    { 5,  5, -3},
    { 5,  0, -3},
    {-3, -3, -3}
  }, {
    { 5, -3, -3},
    { 5,  0, -3},
    { 5, -3, -3}
  }, {
    {-3, -3, -3},
    { 5,  0, -3},
    { 5,  5, -3}
  }, {
    {-3, -3, -3},
    {-3,  0, -3},
    { 5,  5,  5}
  }, {
    {-3, -3, -3},
    {-3,  0,  5},
    {-3,  5,  5}
  }};
  int mask_w = 3;
  int mask_h = 3;

  // Copy image due to nature of algorithm
  copy = image;

  // Get image dimensions
  img_w = image.Width();
  img_h = image.Height();

  // Find center of mask
  center_x = 1;
  center_y = 1;

  // Begin applying mask to image
  for (i = 0; i < img_h; ++i)           // Loop over rows
  {
    for (j = 0; j < img_w; ++j)         // Loop over columns
    {
      // Reset variables
      max = -1;
      for (m = 0; m < 8; ++m)
        sum[m] = 0;

      // Center each mask over pixel
      for (k = 0; k < mask_h; ++k)      // Loop over mask rows
      {
        for (l = 0; l < mask_w; ++l)    // Loop over mask columns
        {
          for (m = 0; m < 8; ++m)       // Loop over all masks
          {
            // Temporarily store variable of current pixel we're going to sum
            x = j + (l - center_x);
            y = i + (k - center_y);

            // If a pixel would be out of bounds, use nearest valid pixel
            if (x < 0)      x = 0;
            if (x >= img_w) x = img_w - 1;
            if (y < 0)      y = 0;
            if (y >= img_h) y = img_h - 1;

            // Add intensity values to sum with weights
            sum[m] += copy[y][x].Intensity() * mask[m][k][l];
          }
        }
      }

      // Find mask with max response
      for (m = 0; m < 8; ++m)
      {
        if (sum[m] > max)
        {
          // clip the max sum
          max = std::max(0,min(255, sum[m]));
        }
      }

      // Put new intensity into image
      image[i][j].SetGray(min(255, max));
    }
  }

  return true;
}

/***************************************************************************//**
 * Menu_EdgeDetection_KirschDirections
 * Author - Dan Andrus
 *
 * Illustrates edge directions using the Kirsch compass edge detection masks.
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool EdgeDetectionMenu::Menu_EdgeDetection_KirschDirections(Image& image)
{
  if (image.IsNull()) return false;
  bool result;
  
  result = kirschDir(image);
  
  return result;
}

/***************************************************************************//**
 * Menu_EdgeDetection_StandardDeviationEdgeDetection
 * Author - Derek Stotz
 *
 * Detects edges in an image by applying pixel intensities determined by the standard
 * deviation of the surround neighborhood of pixel values.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DerekProcessor::Menu_EdgeDetection_StandardDeviation(Image& image)
{
  return this->filterStatisticGreyscale(image, StandardDeviation);
}

/***************************************************************************//**
 * Menu_EdgeDetection_RangeFilter
 * Author - Derek Stotz
 *
 * Replaces pixel values with the maxium - minimum pixel values in their
 * neighborhood in order to emphasize edges.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DerekProcessor::Menu_EdgeDetection_RangeFilter(Image& image)
{
  return this->filterStatisticGreyscale(image, Range);
}

