/***************************************************************************//**
 * DerekProcessor.h
 *
 * Author - Derek Stotz
 *
 * Date - February 26, 2015
 *
 * Details - Contains the declaration for the NoiseToolMenu class
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
class DerekProcessor : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_NoiseTools_NoiseCleanFilter(Image& image);
    bool Menu_NoiseTools_AddGaussianNoise(Image &image);
    bool Menu_NoiseTools_AddImpulseNoise(Image &image);
};
