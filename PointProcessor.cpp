/***************************************************************************//**
 * PointProcessor.cpp
 *
 * Author - Derek Stotz, QtImageLib by Dr. John Weiss
 *
 * Date - Feb 26, 2015
 *
 * Implementations (done ahead of time) of various point processes. Some of them
 * were written by us for the previous assignment, and some are simple
 * impelementations of QtImageLib functions.
 ******************************************************************************/

#include "PointProcessor.h"

/***************************************************************************//**
 * Menu_PointProcesses_ModifiedContrastStretch
 * Author - Derek Stotz
 *
 * Uses the QtImageLib to convert the image to a grayscale image.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool PointProcessor::Menu_PointProcesses_ConvertToGreyscale(Image& image)
{
    return grayscale(image);
}

/***************************************************************************//**
 * Menu_PointProcesses_ModifiedContrastStretch
 * Author - Derek Stotz
 *
 * Uses the QtImageLib to apply a binary threshold filter to the image.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool PointProcessor::Menu_PointProcesses_ApplyBinaryThreshold(Image& image)
{
    int threshold = 0;
    getParams(threshold);
    return binaryThreshold(image, threshold);
}

/***************************************************************************//**
 * Menu_PointProcesses_HistogramEqualization
 * Author - Dan Andrus
 *
 * Applies a histogram equalization to an image.
 * 
 *
 * Parameters - 
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool PointProcessor::Menu_PointProcesses_Equalize(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  int total = rows * cols;
  int tally = 0;
  int tmp;
  
  unsigned char lutable[256];
  int histogram[256] = {0};
  
  // Build histogram
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      histogram[image[i][j].Intensity()]++;
    }
  }
  
  
  // Build lookup table based on histogram
  for (int i = 0; i < 256; i++)
  {
    tally += histogram[i];
    tmp = (int) (tally / (total / 256.0));
    if (tmp < 0) tmp = 0;
    if (tmp > 255) tmp = 255;
    lutable[i] = tmp;
  }
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Pseudocolor each pixel based on intensity
      image[i][j].SetIntensity(lutable[image[i][j].Intensity()]);
    }
  }
  
  return true;
}



/***************************************************************************//**
 * Menu_PointProcesses_HistogramEqualizationWithClipping
 * Author - Dan Andrus
 *
 * Applies a histogram equalization with optional clipping to an image.
 * 
 *
 * Parameters - 
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool PointProcessor::Menu_PointProcesses_EqualizeWithClipping
  (Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  int total = rows * cols;
  int tally = 0;
  int tmp;
  double max;
  
  unsigned char lutable[256];
  int histogram[256] = {0};
  
  // Propt user for threshold value
  max = 0;
  if (!Dialog("Ignore Percentage").Add(max, "Percentage", 0, 100).Show())
    return false;
  
  // Make sure max is greater than 0, otherwise we get a division by 0
  if (max == 0)
    return false;
  
  // Build histogram
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      histogram[image[i][j].Intensity()]++;
    }
  }
  
  // Format max for histogram
  max = (int) (total * (max / 100));
  
  // Clip histogram and recalculate total
  total = 0;
  for (int i = 0; i < 256; i++)
  {
    if (histogram[i] > max)
      histogram[i] = max;
    total += histogram[i];
  }
  
  // Build lookup table based on histogram
  for (int i = 0; i < 256; i++)
  {
    tally += histogram[i];
    tmp = (int) (tally / (total / 256.0));
    if (tmp < 0) tmp = 0;
    if (tmp > 255) tmp = 255;
    lutable[i] = (unsigned char) tmp;
  }
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Pseudocolor each pixel based on intensity
      image[i][j].SetIntensity(lutable[image[i][j].Intensity()]);
    }
  }
  
  return true;
}

/***************************************************************************//**
 * Menu_PointProcesses_AutoContrastStretch
 * Author - Derek Stotz
 *
 * Automatically stretches the contrast so max intensity is 255 and min is 0.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool PointProcessor::Menu_PointProcesses_AutoContrastStretch(Image& image)
{
    int rows = image.Height();
    int cols = image.Width();

    uchar min_i = 255;
    uchar max_i = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            min_i = std::min(min_i, image[i][j].Intensity());
            max_i = std::max(max_i, image[i][j].Intensity());
        }
    }

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
          image[i][j].SetRed((255/(max_i - min_i)) * (image[i][j].Red() - min_i));
          image[i][j].SetGreen((255/(max_i - min_i)) * (image[i][j].Green() - min_i));
          image[i][j].SetBlue((255/(max_i - min_i)) * (image[i][j].Blue() - min_i));
      }
    }

    return true;
}

/***************************************************************************//**
 * Menu_PointProcesses_ModifiedContrastStretch
 * Author - Derek Stotz
 *
 * Stretches the intensity values, clipping the top and bottom n percent of
 * intensity values
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool PointProcessor::Menu_PointProcesses_ModifiedContrastStretch(Image& image)
{
    int rows = image.Height();
    int cols = image.Width();
    int n_pixels = rows*cols;
    int min_p = 0;
    int max_p = 0;
    std::vector<uint>histogram = std::vector<uint>(256);

    // Propt user for threshold value
    if (!Dialog("Gamma Correction").Add(min_p, "Minimum Percentage", 0, 100).Add(max_p, "Maximum Percentage", 0, 100).Show())
      return false;

    uchar min_i = 255;
    uchar max_i = 0;

    // create list of intensity values
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
          histogram[image[i][j].Intensity()]++;
      }
    }

    min_p = (min_p /100.0) * n_pixels;
    max_p = (max_p /100.0) * n_pixels;

    // find the min_i by subtracting pixel counts from the pixels to ignore
    bool done = false;
    for (int i = 0; !done && i < 256; i++)
    {
        min_p -= histogram[i];
        if (min_p <= 0)\
        {
            min_i = i;
            done = true;
        }
    }

    // find the max_i by subtracting pixel counts from the pixels to ignore
    done = false;
    for (int i = 255; !done && i > 0; i--)
    {
        max_p -= histogram[i];
        if (max_p <= 0)\
        {
            max_i = i;
            done = true;
        }
    }

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
          image[i][j].SetRed((255/(max_i - min_i)) * (image[i][j].Red() - min_i));
          image[i][j].SetGreen((255/(max_i - min_i)) * (image[i][j].Green() - min_i));
          image[i][j].SetBlue((255/(max_i - min_i)) * (image[i][j].Blue() - min_i));
      }
    }

    return true;
}

/***************************************************************************//**
 * Menu_PointProcesses_ModifiedContrastStretch
 * Author - Derek Stotz
 *
 * Displays an image histogram generated by QtImageLib subroutines
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool PointProcessor::Menu_PointProcesses_ViewImageHistogram(Image &image)
{
    displayHistogram(image.Histogram(), "Image Histogram");
    return true;
}

