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
    bool Menu_RankOrderFilters_PlusShapedMedianFilter(Image& image);
};

