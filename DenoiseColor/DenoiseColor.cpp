#include <vector>
#include <iostream>
#include "filter/opencv2/ximgproc.hpp"
#include "DenoiseColor.h"
using namespace std;


int guidedFilterRCaculate(int avgLum) 
{
	int filterR = 0;
	if (avgLum > 140) 
	{
		filterR = 1;
	}
	else if (avgLum > 120) 
	{
		filterR = 1 + 5 * (140 - avgLum) / 20;
	}
	else if (avgLum > 60) 
	{
		filterR = 5 + 5 * (120 - avgLum) / 60;
	}
	else if (avgLum > 40) 
	{
		filterR = 10 + 25 * (60 - avgLum) / 20;
	}
	else if (avgLum > 20) 
	{
		filterR = 25 + 10 * (40 - avgLum) / 20;
	}
	else if (avgLum >= 0) 
	{
		filterR = 35 + 15 * (20 - avgLum) / 20;
	}

	return filterR;
}


void denoiseColor(Mat& input, Mat& output, float eps/*=0.2*/)
{
	//原图缩小25倍
	Mat smallImg;
	resize(input, smallImg, Size(), 0.2, 0.2, INTER_NEAREST);

	cout << "原尺寸 width: " << input.cols << "   height: " << input.rows << endl;
	cout << "小尺寸 width: " << smallImg.cols << "   height: " << smallImg.rows << endl;

	//求平均亮度
	Scalar avg;
	avg = mean(smallImg);
	int avgLum = (2990 * avg.val[2] + 5870 * avg.val[1] + 1140 * avg.val[0]) / 10000;
	cout << "平均亮度: " << avgLum << endl;

	//计算滤波器半径
	int radius;
	radius = guidedFilterRCaculate(avgLum);
	cout << "radius: " << radius << endl;

	//模糊
	Mat tempOut = Mat(input.rows, input.cols, CV_32FC3);
	input.convertTo(input, CV_32FC3, 1.0 / 255);
	ximgproc::guidedFilter(input, input, tempOut, radius, eps);
	tempOut.convertTo(tempOut, CV_8UC3, 255);

	//放大到原尺寸
	resize(tempOut, output, Size(input.cols, input.rows), 0,0, INTER_NEAREST);
}

