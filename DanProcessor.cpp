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


bool DanProcessor::filter(Image& image, int** mask, int mask_w, int mask_h)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  // Initialize variables
  Image copy;                           // Copy of original image
  int img_w;                            // Overal image width
  int img_h;                            // Overal image height
  int mask_sum;                         // Sum of numbers in mask
  int sum[3];                           // Sum of all colors
  int center_x;                         // Center of mask
  int center_y;                         // Center of mask
  int temp, i, j, k, l, x, y;           // Temporary variables
  
  // Copy image due to nature of algorithm
  copy = image;
  
  // Get image dimensions
  img_w = image.Width();
  img_h = image.Height();
  
  // Calculate mask total
  mask_sum = 0;
  for (i = 0; i < mask_h; ++i)
    for (j = 0; j < mask_w; ++j)
      mask_sum += mask[i][j];
  
  // Find center of mask. If mask is even x even, take top-left of center 4
  center_x = mask_w / 2 - (1 - mask_w % 2);
  center_y = mask_h / 2 - (1 - mask_h % 2);
  
  // Begin applying mask to image
  for (i = 0; i < img_h; ++i)           // Loop over rows
  {
    for (j = 0; j < img_w; ++j)         // Loop over columns
    {
      // Reset variables
      sum[0] = 0;
      sum[1] = 0;
      sum[2] = 0;
      
      // Center mask over pixel and take weighted average
      for (k = 0; k < mask_h; ++k)      // Loop over mask rows
      {
        for (l = 0; l < mask_w; ++l)    // Loop over mask columns
        {
          // Temporarily store variable of current pixel to sum
          x = l + (l - center_x);
          y = k + (k - center_y);
          
          // If a pixel would be out of bounds, use nearest valid pixel
          if (x < 0)      x = 0;
          if (x >= img_w) x = img_w - 1;
          if (y < 0)      y = 0;
          if (y >= img_h) y = img_h - 1;
          
          // Add RGB values to sum with weights
          sum[0] = copy[y][x].Red() * mask[k][l];
          sum[1] = copy[y][x].Green() * mask[k][l];
          sum[2] = copy[y][x].Blue() * mask[k][l];
        }
      }
      
      // Average out the sum, truncating decimals
      sum[0] /= mask_sum;
      sum[1] /= mask_sum;
      sum[2] /= mask_sum;
      
      // Clip values should they be invalid
      for (k = 0; k < 3; ++k)
      {
        if (sum[k] < 0)     sum[k] = 0;
        if (sum[k] >= 256)  sum[k] = 256-1; // Why not 255? to match lines 69-72
      }
      
      // Put new RGB values into image
      image[i][j].SetRGB(sum[0], sum[1], sum[2]);
    }
  }
  
  return true;
}

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
bool DanProcessor::Menu_Filters_3x3SmoothingFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  // Copy existing image due to nature of operation
  int mask[3][3] = {
    {1, 2, 1},
    {2, 4, 2},
    {1, 2, 1}
  };
  
  return filter(image, mask, 3, 3);
}
