#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "Lectura-IMG.cpp"
#include "Dinamico_Promedio.cpp"
using namespace std;
using namespace cv;

struct RGB
{
    float R;
    float G;
    float B;
};


vector<Mat> Animation(Mat IMAGEN1, Mat IMAGEN2, int Particiones)
{
    vector<vector<int>> IMAGEN_01_1 = To01Scale(IMAGEN1.clone(), 120);
    vector<vector<int>> IMAGEN_01_2 = To01Scale(IMAGEN2.clone(), 120);
    pair<vector<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>>, float> matchings = PromMinTransformacion(IMAGEN_01_1, IMAGEN_01_2);
    vector<Mat> animation;
    //-------------------Vectores-------------------------//
    vector<vector<vector<int>>> imagenesIntermedias;
    for(int e = 0; e < Particiones; e++){
        vector<vector<int>> temp1;
        for(int i = 0; i < IMAGEN_01_1.size(); i++)
        {
            vector<int> temp2;
            for(int j = 0; j < IMAGEN_01_1[0].size();j++)
            {
                temp2.push_back(0);
            }
            temp1.push_back(temp2);
        }
        imagenesIntermedias.push_back(temp1);
    }

    int index = 0;
    for(auto i = matchings.first.begin(); i != matchings.first.end(); i++, index++)
    {
        if((*i).empty()){
            cout << "null" << endl;
        }
        else
        {
            for(auto j = (*i).begin(); j != (*i).end(); j++)
            {
                if((*j).first.empty())
                {
                    int m = 0;
                    for(auto l = (*j).second.begin(); l != (*j).second.end(); l++, m++)
                    {
                        for(int n = (*l).first; n <= (*l).second; n++)
                        {
                            imagenesIntermedias[m][index][n] = 1;
                        }
                    }
                }
                else
                {
                    vector<vector<pair <int, int>>> imgIntermedias;
                    auto A = (*j).first, B = (*j).second;
                    vector<int> D;
                    D.push_back(0);
                    if(A.size() > B.size())
                    {
                        int TotalA = 0, TotalB = (B[0].second-B[0].first+1);
                        for(auto k = A.begin(); k != A.end(); k++)
                        {
                            TotalA+=((*k).second-(*k).first+1);
                        }
                        for(auto k = A.begin(); k != A.end(); k++)
                        {
                            D.push_back(D.back()+round(float(((*k).second-(*k).first+1)*TotalB)/float(TotalA)));
                        }
                        int index1 = 0;
                        for(auto k = A.begin(); k != A.end(); k++,index1++)
                        {
                            pair<int,int> tempB = {B[0].first+D[index1],round(B[0].first+D[index1+1]-(float(1)/float(A.size()))*(index1+1))};
                            vector<pair <int, int>> temp;
                            float s = float(abs((*k).first-tempB.first))/float(Particiones+1);
                            float f = float(abs((*k).second-tempB.second))/float(Particiones+1);
                            for(int l = 0; l < Particiones; l++)
                            {
                                if((*k).first > tempB.first && (*k).second > tempB.second)
                                {
                                    temp.push_back({(round((*k).first)-s*l),(round((*k).second)-f*l)});
                                }
                                else if((*k).first > tempB.first && (*k).second <= tempB.second)
                                {
                                    temp.push_back({(round((*k).first)-s*l),(round((*k).second)+f*l)});
                                }
                                else if((*k).first <= tempB.first && (*k).second > tempB.second)
                                {
                                    temp.push_back({(round((*k).first)+s*l),(round((*k).second)-f*l)});
                                }
                                else if((*k).first <= tempB.first && (*k).second <= tempB.second)
                                {
                                    temp.push_back({(round((*k).first)+s*l),(round((*k).second)+f*l)});
                                }
                            }
                            imgIntermedias.push_back(temp);
                        }
                        
                    }
                    else if(A.size() <= B.size())
                    {
                        int TotalB = 0, TotalA = (A[0].second-A[0].first+1);
                        for(auto k = B.begin(); k != B.end(); k++)
                        {
                            TotalB+=((*k).second-(*k).first+1);
                        }
                        for(auto k = B.begin(); k != B.end(); k++)
                        {
                            D.push_back(D.back()+round(float(((*k).second-(*k).first+1)*TotalA)/float(TotalB)));
                        }
                        int index2 = 0;
                        for(auto k = B.begin(); k != B.end(); k++,index2++)
                        {
                            pair<int,int> tempA = {A[0].first+D[index2],round(A[0].first+D[index2+1]-(float(1)/float(A.size()))*(index2+1))};
                            vector<pair <int, int>> temp;
                            float s = float(abs((*k).first-tempA.first))/float(Particiones+1);
                            float f = float(abs((*k).second-tempA.second))/float(Particiones+1);
                            for(int l = 0; l < Particiones; l++)
                            {
                                if((*k).first < tempA.first && (*k).second < tempA.second)
                                {
                                    temp.push_back({(tempA.first-s*l),(tempA.second-f*l)});
                                }
                                else if((*k).first < tempA.first && (*k).second >= tempA.second)
                                {
                                    temp.push_back({(tempA.first-s*l),(tempA.second+f*l)});
                                }
                                else if((*k).first >= tempA.first && (*k).second < tempA.second)
                                {
                                    temp.push_back({(tempA.first+s*l),(tempA.second-f*l)});
                                }
                                else if((*k).first >= tempA.first && (*k).second >= tempA.second)
                                {
                                    temp.push_back({(tempA.first+s*l),(tempA.second+f*l)});
                                }
                            }
                            imgIntermedias.push_back(temp);
                        }
                    }
                    vector<int> temp;
                    for(auto k = imgIntermedias.begin(); k != imgIntermedias.end(); k++)
                    {
                        int m = 0;
                        for(auto l = (*k).begin(); l != (*k).end(); l++, m++)
                        {
                            for(int n = (*l).first; n <= (*l).second; n++)
                            {
                                imagenesIntermedias[m][index][n] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    //---------------Matriz conversora----------------//
    
    vector<vector<RGB>> martiz_conversora;
    for (int r = 0; r < IMAGEN1.rows; r++)
    {
        vector<RGB> temp;
        for (int c = 0; c < IMAGEN1.cols; c++)
        {
            temp.push_back({float(IMAGEN2.at<Vec3b>(r, c)[0]-IMAGEN1.at<Vec3b>(r, c)[0])/float(Particiones+1),float(IMAGEN2.at<Vec3b>(r, c)[1]-IMAGEN1.at<Vec3b>(r, c)[1])/float(Particiones+1),float(IMAGEN2.at<Vec3b>(r, c)[2]-IMAGEN1.at<Vec3b>(r, c)[2])/float(Particiones+1)});
        }
        martiz_conversora.push_back(temp);
        temp.clear();
    }



    //-------------------Mats-------------------------//
    /*for(int i = 0; i < imagenesIntermedias.size(); i++)
    {

        Mat IMAGEN_temp = IMAGEN1.clone();
        for (int r = 0; r < IMAGEN_temp.rows; r++)
        {
            for (int c = 0; c < IMAGEN_temp.cols; c++)
            {
                IMAGEN_temp.at<Vec3b>(r, c)[0] = round(IMAGEN1.at<Vec3b>(r, c)[0]+martiz_conversora[r][c].R*i);
                IMAGEN_temp.at<Vec3b>(r, c)[1] = round(IMAGEN1.at<Vec3b>(r, c)[1]+martiz_conversora[r][c].G*i);
                IMAGEN_temp.at<Vec3b>(r, c)[2] = round(IMAGEN1.at<Vec3b>(r, c)[2]+martiz_conversora[r][c].B*i);
            }
        }
        animation.push_back(IMAGEN_temp);
    }*/

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
        IMAGEN_temp.release();
    }

    IMAGEN1.release();
    IMAGEN2.release();
    IMAGEN_01_1.clear();
    IMAGEN_01_2.clear();

    return animation;
}