/***************************************************************************//**
 * EdgeDetectionMenu.h
 *
 * Author - Dan Andrus
 *
 * Date - February 26, 2015
 *
 * Details - Contains the declaration for the EdgeDetectionMenu class.
 *
 ******************************************************************************/

#pragma once

#include "toolbox.h"

/***************************************************************************//**
 * EdgeDetectionMenu
 *
 * Author - DanAndrus
 *
 * Child of QObject class.
 *
 * Declares various edge detection neighborhood processes that can be applied to
 * images using QT.
 ******************************************************************************/
class EdgeDetectionMenu : public QObject
{
  Q_OBJECT;
  
  public slots:
    bool Menu_EdgeDetection_3x3SharpeningFilter(Image& image);
    bool Menu_EdgeDetection_Emboss(Image& image);
    bool Menu_EdgeDetection_Laplacian(Image& image);
    bool Menu_EdgeDetection_SobelMagnitude(Image& image);
    bool Menu_EdgeDetection_SobelDirection(Image& image);
    bool Menu_EdgeDetection_KirschDirection(Image& image);
};

