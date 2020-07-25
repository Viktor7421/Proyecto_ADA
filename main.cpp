#include <iostream>
#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "Min-Transformacion/Animacion-IMG_Voraz.cpp"
using namespace std;
using namespace cv;

int main()
{
    Mat IMAGEN = imread("Min-Transformacion/IMG/lucario.jpg", IMREAD_COLOR);
    Mat IMAGEN2 = imread("Min-Transformacion/IMG/megalucario.jpg", IMREAD_COLOR);
    Mat IMAGEN3 = imread("Min-Transformacion/IMG/lucario.jpg", IMREAD_COLOR);
    Mat IMAGEN4 = imread("Min-Transformacion/IMG/megalucario.jpg", IMREAD_COLOR);
    const char* WIN_IMG = "IMG1";
    const char* WIN_IMG2 = "IMG2";
    const char* WIN_VID = "Video";
    namedWindow(WIN_IMG, WINDOW_AUTOSIZE);
    namedWindow(WIN_IMG2, WINDOW_AUTOSIZE);
    namedWindow(WIN_VID, WINDOW_AUTOSIZE);
    moveWindow(WIN_IMG, 400, 0);         
    moveWindow(WIN_VID, 700, 0);         

    //------------------------Imagen----------------------//

    vector<vector<int>> IMAGEN_01 = To01Scale(IMAGEN.clone(), 120);

    for (int r = 0; r < IMAGEN.rows; r++)
    {
        for (int c = 0; c < IMAGEN.cols; c++)
        {
            if (IMAGEN_01[r][c] == 0)
            {
                IMAGEN.at<Vec3b>(r, c)[0] = 0;
                IMAGEN.at<Vec3b>(r, c)[1] = 0;
                IMAGEN.at<Vec3b>(r, c)[2] = 0;
            }
            else
            {
                IMAGEN.at<Vec3b>(r, c)[0] = 255;
                IMAGEN.at<Vec3b>(r, c)[1] = 255;
                IMAGEN.at<Vec3b>(r, c)[2] = 255;
            }
        }
    }

    IMAGEN_01 = To01Scale(IMAGEN2.clone(), 120);

    for (int r = 0; r < IMAGEN2.rows; r++)
    {
        for (int c = 0; c < IMAGEN2.cols; c++)
        {
            if (IMAGEN_01[r][c] == 0)
            {
                IMAGEN2.at<Vec3b>(r, c)[0] = 0;
                IMAGEN2.at<Vec3b>(r, c)[1] = 0;
                IMAGEN2.at<Vec3b>(r, c)[2] = 0;
            }
            else
            {
                IMAGEN2.at<Vec3b>(r, c)[0] = 255;
                IMAGEN2.at<Vec3b>(r, c)[1] = 255;
                IMAGEN2.at<Vec3b>(r, c)[2] = 255;
            }
        }
    }
    cv::imshow(WIN_IMG, IMAGEN);
    cv::imshow(WIN_IMG2, IMAGEN2);

    //----------------------Animacion-----------------------//
 
    vector<Mat> animation = Animation(IMAGEN3.clone(), IMAGEN4.clone(), 300);

    cout << "Animation END" << endl;

    for (auto i = animation.begin(); i != animation.end(); i++)
    {
        cv::imshow(WIN_VID, (*i));
        if (cv::waitKey(27) >= 0) break;
    }

    // Destroy all windows

    animation.clear();

    waitKey(0);
    cv::destroyAllWindows();
    IMAGEN3.release();
    IMAGEN4.release();
    //------------------------------------------------------//

    return 0;
}