#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "Computing.h"
#include "Patch.h"

using namespace cv;
using namespace std;
int main(int argc, char** argv) {
    samples::addSamplesDataSearchPath("./rasters");
    const string keys = "{@input1 | new_029000665728.pbm | raster des annotations}"
                        "{@input2 | new_029000665728.png | l'ortho-image de la mine}";
    CommandLineParser parser(argc, argv, keys);
    Mat shapeRaster = imread(samples::findFile(parser.get<String>("@input1"),true, true ), IMREAD_COLOR);
    Mat orthoMosaiq = imread(samples::findFile(parser.get<string>("@input2"), true, true), IMREAD_COLOR);
    if (!shapeRaster.empty() && !orthoMosaiq.empty())
    {
        Mat raster = imageProcess(shapeRaster);
        vector <vector<Patch> > tableImages;
         imageCroping(raster, orthoMosaiq);
        //cout << tableImages.at(0).size();
        //WriteOnDisk(tableImages);

    } else {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    return 0;
}