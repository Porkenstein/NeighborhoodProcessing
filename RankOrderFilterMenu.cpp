
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

