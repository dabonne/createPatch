//
// Created by lirisimagine on 18/02/2020.
//

#ifndef CREATPATCH_PATCH_H
#define CREATPATCH_PATCH_H

#include "opencv2/imgproc.hpp"

using namespace cv;
class Patch {
public:
    Patch(Mat &image);
    Patch();
    void setNbAnnotation();
    int getNbAnnotation() const;
    void setFlag();
    bool getFlag() const;
    void setImage(Mat &image);

    void setRatio();
    double getRatio() const;
    Mat getImage() const;
    Rect rect_from_big_image;
    ~Patch();

private:
    int m_nbAnnotation;
    bool m_flag{};
    double m_ratio;
    Mat m_image;
};


#endif //CREATPATCH_PATCH_H
