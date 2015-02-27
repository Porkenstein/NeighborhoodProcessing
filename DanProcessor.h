/***************************************************************************//**
 * DanProcessor.h
 *
 * Author - Dan Andrus
 *
 * Date - February 25, 2015
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
 * DanProcessor
 *
 * Author - DanAndrus
 *
 * Child of QObject class.
 *
 * Declares various neighborhood processes that can be applied to images using
 * QT.
 ******************************************************************************/
class DanProcessor : public QObject
{
  Q_OBJECT;
  
  private:
    bool filterAverage(Image& image, int** mask, int mask_w, int mask_h, bool gray);
    bool filterMedian(Image& image, int** mask, int mask_w, int mask_h);
    bool filterEmboss(Image& image, int** mask, int mask_w, int mask_h);
    bool sobel(Image& image, bool mag);
    bool kirschDir(Image& image);
    int** alloc2d(int w, int h);
    void  dealloc2d(int** array, int w, int h);
  
  public slots:
    bool Menu_Smoothing_3x3SmoothingFilter(Image& image);
    bool Menu_EdgeDetection_3x3SharpeningFilter(Image& image);
    bool Menu_RankOrderFilters_PlusShapedMedianFilter(Image& image);
    bool Menu_EdgeDetection_Emboss(Image& image);
    bool Menu_EdgeDetection_LaplacianEdges(Image& image);
    bool Menu_EdgeDetection_SobelEdgeMagnitudes(Image& image);
    bool Menu_EdgeDetection_SobelEdgeDirections(Image& image);
    bool Menu_EdgeDetection_KirschEdgeDirections(Image& image);
};

