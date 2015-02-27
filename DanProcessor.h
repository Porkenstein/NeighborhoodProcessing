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

#include "toolbox.h"

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

