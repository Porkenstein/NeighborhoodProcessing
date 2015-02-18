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
   bool Menu_DerekFunctions_MinMaxStandardDeviationEdgeDetection(Image& image);
   bool Menu_DerekFunctions_NoiseCleanFilter(Image& image);
   bool Menu_DerekFunctions_MeanFilter(Image& image);
   bool Menu_DerekFunctions_KirschEdgeDetection(Image& image);
   bool Menu_DerekFunctions_MedianFilter(Image& image);
   bool Menu_DerekFunctions_KirschEdgeMagnitude(Image& image);
   bool Menu_DerekFunctions_MinimumFilter(Image& image);
   bool Menu_DerekFunctions_StandardDeviationEdgeDetection(Image& image);
   bool Menu_DerekFunctions_MaximumFilter(Image& image);
   bool Menu_DerekFunctions_RangeFilter(Image& image);
};
