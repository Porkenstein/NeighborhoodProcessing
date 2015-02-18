/***************************************************************************//**
 * DanProcessor.h
 *
 * Author - Dan Andrus
 *
 * Date - January 30, 2015
 *
 * Details - Contains the declaration for the DanProcessor class.
 *
 ******************************************************************************/

#pragma once
#include <qtimagelib.h>
#include <iostream>

/***************************************************************************//**
 * DanPreprocessor
 *
 * Author - DanAndrus
 *
 * Child of QObject class.
 *
 * Declares various point processes that can be applied to images using QT.
 * Allows users to negate, posterize, and brighten images, as well as apply
 * binary threshold, linear contrast, and 8-level pseudocolor processes.
 ******************************************************************************/
class DanProcessor : public QObject
{
  Q_OBJECT;
  
  private:
    bool filter(Image& image, int** mask, int mask_w, int mask_h);
  
  public slots:
    bool Menu_Filters_3x3SmoothingFilter(Image& image);
};

