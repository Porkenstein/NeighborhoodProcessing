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

#define _USE_MATH_DEFINES
#include <qtimagelib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

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
    bool Menu_NoiseTools_NoiseCleanFilter(Image& image);
    bool Menu_RankOrderFilters_MeanFilter(Image& image);
    bool Menu_RankOrderFilters_MedianFilter(Image& image);
    bool Menu_EdgeDetection_KirschEdgeMagnitude(Image& image);
    bool Menu_RankOrderFilters_MinimumFilter(Image& image);
    bool Menu_EdgeDetection_StandardDeviationEdgeDetection(Image& image);
    bool Menu_RankOrderFilters_MaximumFilter(Image& image);
    bool Menu_EdgeDetection_RangeFilter(Image& image);

 public:
    enum  operation {Min, Max, Mean, Median, Range, StandardDeviation, NoiseClean};

private:
  int** alloc2d(int w, int h);
  void dealloc2d(int** array, int h);
  bool filterStatistic(Image& image, operation operation);
  bool filterStatisticGreyscale(Image& image, operation operation);
};

