#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "Lectura-IMG.cpp"
#include "Voraz.cpp"
using namespace std;
using namespace cv;

vector<Mat> Animation(Mat IMAGEN1, Mat IMAGEN2, int Divisiones)
{
    vector<vector<int>> IMAGEN_01_1 = To01Scale(IMAGEN1, 120);
    vector<vector<int>> IMAGEN_01_2 = To01Scale(IMAGEN2, 120);
    
    vector<vector<vector<int>>> IMAGENES;IMAGENES.push_back(IMAGEN_01_1);

    auto matching = MinTransformacion(IMAGEN_01_1,IMAGEN_01_2);
    for (auto i = matching.first.begin(); i != matching.first.end(); i++)
    {
        for (auto j = (*i).begin(); j != (*i).end(); j++)
        {
            if ((*j).first.size() > (*j).second.size())
            {
                float val = float((*j).second[0].second-(*j).second[0].first+1);
                vector<float> temp;
                vector<int> temp2;
                int total = 0;
                int total2 = 0;

                for (auto k = (*j).first.begin(); k != (*j).first.end(); k++)
                {
                    float T = (*k).second-(*k).first+1;
                    temp.push_back(T);
                    total+=T;
                }

                for (auto k = temp.begin(); k != temp.end(); k++)
                {
                    int T = round(float((*j).first.size()*(*k))/float(total));
                    temp2.push_back(T);
                    total2+=T;
                }
            }
        }
    }
}