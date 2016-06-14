#include <vector>
#include <iostream>
#include <direct.h>
#include "FileFind.h"
#include "DenoiseColor.h"

using namespace std;

const int BUFLEN = 200;

void help()
{
	cout << "---Usage:DenoiseColor.exe n(n>0 for n th dir, n==0 for all)proceess n th dir in resource )  eps" << endl;
}

bool process(string sdir_path, string sdir_name, int num, float eps = 0.2)
{
	cout << "----------Enter " << num << "sud dir----------" << endl;
	int len = 0;
	vector<string> img_dir_path(0), img_dir_name(0);
	FindSubDir((sdir_path).c_str(), img_dir_path, img_dir_name, len);

	Mat rgb;
	Mat rgb_denoise;

	string rgb_name;

	char *rgb_dir = (char*)malloc(512 * sizeof(char));
	char *rgb_denoise_dir = (char*)malloc(512 * sizeof(char));
	memset(rgb_dir, '\0', 512 * sizeof(char));
	memset(rgb_denoise_dir, '\0', 512 * sizeof(char));

	string s = "output";
	_mkdir(s.c_str());

	const char* bsp_t = sdir_name.c_str();
	s += "\\";
	s += sdir_name;
	const char* bsp_timestamp = s.c_str();
	_mkdir(bsp_timestamp);

	stringstream ss;
	string str;
	string s1;

	if (len == 0)
	{
		cout << "cannot find pic" << endl;
		return 0;
	}
	cout << "There are " << len << "  images in this dir" << endl;
	for (int i = 0; i < len; i++)
	{
		sprintf_s(rgb_denoise_dir, BUFLEN, "output/%s/%s", bsp_t, img_dir_name[i].c_str());
		_mkdir(rgb_denoise_dir);

		cout << "----------start process image----------" << i+1 << endl;
		rgb_name.clear();
		rgb_name = img_dir_path[i];
		rgb_name += "/rcv_rgb_cop.jpg";
		cout << "----------"<<rgb_name<<"----------" << endl;
		rgb = imread(rgb_name.c_str());
		if (rgb.empty())
		{
			cout << "Failed to Load rgb img %d" << i << endl;
			continue;
			cout << "Press Enter finish program" << endl;
			getchar();
			return -1;
		}

		denoiseColor(rgb, rgb_denoise, eps);

		cout << "----------finish process image----------" << i+1 << endl << endl;


		ss.str("");
		ss << (i + 1);
		str.clear();
		str = ss.str();

		s1.clear(); 
		s1 = rgb_denoise_dir; 
		s1 += "/rcv_rgb_denoise.jpg";

		imwrite(s1, rgb_denoise);
	}
	cout << "----------Finish " << num << " sub dir----------" << endl << endl;
}


int main(int argc, char* argv[])
{
	//help();
	//if (argc < 2)
	//{
	//	cout << "Usage:DenoiseColor.exe 1" << endl;
	//	cout << "Press Enter to finish the program" << endl;
	//	getchar();
	//	return -1;
	//}
	//int nSub = 0;
	//vector<string> sub_dir_path(0), sub_dir_name(0);
	//FindSubDir("resource", sub_dir_path, sub_dir_name, nSub);

	//if (nSub == 0)
	//{
	//	cout << "Make sure you have correct directory" << endl;
	//	cout << "no sub dir in resource" << endl;
	//	cout << "Press Enter to finish the program" << endl;
	//	getchar();
	//	return -1;
	//}

	//int dirNum = atoi(argv[1]);
	////int dirNum = 3;

	//int start = 0;
	//int end = nSub;
	//if (dirNum == 0 && nSub > 0)
	//{
	//	cout << "Process all bsp_timestamp" << endl;

	//}
	//else if (dirNum > 0 && dirNum <= nSub)
	//{
	//	cout << "Process one bsp_timestamp" << endl;
	//	start = dirNum-1;
	//	end = dirNum ;
	//}
	//else if (dirNum<0 || dirNum>nSub)
	//{
	//	cout << "Make sure you enter correct number" << endl;
	//	cout << "Press Enter to finish the program" << endl;
	//	getchar();
	//	getchar();
	//	return -1;
	//}

	//float eps = 0;
	//if (argc > 2)
	//{
	//	eps = atof(argv[2]);
	//}
	//else
	//{
	//	eps = 0.2;
	//}

	//cout << "----------Start batch test----------" << endl;
	//for (int i = start; i < end; i++)
	//{

	//	cout << "Process " << (i + 1) << " dir name is:" << sub_dir_name[i].c_str() << endl;
	//	bool state = process(sub_dir_path[i], sub_dir_name[i], i, eps);
	//	if (!state)
	//		continue;
	//	cout << "finish Process " << (i + 1) << " dir name is:" << sub_dir_name[i].c_str() << endl;
	//}
	//cout << "----------Finish batch test----------" << endl << endl;

	Mat rgb = imread("E:\\work\\Fusion\\Test\\Align_Fushion_Test\\output\\bsp_2016_05_24\\pair1\\rcv_rgb_cop.jpg");
	Mat rgb_denoise;
	denoiseColor(rgb, rgb_denoise);
	imwrite("rcv_rgb_denoise.jpg", rgb_denoise);
}