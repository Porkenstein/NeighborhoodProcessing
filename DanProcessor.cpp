/***************************************************************************//**
 * DanProcessor.cpp
 *
 * Author - Dan Andrus
 *
 * Date - February 26, 2015
 *
 * Details - Defines some basic neighborhood processes that can be applied to
 * images. To be used with QT image library.
 *
 ******************************************************************************/
#include "DanProcessor.h"


/***************************************************************************//**
 * Menu_Smoothing_3x3SmoothingFilter
 * Author - Dan Andrus
 *
 * Smooths an image using a 3x3 smoothing filter
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DanProcessor::Menu_Smoothing_3x3SmoothingFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  bool result;
  
  // Build filter mask
  int** mask = alloc2d(3, 3);
  
  // Indendation + brackets for visual reasons
  {
    mask[0][0] = 1;
    mask[0][1] = 2;
    mask[0][2] = 1;
    
    mask[1][0] = 2;
    mask[1][1] = 4;
    mask[1][2] = 2;
    
    mask[2][0] = 1;
    mask[2][1] = 2;
    mask[2][2] = 1;
  }
  
  // Apply filter to image
  result = filterAverage(image, mask, 3, 3);
  
  dealloc2d(mask, 3, 3);
  
  return result;
}

/***************************************************************************//**
 * Menu_OS_PlusShapedMedianFilter
 * Author - Dan Andrus
 *
 * Slightly blurs an image or attempts to remove noise from an image using a
 * plus-shaped 3x3 median filter
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DanProcessor::Menu_RankOrderFilters_PlusShapedMedianFilter(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  bool result;
  
  // Build filter mask
  int** mask = alloc2d(3, 3);
  
  // Indendation + brackets for visual reasons
  {
    mask[0][0] = 0;
    mask[0][1] = 1;
    mask[0][2] = 0;
    
    mask[1][0] = 1;
    mask[1][1] = 1;
    mask[1][2] = 1;
    
    mask[2][0] = 0;
    mask[2][1] = 1;
    mask[2][2] = 0;
  }
  
  // Apply filter to image
  result = filterMedian(image, mask, 3, 3);
  
  dealloc2d(mask, 3, 3);
  
  return result;
}

