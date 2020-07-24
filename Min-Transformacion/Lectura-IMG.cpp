#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

vector<vector<int>> To01Scale(Mat IMAGEN, int val)
{
    vector<vector<int>> IMAGEN_01;

    for (int r = 0; r < IMAGEN.rows; r++)
    {
        for (int c = 0; c < IMAGEN.cols; c++)
        {
            auto R = IMAGEN.at<Vec3b>(r, c)[0];
            auto G = IMAGEN.at<Vec3b>(r, c)[1];
            auto B = IMAGEN.at<Vec3b>(r, c)[2];

            IMAGEN.at<Vec3b>(r, c)[0] = 0.299 * R + 0.587 * G + 0.114 * B;
            IMAGEN.at<Vec3b>(r, c)[1] = 0.299 * R + 0.587 * G + 0.114 * B;
            IMAGEN.at<Vec3b>(r, c)[2] = 0.299 * R + 0.587 * G + 0.114 * B;
        }
    }

    for (int r = 0; r < IMAGEN.rows; r++)
    {
        vector<int> temp;
        for (int c = 0; c < IMAGEN.cols; c++)
        {
            if (IMAGEN.at<Vec3b>(r, c)[0] < val)
            {
                temp.push_back(0);
            }
            else 
            {
                temp.push_back(1);
            }
        }
        IMAGEN_01.push_back(temp);
        temp.clear();
    }

    IMAGEN.release();
    return IMAGEN_01;
}