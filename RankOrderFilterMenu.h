/***************************************************************************//**
 * RankOrderFilterMenu.h
 *
 * Author - Derek Stotz
 *
 * Date - February 26, 2015
 *
 * Details - Contains the declaration for the RankOrderFilterMenu class
 *
 ******************************************************************************/

#include "toolbox.h"

/***************************************************************************//**
 * RankOrderFilterMenu
 *
 * Author - Derek Stotz
 *
 * Child of QObject class.
 *
 * Declares various neighborhood proccess for Rank Order filters with specifiable
 * filter sizes.  Pixels filtered through these will be set to whatever statistically
 * signifcant value in the neighborhood specified.
 ******************************************************************************/
class RankOrderFilterMenu : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_RankOrderFilters_MeanFilter(Image& image);
    bool Menu_RankOrderFilters_MedianFilter(Image& image);
    bool Menu_RankOrderFilters_MinimumFilter(Image& image);
    bool Menu_RankOrderFilters_MaximumFilter(Image& image);
    bool Menu_RankOrderFilters_PlusShapedMedianFilter(Image& image);
};
