/***************************************************************************//**
 * DerekProcessor.h
 *
 * Author - Derek Stotz
 *
 * Date - January 30, 2015
 *
 * Details - Contains the declaration for the DerekProcessor class.
 *
 ******************************************************************************/

#pragma once
#include <qtimagelib.h>

/***************************************************************************//**
 * DerekPreprocessor
 *
 * Author - Derek Stotz
 *
 * Child of QObject class.
 *
 * Declares various point processes that can be applied to images using QT.
 * Allows users to apply Gamma and Log transforms, view image histograms,
 * apply continuous pseudocolors, subtract other images from the selected image,
 * and apply contrast stretches.
 ******************************************************************************/
class DerekProcessor : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_DerekFunctions_ApplyGamma(Image& image);
};
