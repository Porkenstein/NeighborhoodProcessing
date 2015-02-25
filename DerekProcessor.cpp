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


/***************************************************************************//**
 * Utility functions
 ******************************************************************************/

/***************************************************************************//**
 * alloc2d
 * Author - Dan Andrus
 *
 * Allocates a 2-dimensional array
 *
 * Parameters -
            w - the width of the 2d array
            h - the height of the 2d array
 *
 * Returns
 *          a pointer to a two-dimensional array
 ******************************************************************************/
int** DerekProcessor::alloc2d(int w, int h)
{
  int** array;
  array = new int* [h];
  for (int i = 0; i < h; i++)
    array[i] = new int [w];
  return array;
}

/***************************************************************************//**
 *dealloc2d
 * Author - Dan Andrus
 *
 * Deallocates a 2-dimensional array
 *
 * Parameters -
 *          array - the array to deallocate
            h - the height of the 2d array
 ******************************************************************************/
void DerekProcessor::dealloc2d(int** array, int h)
{
  for (int i = 0; i < h; i++)
    delete [] array[i];
  delete [] array;
}

/***************************************************************************//**
 *filterStatistic
 * Author - Dan Andrus & Derek Stotz
 *
 * For each pixel in an image, sorts the surrounding pixel neighborhood and applies
 * one of several different filters to the pixel using the ranked order of the pixel
 * values.  This makes use of the operation enum found in DerekProcessor.h.
 *
 * Parameters -
 *          image - the image to filter
 *          mask_w - the mask width (and height)
 *          op - the operation (Min, Max, Median, or Mean)
 ******************************************************************************/
bool DerekProcessor::filterStatistic(Image& image, operation op)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;

  // Initialize variables
  Image copy;                           // Copy of original image
  int img_w;                            // Overal image width
  int img_h;                            // Overal image height
  int mask_w;                           // The width of the filter
  int val[3];                           // New values of all colors
  int center;                           // Center of mask (x and y are the same in any case)
  uint i, j, k, l, x, y;                 // Temporary variables
  int min_thresh, max_thresh;           // Thresholds

  vector<int> red_list;                 // Intensity values for red
  vector<int> gre_list;                 // Intensity values for green
  vector<int> blu_list;                 // Intensity values for blu

  // Copy image due to nature of algorithm
  copy = image;

  // Ask the user for the dimensions of the filer
  if (!Dialog("Dialog").Add(mask_w, "Filter Width").Show() || mask_w < image.Width() || mask_w < image.Height() || mask_w < 2)
      return false;

  // If this filter wants a threshold, ask for it.
  if (op == NoiseClean && !Dialog("Linear Contrast").Add(min_thresh, "Minimum Threshold", -1, 255)
        .Add(max_thresh, "Maximum Threshold", 0, 256).Show())
    return false;

  // Get image dimensions
  img_w = image.Width();
  img_h = image.Height();

  // Find center of mask. If mask is even x even, take top-left of center 4
  center = mask_w / 2 - (1 - mask_w % 2);

  // Begin applying filter to image
  for (i = 0; i < img_h; ++i)           // Loop over rows
  {
    for (j = 0; j < img_w; ++j)         // Loop over columns
    {

      // first, check to see if the pixel value is inside of our threshold (for Noise Clean)
      if (op == NoiseClean && copy[i][j].Intensity() < max_thresh && copy[i][j].Intensity() > min_thresh)
      {
          // if it is, don't bother with the mask on this pixel
          continue;
      }

      // Reset variables
      red_list.clear();
      gre_list.clear();
      blu_list.clear();
      val[0] = 0;
      val[1] = 0;
      val[2] = 0;

      // Center mask over pixel and take weighted average
      for (k = 0; k < mask_w; ++k)      // Loop over mask rows
      {
        for (l = 0; l < mask_w; ++l)    // Loop over mask columns
        {
          // Temporarily store location of pixel in mask
          x = j + (l - center);
          y = i + (k - center);

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

      if (op != Mean)
      {
          // Sort lists if they aren't going to be averaged
          sort(red_list.begin(), red_list.end());
          sort(gre_list.begin(), gre_list.end());
          sort(blu_list.begin(), blu_list.end());
      }

      // Calculate the new value, depending on the operation

      switch(op)
      {
      case Min:
          // set the new RGB values to the min values
          val[0] = red_list[0];
          val[1] = gre_list[0];
          val[2] = blu_list[0];
          break;

      case Max:  // set the new RGB values to the max values
          val[0] = red_list[red_list.size()];
          val[1] = gre_list[gre_list.size()];
          val[2] = blu_list[blu_list.size()];
          break;

      case NoiseClean:
          // fall through and apply the median filter

      case Median:  // find the medians, or the average of the two medians
          val[0] = red_list[red_list.size() / 2];
          if (red_list.size() % 2 == 0 && red_list.size() > 0)
            val[0] = (val[0] + red_list[(red_list.size() / 2) - 1]) / 2;

          val[1] = gre_list[gre_list.size() / 2];
          if (gre_list.size() % 2 == 0 && gre_list.size() > 0)
            val[1] = (val[1] + gre_list[(gre_list.size() / 2) - 1]) / 2;

          val[2] = blu_list[blu_list.size() / 2];
          if (blu_list.size() % 2 == 0 && blu_list.size() > 0)
            val[2] = (val[2] + blu_list[(blu_list.size() / 2) - 1]) / 2;
          break;

      case Mean:
      {
          int sum[3] = {0}; // the sum of the three colors
          for( i = 0; i < red_list.size(); i++)
              sum[0] += red_list[i];
              sum[1] += gre_list[i];
              sum[2] += blu_list[i];

          val[0] = sum[0] / red_list.size();
          val[1] = sum[1] / gre_list.size();
          val[2] = sum[2] / blu_list.size();
          break;
      }

      default:  // if it's any other operation, it should probably be a grayscale one.

          return false;
      }

      // Put new RGB values into image
      image[i][j].SetRGB(val[0], val[1], val[2]);
    }
  }

  return true;
}


/***************************************************************************//**
 *filterStatisticGreyscale
 * Author - Dan Andrus & Derek Stotz
 *
 * For each pixel in an image, sorts the surrounding pixel neighborhood and applies
 * one of several different filters to the pixel using the ranked order of the pixel
 * values.  This makes use of the operation enum found in DerekProcessor.h.
 *
 * Parameters -
 *          image - the image to filter
 *          op - the operation (either standard deviation or range)
 ******************************************************************************/
bool DerekProcessor::filterStatisticGreyscale(Image& image, operation op)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;

  // Initialize variables
  Image copy;                           // Copy of original image
  int mask_w;                           // The width of the filter
  int img_w;                            // Overal image width
  int img_h;                            // Overal image height
  int val;                              // New values of all colors
  int center;                           // Center of mask (x and y are the same in any case)
  int i, j, k, l, x, y, temp, avg;      // Temporary variables

  vector<int> list;                 // Intensity values

  // Ask the user for the dimensions of the filer
  if (!Dialog("Dialog").Add(mask_w, "Filter Width").Show() || mask_w < image.Width() || mask_w < image.Height() || mask_w < 2)
      return false;

  // Copy image due to nature of algorithm
  copy = image;

  // Get image dimensions
  img_w = image.Width();
  img_h = image.Height();

  // Find center of mask. If mask is even x even, take top-left of center 4
  center = mask_w / 2 - (1 - mask_w % 2);

  // Begin applying filter to image
  for (i = 0; i < img_h; ++i)           // Loop over rows
  {
    for (j = 0; j < img_w; ++j)         // Loop over columns
    {
      // Reset variables
      list.clear();
      val = 0;

      // Center mask over pixel and take weighted average
      for (k = 0; k < mask_w; ++k)      // Loop over mask rows
      {
        for (l = 0; l < mask_w; ++l)    // Loop over mask columns
        {
          // Temporarily store location of pixel in mask
          x = j + (l - center);
          y = i + (k - center);

          // If a pixel would be out of bounds, use nearest valid pixel
          if (x < 0)      x = 0;
          if (x >= img_w) x = img_w - 1;
          if (y < 0)      y = 0;
          if (y >= img_h) y = img_h - 1;

          // Add RGB values to lists
          list.push_back(copy[y][x].Intensity());
        }
      }

      // Sort lists
      sort(list.begin(), list.end());

      // Calculate the new value, depending on the operation

      switch(op)
      {
      case StandardDeviation: // set the intensity to the stdev of surrounding pixels

          // start by finding the mean
          avg = 0;
          for( i = 0; i < list.size(); i++)
              avg += list[i];
          avg = avg / list.size();

          // then find each square deviation and add them together
          temp = 0;
          for ( i = 0; i < list.size(); i++)
               temp += pow(list[i] - avg, 2);

          // use the sum of the squared deviations to find the stdev
          temp /= list.size()-1; // we know that list.size() is > 1
          val = min((int)sqrt((double)temp), 255);
          break;

      case Range:  // set the intensity to the range of surrounding pixel values
          val = list[list.size()] - list[0];
          break;

      default:  // if it's any other operation, it should probably be a non-grayscale one.
          return false;
      }

      // Put new RGB values into image
      image[i][j].SetIntensity(val);
    }
  }

  return true;
}




/***************************************************************************//**
 * Neighborhood Processes
 ******************************************************************************/

/***************************************************************************//**
 * Menu_EdgeDetection_KirschEdgeDetection
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
bool DerekProcessor::Menu_EdgeDetection_KirschEdgeDetection(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
  return true;
}

/***************************************************************************//**
 * Menu_EdgeDetection_KirschEdgeDetection
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
bool DerekProcessor::Menu_EdgeDetection_KirschEdgeMagnitude(Image& image)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;
  
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
bool DerekProcessor::Menu_EdgeDetection_StandardDeviationEdgeDetection(Image& image)
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
bool DerekProcessor::Menu_NoiseTools_NoiseCleanFilter(Image& image)
{
  return this->filterStatistic(image, NoiseClean);
}

/***************************************************************************//**
 * Menu_RankOrderFilers_MeanFilter
 * Author - Derek Stotz
 *
 * Applies a mean filter to an image, replacing all pixels with the mean pixel value
 * in the neighborood.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DerekProcessor::Menu_RankOrderFilters_MeanFilter(Image& image)
{
  return this->filterStatistic(image, Mean);
}

/***************************************************************************//**
 * Menu_RankOrderFilers_MedianFilter
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
bool DerekProcessor::Menu_RankOrderFilters_MedianFilter(Image& image)
{
  return this->filterStatistic(image, Median);
}


/***************************************************************************//**
 * Menu_RankOrderFilers_MinimumFilter
 * Author - Derek Stotz
 *
 * Applies a minimum filter to an image, replacing all pixels with the min pixel value
 * in the neighborood.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DerekProcessor::Menu_RankOrderFilters_MinimumFilter(Image& image)
{
  return this->filterStatistic(image, Min);
}

/***************************************************************************//**
 * Menu_RankOrderFilers_MaximumFilter
 * Author - Derek Stotz
 *
 * Applies a max filter to an image, replacing all pixels with the max pixel value
 * in the neighborood.
 *
 * Parameters -
            image - the image object to manipulate.
 *
 * Returns
 *          true if successful, false if not
 ******************************************************************************/
bool DerekProcessor::Menu_RankOrderFilters_MaximumFilter(Image& image)
{
  return this->filterStatistic(image, Max);
}
