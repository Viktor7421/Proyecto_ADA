#include <iostream>
#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "Min-Transformacion/Lectura-IMG.cpp"
using namespace std;
using namespace cv;

int fib(int n)
{
    if (n < 2)
        return n;

    return fib(n - 1) + fib(n - 2);
}

int main()
{
    string fileName = "Min-Transformacion/IMG/lucario.jpg";
    Mat IMAGEN = imread(fileName, IMREAD_COLOR);
    Mat IMAGEN2 = imread(fileName, IMREAD_COLOR);
    const char* WIN_IMG = "Under Test";
    const char* WIN_VID = "Reference";
    namedWindow(WIN_IMG, WINDOW_AUTOSIZE);
    namedWindow(WIN_VID, WINDOW_AUTOSIZE);
    moveWindow(WIN_IMG, 400        , 0);         
    moveWindow(WIN_VID, 700, 0);         

    //------------------------Imagen----------------------//

    vector<vector<int>> IMAGEN_01 = To01Scale(IMAGEN2, 120);

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
    cv::imshow(WIN_IMG, IMAGEN2);

    //----------------------Animacion-----------------------//

    cv::Mat frame = IMAGEN.clone();
    int delay = 100;

    for (int i = 0; i < 256; i++)
    {

        // Display the frame
        cv::imshow(WIN_VID, frame);

        cout << "Frame: " << i << "# " << endl;

        vector<vector<int>> IMAGEN_01 = To01Scale(IMAGEN.clone(), i);

        for (int r = 0; r < IMAGEN2.rows; r++)
        {
            for (int c = 0; c < IMAGEN2.cols; c++)
            {
                if (IMAGEN_01[r][c] == 0)
                {
                    frame.at<Vec3b>(r, c)[0] = 0;
                    frame.at<Vec3b>(r, c)[1] = 0;
                    frame.at<Vec3b>(r, c)[2] = 0;
                }
                else
                {
                    frame.at<Vec3b>(r, c)[0] = 255;
                    frame.at<Vec3b>(r, c)[1] = 255;
                    frame.at<Vec3b>(r, c)[2] = 255;
                }
            }
        }


        // For breaking the loop
        if (cv::waitKey(27) >= 0) break;
    }

    // Destroy all windows
    cv::destroyAllWindows();


    //------------------------------------------------------//

    return 0;
}