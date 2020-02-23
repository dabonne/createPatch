//
// Created by lirisimagine on 18/02/2020.
//

#include "Patch.h"
Patch::Patch(Mat &image): m_image(image){
    m_nbAnnotation = 0;
    m_ratio = 0.0;
}
Patch::Patch() {
    Mat image;
    m_image = image;
    m_flag = false;
    m_ratio = 0.0;
    m_nbAnnotation = 0;
}

void Patch::setImage(Mat &image) {
    m_image = image;
}
Mat Patch::getImage() const {
    return m_image;
}
void Patch::setFlag(){
    m_flag = true;
}

bool Patch::getFlag() const {
    return m_flag;
}
void Patch::setRatio(){
    m_ratio = double(countNonZero(m_image)/double(m_image.rows));
}

double Patch::getRatio() const {
    return m_ratio;
}
void Patch::setNbAnnotation(){
    m_nbAnnotation = countNonZero(m_image);
}
int Patch::getNbAnnotation() const {
    return m_nbAnnotation;
}
Patch::~Patch() {}