#include "iostream"
#include <utility> 
#include <vector> 
#include <limits.h>
#include <float.h>
using namespace std;

float Sumatoria(vector<pair<int,int>> X){
    int Suma = 0;
    for(int i = 0; i < X.size(); i++){
        Suma = Suma + (X[i].second-X[i].first+1);
    }
    return Suma;
}

float Sumatoria(vector<pair<int,int>> X, int min, int max){
    int Suma = 0;
    for(int i = min; i < max; i++){
        Suma = Suma + (X[i].second-X[i].first+1);
    }
    return Suma;
}

vector<pair<int,int>> Divisiones(vector<int> X){
    vector<pair<int,int>> Divisiones;
    for (int i = 0; i < X.size(); i++){
        if(X[i] == 1){
            int start = i;
            while ( X[i+1] == 1 ){ i++;}
            Divisiones.push_back({start,i});
        }
    }
    return Divisiones;
}

pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> Min(pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> A, pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> B){
    pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> X;
    X.second = FLT_MAX;
    if(X.second >= A.second){X = A;}
    if(X.second >= B.second){X = B;}
    return X;
}


pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> PromMinMatching(vector<int> A, vector<int> B)
{

    //--------------------------------------------------------//

    vector<pair<int,int>> DivisionesA = Divisiones(A);
    vector<pair<int,int>> DivisionesB = Divisiones(B);
    
    if(DivisionesB.empty())
    {
        vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>> X;
        return {X,0};
    }
    else if(DivisionesA.empty())
    {
        vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>> X;
        vector<pair<int,int>> temp;
        X.push_back({temp,DivisionesB});
        return {X,0};
    }
    //--------------------------------------------------------//

    else if(DivisionesA.size() == 1 && DivisionesB.size() == 1){
        float pesoA = (DivisionesA[0].second-DivisionesA[0].first+1);
        float pesoB = (DivisionesB[0].second-DivisionesB[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>> X;
        X.push_back({DivisionesA,DivisionesB});

        return {X,peso};
    }

    //--------------------------------------------------------//

    else if(DivisionesA.size() == 1){
        float pesoB = Sumatoria(DivisionesB);
        float pesoA = (DivisionesA[0].second-DivisionesA[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>> X;
        X.push_back({DivisionesA,DivisionesB});

        return {X,peso};
    }

    //--------------------------------------------------------//

    else if(DivisionesB.size() == 1){
        float pesoA = Sumatoria(DivisionesA);
        float pesoB = (DivisionesB[0].second-DivisionesB[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>> X;
        X.push_back({DivisionesA,DivisionesB});

        return {X,peso};
    }
    //--------------------------------------------------------//

    pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float>** M;

    M = new pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float>* [DivisionesA.size()];
    for(int i = 0; i < DivisionesA.size(); i++) {
        M[i] = new pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> [DivisionesB.size()];  
    }

    //-------------------------------------------------------//

    vector<pair <int, int>> Acopia;
    vector<pair <int, int>> Bcopia;

    vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>> X1;
    pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> X2;

    vector<pair <int, int>> tempA;
    vector<pair <int, int>> tempB;
    pair <int, int> Ai;
    pair <int, int> Bi;

    Bi = DivisionesB.front(); 
    tempB.push_back(Bi);
    for (int i = 0; i < DivisionesA.size(); i++)
    {
        X1.clear();
        float pesoA = Sumatoria(DivisionesA, 0, i+1);
        float pesoB = (Bi.second-Bi.first+1);
        float peso = pesoA/pesoB;
        Ai = DivisionesA[i]; 
        tempA.push_back(Ai);
        X1.push_back({tempA,tempB});

        M[i][0] = {X1,peso};
    }

    tempA.clear();
    tempB.clear();
    X1.clear();

    Ai = DivisionesA.front(); 
    tempA.push_back(Ai);
    for (int i = 0; i < DivisionesB.size(); i++)
    {
        X1.clear();
        float pesoB = Sumatoria(DivisionesB, 0, i+1);
        float pesoA = (Ai.second-Ai.first+1);
        float peso = pesoA/pesoB;
        Bi = DivisionesB[i]; 
        tempB.push_back(Bi);
        X1.push_back({tempA,tempB});

        M[0][i] = {X1,peso};
    }

    Acopia.clear();
    Bcopia.clear();

    for (int i = 1; i < DivisionesA.size(); i++)
    {
        for (int j = 1; j < DivisionesB.size(); j++)
        {
            tempA.clear();
            tempB.clear();

            pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> peso1;

            peso1.second = FLT_MAX; 
            
            int index_1;

            float pesoB = Sumatoria(DivisionesB, j, j+1);
            for(int l = 0; l < i; l++){
                float pesoA = Sumatoria(DivisionesA,i-l,i+1);
                auto OPT = M[i-l-1][j-1];
                if(peso1.second > (OPT.second+pesoA/pesoB)/float(OPT.first.size()+1)){
                    peso1.second = (OPT.second+pesoA/pesoB)/float(OPT.first.size()+1);
                    peso1.first =  OPT.first;
                    index_1 = l;
                }
            }
            
            pair <int, int> Bi = DivisionesB[j]; 
            tempB.push_back(Bi);
            for (int k = i-index_1; k < i+1;k++)
            {
                pair <int, int> Ai = DivisionesA[k]; 
                tempA.push_back(Ai);
            }
            peso1.first.push_back({tempA,tempB});

            //--------------------------------------------------------//

            pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> peso2;

            Acopia = DivisionesA;
            Bcopia = DivisionesB;
            tempA.clear();
            tempB.clear();

            peso2.second = FLT_MAX; 
            
            int index_2;

            float pesoA = Sumatoria(DivisionesA,i,i+1);
            for(int l = 0; l < j; l++){
                float pesoB = Sumatoria(DivisionesB,j-l,j+1);
                auto OPT = M[i-1][j-l-1];
                if(peso2.second > (OPT.second+pesoA/pesoB)/float(OPT.first.size()+1)){
                    peso2.second = (OPT.second+pesoA/pesoB)/float(OPT.first.size()+1);
                    peso2.first =  OPT.first;
                    index_2 = l;
                }
            }

            pair <int, int> Ai = DivisionesA[i]; 
            tempA.push_back(Ai);
            for (int k = j-index_2; k < j+1;k++)
            {
                pair <int, int> Bi = DivisionesB[k]; 
                tempB.push_back(Bi);
            }
            peso2.first.push_back({tempA,tempB});
            //--------------------------------------------------------//

            X2 = Min(peso1,peso2);
            M[i][j] = X2;
        }
    }
    
    pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> result = M[DivisionesA.size()-1][DivisionesB.size()-1]; 
    
    for(int i = 0; i < DivisionesA.size();i++){
        delete[] M[i];
    }
    delete[] M;

    DivisionesA.clear();
    DivisionesB.clear();
    Acopia.clear();
    Bcopia.clear();
    tempA.clear();
    tempB.clear();

    return result;
}
/*
int main( ) {
    vector<int> A = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    vector<int> B = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    vector<pair<int,int>> DivisionesA;
    vector<pair<int,int>> DivisionesB;
    int p = A.size();

    //--------------------------------------------------------//

    for (int i = 0; i < p; i++){
        if(A[i] == 1){
            int start = i;
            while ( A[i+1] == 1 ){ i++;}
            DivisionesA.push_back({start,i});
        }
    }

    //--------------------------------------------------------//

    for (int i = 0; i < p; i++){
        if(B[i] == 1){
            int start = i;
            while ( B[i+1] == 1 ){ i++;}
            DivisionesB.push_back({start,i});
        }
    }

    auto X = MinMatching(A,B);
    //--------------------------------------------------------//

    for(auto i = X.first.begin(); i != X.first.end(); i++){
        cout << '[';
        for (auto j = (*i).first.begin(); j != (*i).first.end(); j++)
        {
            cout << '(' << (*j).first << ',' << (*j).second << ")";
        }
        cout << "],[";
        for (auto j = (*i).second.begin(); j != (*i).second.end(); j++)
        {
            cout << '(' << (*j).first << ',' << (*j).second << ")";
        }
        cout << "]\n";
        //cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }
    cout << X.second << "\n";
    return 0;
}*/