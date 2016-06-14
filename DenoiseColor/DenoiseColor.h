#ifndef _DENOISE_COLOR_H_
#define _DENOISE_COLOR_H_

#include <opencv2/opencv.hpp>

using namespace cv;

int guidedFilterRCaculate(int avgLum);
void denoiseColor(Mat& input, Mat& output, float eps = 0.2);

#endif //_DENOISE_COLOR_H_

