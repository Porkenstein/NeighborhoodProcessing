/***************************************************************************//**
 * PointProcessor.h
 *
 * Author - Derek Stotz
 *
 * Date - Feb 26, 2015
 *
 * Details - Contains the declaration for the PointProcessor class.
 *
 ******************************************************************************/

#pragma once
#include <qtimagelib.h>

/***************************************************************************//**
 * PointProcessor
 *
 * Author - Derek Stotz
 *
 * Child of QObject class.
 *
 *
 * A class containing implementations (done ahead of time) of various point
 * processes. Some of them were written by us for the previous assignment, and
 * some are simple impelementations of QtImageLib functions.
 ******************************************************************************/

class PointProcessor : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_PointProcesses_ConvertToGreyscale(Image& image);
    bool Menu_PointProcesses_ApplyBinaryThreshold(Image& image);
    bool Menu_PointProcesses_Equalize(Image& image);
    bool Menu_PointProcesses_EqualizeWithClipping(Image& image);
    bool Menu_PointProcesses_AutoContrastStretch(Image& image);
    bool Menu_PointProcesses_ModifiedContrastStretch(Image& image);
    bool Menu_PointProcesses_ViewImageHistogram(Image &image);
    bool Menu_NoiseTools_AddGaussianNoise(Image &image);
    bool Menu_NoiseTools_AddImpulseNoise(Image &image);
};

