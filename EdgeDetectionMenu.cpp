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

