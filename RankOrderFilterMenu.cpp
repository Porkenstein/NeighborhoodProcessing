
#include "RankOrderFilterMenu.h"

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
bool RankOrderFilterMenu::Menu_RankOrderFilters_MeanFilter(Image& image)
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
bool RankOrderFilterMenu::Menu_RankOrderFilters_MedianFilter(Image& image)
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
bool RankOrderFilterMenu::Menu_RankOrderFilters_MinimumFilter(Image& image)
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
bool RankOrderFilterMenu::Menu_RankOrderFilters_MaximumFilter(Image& image)
{
  return this->filterStatistic(image, Max);
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
bool RankOrderFilterMenu::Menu_RankOrderFilters_PlusShapedMedianFilter(Image& image)
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

