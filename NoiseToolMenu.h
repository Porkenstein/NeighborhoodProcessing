/***************************************************************************//**
 * NoiseToolMenu.h
 *
 * Author - Derek Stotz
 *
 * Date - February 26, 2015
 *
 * Details - Contains the declaration for the NoiseToolMenu class
 *
 ******************************************************************************/

#include "toolbox.h"

/***************************************************************************//**
 * NoiseToolMenu
 *
 * Author - Derek Stotz
 *
 * Child of QObject class.
 *
 * Declares various neighborhood and noise generation processes which are used in
 * prog2.  The noise generation is done with built-in imagelib functions, and the
 * noise removal is done through a rank order filter.
 ******************************************************************************/
class NoiseToolMenu : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_NoiseTools_NoiseCleanFilter(Image& image);
    bool Menu_NoiseTools_AddGaussianNoise(Image &image);
    bool Menu_NoiseTools_AddImpulseNoise(Image &image);
};
