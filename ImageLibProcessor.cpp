/***************************************************************************//**
 * ImageLibProcessor.cpp
 *
 * Author - Derek Stotz, QtImageLib by Dr. John Weiss
 *
 * Date - January 30, 2015
 *
 * Implementations of the QtImageLib functions.  These are entirely "bare-bones",
 * and not error checked or descriptive, as they are intended only for testing.
 * Function descriptions can be found in the QtImageLib documentation.
 ******************************************************************************/

#include "ImageLibProcessor.h"

bool ImageLibProcessor::Menu_ImageLibFunctions_ConvertToGreyscale(Image& image)
{
    return grayscale(image);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_NegateImage(Image& image)
{
    return negatePalette(image);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_ApplyBinaryThreshold(Image& image)
{
    int threshold = 0;
    getParams(threshold);
    return binaryThreshold(image, threshold);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_PosterizeImage(Image& image)
{
    int arg = 0;
    getParams(arg);
    return posterizePalette(image, arg);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_ApplyGamma(Image& image)
{
    double arg = 0;
    getParams(arg);
    return gammaPalette(image, (float)arg);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_ApplyLogTransform(Image& image)
{
    return logPalette(image);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_Apply8LevelPseudocolor(Image& image)
{
    return pseudocolor8Palette(image);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_ApplyContinuousPseudocolor(Image& image)
{
    return pseudocolorGWPalette(image);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_Equalize(Image& image)
{
    return histogramEqualize(image);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_EqualizeWithClipping(Image& image)
{
    double arg = 0;
    getParams(arg);
    return histogramEqualizeClip(image, (float)arg);
}

bool ImageLibProcessor::Menu_ImageLibFunctions_ViewImageHistogram(Image &image)
{
    displayHistogram(image.Histogram(), "Image Histogram");
    return true;
}

