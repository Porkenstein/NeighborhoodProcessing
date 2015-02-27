#include "toolbox.h"

/***************************************************************************//**
 * filterAverage
 * Author - Dan Andrus
 *
 * Applies an averaging filter to an image using the supplied mask.
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *          mask - the 2d integer mask to apply to the image
 *          mask_w - columns in the mask
 *          mask_h - rows in the mask
 *
 * Returns
 *          True if the operation was successful, false if not
 ******************************************************************************/
bool filterAverage(Image& image, int** mask, int mask_w, int mask_h, bool gray)
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

/***************************************************************************//**
 * filterMedian
 * Author - Dan Andrus
 *
 * Applies a median filter to an image using the supplied mask.
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *          mask - the 2d integer mask to apply to the image
 *          mask_w - columns in the mask
 *          mask_h - rows in the mask
 *
 * Returns
 *          True if the operation was successful, false if not
 ******************************************************************************/
bool filterMedian(Image& image, int** mask, int mask_w, int mask_h)
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

/***************************************************************************//**
 * filterEmboss
 * Author - Dan Andrus
 *
 * Embosses the given image object.
 *
 * Parameters - 
 *          image - the image object to manipulate.
 *          mask - the 2d integer mask to apply to the image
 *          mask_w - columns in the mask
 *          mask_h - rows in the mask
 *
 * Returns
 *          True if the operation was successful, false if not
 ******************************************************************************/
bool filterEmboss(Image& image, int** mask, int mask_w, int mask_h)
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
          
          // Add intensity values to sum with weights
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

/***************************************************************************//**
 * alloc2d
 * Author - Dan Andrus
 *
 * Allocates a new 2d row-major integer array
 *
 * Parameters - 
 *          w - number of columns in the array
 *          h - number of rows in the array
 *
 * Returns
 *          Pointer to the 2d integer array
 ******************************************************************************/
int** alloc2d(int w, int h)
{
  int** array;
  array = new int* [h];
  for (int i = 0; i < h; i++)
    array[i] = new int [w];
  return array;
}

/***************************************************************************//**
 * dealloc2d
 * Author - Dan Andrus
 *
 * Deallocate a 2-dimensional row-major integer array
 *
 * Parameters - 
 *          array - Pointer to the array of int pointers to deallocate
 *          w - number of columns in the array
 *          h - number of rows in the array
 ******************************************************************************/
void dealloc2d(int** array, int h)
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
bool filterStatistic(Image& image, operation op)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;

  // Initialize variables
  Image copy;                           // Copy of original image
  int img_w;                            // Overal image width
  int img_h;                            // Overal image height
  int mask_w = 3;                       // The width of the filter
  int val[3];                           // New values of all colors
  int center;                           // Center of mask (x and y are the same in any case)
  int i, j, k, l, x, y, m;             // Temporary variables
  int threshold = 0;                        // Threshold for noise removal
  int sum[3] = {0};

  vector<int> red_list;                 // Intensity values for red
  vector<int> gre_list;                 // Intensity values for green
  vector<int> blu_list;                 // Intensity values for blu

  // Copy image due to nature of algorithm
  copy = image;

  // Ask the user for the dimensions of the filer
  if (!Dialog("Dialog").Add(mask_w, "Filter Width").Show() || mask_w < 2)
      return false;

  // If this filter wants a threshold, ask for it.
  if (op == NoiseClean && !Dialog("Noise Removal").Add(threshold, "Threshold", 0, 255).Show())
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

      if (op != Mean && op != NoiseClean)
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
          val[0] = red_list[red_list.size()-1];
          val[1] = gre_list[gre_list.size()-1];
          val[2] = blu_list[blu_list.size()-1];
          break;

      case NoiseClean:
          sum[0] = 0;
          sum[1] = 0;
          sum[2] = 0; // the sum of the three colors

          for( m = 0; m < (int)red_list.size(); m++)
          {
              sum[0] += red_list[m];
              sum[1] += gre_list[m];
              sum[2] += blu_list[m];
          }

          sum[0] /= red_list.size();
          sum[1] /= gre_list.size();
          sum[2] /= blu_list.size();

          // replace the pixel with the average if the value - the averages
          //    exceed the user-specified threshold.

          if (abs(sum[0] - copy[i][j].Red()) > threshold)
            val[0] = sum[0];
          else
            val[0] = copy[i][j].Red();

          if (abs(sum[1] - copy[i][j].Green()) > threshold)
            val[1] = sum[1];
          else
            val[1] = copy[i][j].Green();

          if (abs(sum[2] - copy[i][j].Blue()) > threshold)
            val[2] = sum[2];
          else
            val[2] = copy[i][j].Blue();

          break;

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
          sum[0] = 0;
          sum[1] = 0;
          sum[2] = 0; // the sum of the three colors

          for( m = 0; m < (int)red_list.size(); m++)
          {
              sum[0] += red_list[m];
              sum[1] += gre_list[m];
              sum[2] += blu_list[m];
          }

          val[0] = sum[0] / red_list.size();
          val[1] = sum[1] / gre_list.size();
          val[2] = sum[2] / blu_list.size();
          break;

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
bool filterStatisticGreyscale(Image& image, operation op)
{
  // Make sure image isn't null
  if (image.IsNull()) return false;

  // Initialize variables
  Image copy;                           // Copy of original image
  int mask_w = 3;                       // The width of the filter
  int img_w;                            // Overal image width
  int img_h;                            // Overal image height
  int val;                              // New values of all colors
  int center;                           // Center of mask (x and y are the same in any case)
  int i, j, k, l, x, y, m, temp, avg;   // Temporary variables

  vector<int> list;                     // Intensity values

  // Ask the user for the dimensions of the filer
  if (!Dialog("Dialog").Add(mask_w, "Filter Width").Show() || mask_w == 1)
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
          for( m = 0; m < (int)list.size(); m++)
              avg += list[m];
          avg = avg / list.size();

          // then find each square deviation and add them together
          temp = 0;
          for ( m = 0; m < (int)list.size(); m++)
               temp += pow(list[m] - avg, 2);

          // use the sum of the squared deviations to find the stdev
          temp /= list.size()-1; // we know that list.size() is > 1
          val = min((int)sqrt((double)temp), 255);
          break;

      case Range:  // set the intensity to the range of surrounding pixel values
          val = list[list.size()-1] - list[0];
          break;

      default:  // if it's any other operation, it should probably be a non-grayscale one.
          return false;
      }

      // Put new RGB values into image
      image[i][j].SetGray(val);
    }
  }

  return true;
}
