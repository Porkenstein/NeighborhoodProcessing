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


bool DanProcessor::filterAverage(Image& image, int** mask, int mask_w, int mask_h, bool gray = false)
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
  int i, j, k, l, x, y;                 // Temporary variables
  
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
  
  // Avoid division by 0
  if (mask_sum < 1) mask_sum = 1;
  
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
          x = j + (l - center_x);
          y = i + (k - center_y);
          
          // If a pixel would be out of bounds, use nearest valid pixel
          if (x < 0)      x = 0;
          if (x >= img_w) x = img_w - 1;
          if (y < 0)      y = 0;
          if (y >= img_h) y = img_h - 1;
          
          // Add RGB values to sum with weights
          sum[0] += copy[y][x].Red() * mask[k][l];
          sum[1] += copy[y][x].Green() * mask[k][l];
          sum[2] += copy[y][x].Blue() * mask[k][l];
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
      
      // Convert to grayscale if gray is set
      if (gray)
        image[i][j].SetGray(image[i][j]);
    }
  }
  
  return true;
}

bool DanProcessor::filterMedian(Image& image, int** mask, int mask_w, int mask_h)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  // Initialize variables
  Image copy;                           // Copy of original image
  int img_w;                            // Overal image width
  int img_h;                            // Overal image height
  int median[3];                        // Median of all colors
  int center_x;                         // Center of mask
  int center_y;                         // Center of mask
  int i, j, k, l, x, y;                 // Temporary variables
  
  vector<int> red_list;                 // Intensity values for red
  vector<int> gre_list;                 // Intensity values for green
  vector<int> blu_list;                 // Intensity values for blu
  
  // Copy image due to nature of algorithm
  copy = image;
  
  // Get image dimensions
  img_w = image.Width();
  img_h = image.Height();
  
  // Find center of mask. If mask is even x even, take top-left of center 4
  center_x = mask_w / 2 - (1 - mask_w % 2);
  center_y = mask_h / 2 - (1 - mask_h % 2);
  
  // Begin applying mask to image
  for (i = 0; i < img_h; ++i)           // Loop over rows
  {
    for (j = 0; j < img_w; ++j)         // Loop over columns
    {
      // Reset variables
      red_list.clear();
      gre_list.clear();
      blu_list.clear();
      median[0] = 0;
      median[1] = 0;
      median[2] = 0;
      
      // Center mask over pixel and take weighted average
      for (k = 0; k < mask_h; ++k)      // Loop over mask rows
      {
        for (l = 0; l < mask_w; ++l)    // Loop over mask columns
        {
          // Skip if value in mask is 0
          if (mask[k][l] == 0) continue;
          
          // Temporarily store location of pixel in mask
          x = j + (l - center_x);
          y = i + (k - center_y);
          
          // If a pixel would be out of bounds, use nearest valid pixel
          if (x < 0)      x = 0;
          if (x >= img_w) x = img_w - 1;
          if (y < 0)      y = 0;
          if (y >= img_h) y = img_h - 1;
          
          // Add RGB values to lists
          red_list.push_back(copy[y][x].Red());
          gre_list.push_back(copy[y][x].Green());
          blu_list.push_back(copy[y][x].Blue());
        }
      }
      
      // Sort lists
      sort(red_list.begin(), red_list.end());
      sort(gre_list.begin(), gre_list.end());
      sort(blu_list.begin(), blu_list.end());
      
      // Calculate medians
      median[0] = red_list[red_list.size() / 2];
      if (red_list.size() % 2 == 0 && red_list.size() > 0)
        median[0] = (median[0] + red_list[(red_list.size() / 2) - 1]) / 2;
      
      median[1] = gre_list[gre_list.size() / 2];
      if (gre_list.size() % 2 == 0 && gre_list.size() > 0)
        median[1] = (median[1] + gre_list[(gre_list.size() / 2) - 1]) / 2;
      
      median[2] = blu_list[blu_list.size() / 2];
      if (blu_list.size() % 2 == 0 && blu_list.size() > 0)
        median[2] = (median[2] + blu_list[(blu_list.size() / 2) - 1]) / 2;
      
      // Put new RGB values into image
      image[i][j].SetRGB(median[0], median[1], median[2]);
    }
  }
  
  return true;
}

bool DanProcessor::filterEmboss(Image& image, int** mask, int mask_w, int mask_h)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  // Initialize variables
  Image copy;                           // Copy of original image
  int img_w;                            // Overal image width
  int img_h;                            // Overal image height
  int sum;                              // Sum of intensities
  int center_x;                         // Center of mask
  int center_y;                         // Center of mask
  int i, j, k, l, x, y;                 // Temporary variables
  
  // Copy image due to nature of algorithm
  copy = image;
  
  // Get image dimensions
  img_w = image.Width();
  img_h = image.Height();
  
  // Find center of mask. If mask is even x even, take top-left of center 4
  center_x = mask_w / 2 - (1 - mask_w % 2);
  center_y = mask_h / 2 - (1 - mask_h % 2);
  
  // Begin applying mask to image
  for (i = 0; i < img_h; ++i)           // Loop over rows
  {
    for (j = 0; j < img_w; ++j)         // Loop over columns
    {
      // Reset variables
      sum = 0;
      
      // Center mask over pixel and take weighted average
      for (k = 0; k < mask_h; ++k)      // Loop over mask rows
      {
        for (l = 0; l < mask_w; ++l)    // Loop over mask columns
        {
          // Temporarily store variable of current pixel to sum
          x = j + (l - center_x);
          y = i + (k - center_y);
          
          // If a pixel would be out of bounds, use nearest valid pixel
          if (x < 0)      x = 0;
          if (x >= img_w) x = img_w - 1;
          if (y < 0)      y = 0;
          if (y >= img_h) y = img_h - 1;
          
          // Add RGB values to sum with weights
          sum += copy[y][x] * mask[k][l];
        }
      }
      
      // Add 127 and scale for embossing
      sum = 127 + (sum / 2);
           
      // Clip values should they be invalid
      if (sum < 0)     sum = 0;
      if (sum >= 256)  sum = 256-1; // Why not 255? to match lines 69-72
      
      // Put new RGB values into image
      image[i][j].SetGray(sum);
    }
  }
  
  return true;
}

int** DanProcessor::alloc2d(int w, int h)
{
  int** array;
  array = new int* [h];
  for (int i = 0; i < h; i++)
    array[i] = new int [w];
  return array;
}

void DanProcessor::dealloc2d(int** array, int w, int h)
{
  for (int i = 0; i < h; i++)
    delete [] array[i];
  delete [] array;
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

bool DanProcessor::Menu_EdgeDetection_3x3SharpeningFilter(Image& image)
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

bool DanProcessor::Menu_OS_PlusShapedMedianFilter(Image& image)
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

bool DanProcessor::Menu_EdgeDetection_Emboss(Image& image)
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

bool DanProcessor::Menu_EdgeDetection_LaplacianEdges(Image& image)
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

