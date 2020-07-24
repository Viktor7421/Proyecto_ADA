#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;
struct RGB
{
    float R;
    float G;
    float B;
};

vector<Mat> Coloracion(Mat IMAGEN1, Mat IMAGEN2, vector<vector<vector<int>>> imagenesIntermedias)
{
    vector<Mat> animation;
    for(int i = 0; i < imagenesIntermedias.size(); i++)
    {

        Mat IMAGEN_temp = IMAGEN1.clone();
        for (int r = 0; r < IMAGEN_temp.rows; r++)
        {
            for (int c = 0; c < IMAGEN_temp.cols; c++)
            {
                if(imagenesIntermedias[i][r][c] == 0){
                    IMAGEN_temp.at<Vec3b>(r, c)[0] = 0;
                    IMAGEN_temp.at<Vec3b>(r, c)[1] = 0;
                    IMAGEN_temp.at<Vec3b>(r, c)[2] = 0;
                }
                else
                {
                    IMAGEN_temp.at<Vec3b>(r, c)[0] = 255;
                    IMAGEN_temp.at<Vec3b>(r, c)[1] = 255;
                    IMAGEN_temp.at<Vec3b>(r, c)[2] = 255;
                }
            }
        }
        animation.push_back(IMAGEN_temp);
}