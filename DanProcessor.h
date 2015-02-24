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

#define _USE_MATH_DEFINES
#include <qtimagelib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

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
    bool filterAverage(Image& image, int** mask, int mask_w, int mask_h, bool gray);
    bool filterMedian(Image& image, int** mask, int mask_w, int mask_h);
    bool filterEmboss(Image& image, int** mask, int mask_w, int mask_h);
    bool sobel(Image& image, bool mag);
    int** alloc2d(int w, int h);
    void  dealloc2d(int** array, int w, int h);
  
  public slots:
    bool Menu_Smoothing_3x3SmoothingFilter(Image& image);
    bool Menu_EdgeDetection_3x3SharpeningFilter(Image& image);
    bool Menu_OS_PlusShapedMedianFilter(Image& image);
    bool Menu_EdgeDetection_Emboss(Image& image);
    bool Menu_EdgeDetection_LaplacianEdges(Image& image);
    bool Menu_EdgeDetection_SobelEdgeMagnitudes(Image& image);
    bool Menu_EdgeDetection_SobelEdgeDirections(Image& image);
};

