#pragma once

#define _USE_MATH_DEFINES
#include <qtimagelib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool filterAverage(Image& image, int** mask, int mask_w, int mask_h, bool gray = false);
bool filterMedian(Image& image, int** mask, int mask_w, int mask_h);
bool filterEmboss(Image& image, int** mask, int mask_w, int mask_h);
bool sobel(Image& image, bool mag);
bool kirschDir(Image& image);
int** alloc2d(int w, int h);
void  dealloc2d(int** array, int w, int h);
