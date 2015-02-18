/***************************************************************************//**
 * ImageLibProcessor.h
 *
 * Author - Derek Stotz
 *
 * Date - January 30, 2015
 *
 * Details - Contains the declaration for the ImageLibProcessor class.
 *
 ******************************************************************************/

#pragma once
#include <qtimagelib.h>

/***************************************************************************//**
 * ImageLibProcessor
 *
 * Author - Derek Stotz
 *
 * Child of QObject class.
 *
 * Declares wrappers for various point processes implemented in the QtImageLib.
 ******************************************************************************/
class ImageLibProcessor : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_ImageLibFunctions_ConvertToGreyscale(Image& image);
    bool Menu_ImageLibFunctions_NegateImage(Image& image);
    bool Menu_ImageLibFunctions_ApplyBinaryThreshold(Image& image);
    bool Menu_ImageLibFunctions_PosterizeImage(Image& image);
    bool Menu_ImageLibFunctions_ApplyGamma(Image& image);
    bool Menu_ImageLibFunctions_ApplyLogTransform(Image& image);
    bool Menu_ImageLibFunctions_Apply8LevelPseudocolor(Image& image);
    bool Menu_ImageLibFunctions_ApplyContinuousPseudocolor(Image& image);
    bool Menu_ImageLibFunctions_Equalize(Image& image);
    bool Menu_ImageLibFunctions_EqualizeWithClipping(Image& image);
    bool Menu_ImageLibFunctions_ViewImageHistogram(Image& image);
};

