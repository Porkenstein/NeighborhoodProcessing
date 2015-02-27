/***************************************************************************//**
 * SmoothingMenu.h
 *
 * Author - Derek Stotz
 *
 * Date - February 26, 2015
 *
 * Details - Contains the declaration for the SmoothingMenu class
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
 * Declares one smoothing function, could be extended to include Gaussian smoothing
 * for extra credit.
 ******************************************************************************/
class RankOrderFilterMenu : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_Smoothing_3x3SmoothingFilter(Image& image);

};
