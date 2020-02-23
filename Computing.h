//
// Created by lirisimagine on 18/02/2020.
//

#ifndef CREATPATCH_COMPUTING_H
#define CREATPATCH_COMPUTING_H
#include "opencv2/imgproc.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Patch.h"
#include "fstream"

using namespace cv;
using namespace std;

void show_wait_destroy(const char* winname, cv::Mat &img);
vector<int> geometriqueTable(void);
Mat imageProcess(Mat image);
void imageCroping(Mat &img, Mat &real);
void WriteOnDisk(vector <vector<Patch> > &tableImag);
#endif //CREATPATCH_COMPUTING_H
