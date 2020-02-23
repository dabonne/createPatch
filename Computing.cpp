//
// Created by lirisimagine on 18/02/2020.
//

#include <iostream>
#include "Computing.h"
#include "Patch.h"
void show_wait_destroy(const char* winname, cv::Mat &img) {
    imshow(winname, img);
    moveWindow(winname, 500, 0);
    waitKey(0);
    destroyWindow(winname);
}

Mat imageProcess(Mat image){
    double thresh = 55;
    double maxValue = 255;
    cv::cvtColor(image, image, COLOR_BGR2GRAY);
    threshold(image, image, thresh, maxValue, THRESH_BINARY);
    return image;
}

void imageCroping(Mat &img, Mat &real){

    Mat imR;
    Mat imReal;
    resize(img, imR, Size(32935, 30880));
    resize(real, imReal, Size(32935, 30880));
    vector <Patch> tableImgR;
    vector <Patch> tableImgReal;


    cout << "_________ Start croping ___________" << endl;
    string const file_open("./Result_data/state/statesPatch.txt");
    ofstream file_stream(file_open.c_str());
    if (!file_stream) {
        cout << "ERREUR: Impossible d'ouvrir le fichier des states" << endl;
        exit(0);
    }
    for(int t: geometriqueTable()){
        int carrier = 0;
        int notCarrier = 0;
        int autre = 0;
        int height(t), width(t);
        file_stream << height << " ";
        for(int x(0); x+height <= imR.cols; x += width)
        {
            for(int y(0); y+width <= imR.rows; y += height)
            {
                Rect imgRect = Rect(x, y, width, height);
                if(0 <= imgRect.x && 0 <= imgRect.width && imgRect.x + imgRect.width < img.cols &&
                   0 <= imgRect.y && 0 <= imgRect.height && imgRect.y + imgRect.height < img.rows)
                {
                    Mat new_image = img(imgRect);
                    Mat new_imageReal = real(imgRect);
                    Patch image(new_image);
                    Patch imageReal(new_imageReal);
                    int aire = (image.getImage().rows * image.getImage().cols)/2;
                    image.rect_from_big_image = imgRect;
                    image.setNbAnnotation();
                    if(image.getNbAnnotation() && aire < image.getNbAnnotation()){
                        image.Patch::setFlag();
                        carrier ++;
                    } else if(image.getNbAnnotation() && aire > image.getNbAnnotation()){
                        autre++;
                    } else{
                        notCarrier ++;
                    }
                    imageReal.rect_from_big_image = imgRect;
                    tableImgR.push_back(image);
                    tableImgReal.push_back(imageReal);
                }
            }
        }
        file_stream << carrier << " " << notCarrier << " "<< autre << endl;
    }


    /*vector < vector<Patch> > vect_array;
    vect_array.push_back(tableImgR);
    vect_array.push_back(tableImgReal);*/
    cout << "_________ End croping ___________" << endl;
   // return vect_array;
}

void WriteOnDisk(vector <vector<Patch> > &tableImag){
    cout << "*********************************************************************************" << endl;
    cout << "=========================Write On Disk====================" << endl;
    cout << "*********************************************************************************" << endl;
    vector <Patch> shape = tableImag.at(0);
    vector <Patch> ortho = tableImag.at(1);
   /* int max = 0;
    string const file_open("./Result_data/state/statesFile.txt");
    ofstream file_stream(file_open.c_str());
    if (!file_stream) {
        cout << "ERREUR: Impossible d'ouvrir le fichier des states" << endl;
        exit(0);
    }*/

    for (int i(0); i< shape.size();i ++) {
        cout << shape.at(i).Patch::getFlag()<< endl;
        int aire = (shape.at(i).Patch::getImage().rows * shape.at(i).Patch::getImage().cols)/2;
        if(shape.at(i).Patch::getFlag() != 0 && (aire < shape.at(i).Patch::getNbAnnotation())){

            imwrite("./Result_data/ShapesRaster/Annotes/img"+to_string(i)+".pbm",shape.at(i).Patch::getImage());
            imwrite("./Result_data/OrthoImages/Annotes/img"+to_string(i)+".png",ortho.at(i).Patch::getImage());
        }
        else if(!shape.at(i).Patch::getFlag()){
            imwrite("./Result_data/ShapesRaster/NonAnnotes/img"+to_string(i)+".pbm",shape.at(i).Patch::getImage());
            imwrite("./Result_data/OrthoImages/NonAnnotes/img"+to_string(i)+".png",ortho.at(i).Patch::getImage());
        } else {
            imwrite("./Result_data/ShapesRaster/Autres/img"+to_string(i)+".pbm",shape.at(i).Patch::getImage());
            imwrite("./Result_data/OrthoImages/Autres/img"+to_string(i)+".png",ortho.at(i).Patch::getImage());
        }

    }

}

vector<int> geometriqueTable(void){
    double Q = exp((log(3000)-log(100))/50);
    vector <int> values;

    double U = 100;
    int n = 50;
    while(n > 0){
        values.push_back(U);
        U = round(U * Q);
        n--;
    }
    return values;
}
