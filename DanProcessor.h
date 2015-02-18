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
  
  public slots:
    bool Menu_DanFunctions_Negate(Image& image);
};

