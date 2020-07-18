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

pair<vector<pair <int, int>>, float> Min(pair<vector<pair <int, int>>, float> A, pair<vector<pair <int, int>>, float> B){
    pair<vector<pair <int, int>>, float> X;
    X.second = FLT_MAX;
    if(X.second >= A.second){X = A;}
    if(X.second >= B.second){X = B;}
    return X;
}


pair<vector<pair <int, int>>, float> MinMatching(vector<pair<int,int>> A, vector<pair<int,int>> B){

    //--------------------------------------------------------//

    if(A.size() == 1 && B.size() == 1){
        float pesoA = (A[0].second-A[0].first+1);
        float pesoB = (B[0].second-B[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair <int, int>> X;
        X.push_back({0,0});

        return {X,peso};
    }

    //--------------------------------------------------------//

    else if(A.size() == 1){
        float pesoB = Sumatoria(B);
        float pesoA = (A[0].second-A[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair <int, int>> X;
        for(int i = 0; i < B.size(); i++){
            X.push_back({0,i});
        }

        return {X,peso};
    }

    //--------------------------------------------------------//

    else if(B.size() == 1){
        float pesoA = Sumatoria(A);
        float pesoB = (B[0].second-B[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair <int, int>> X;
        for(int i = 0; i < A.size(); i++){
            X.push_back({i,0});
        }

        return {X,peso};
    }

    //--------------------------------------------------------//

    vector<pair <int, int>> Acopia;
    vector<pair <int, int>> Bcopia;

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> peso2;

    Acopia = A;
    Bcopia = B;

    peso2.second = FLT_MAX; 
    
    Bcopia.pop_back();
    float pesoB = B.back().second-B.back().first + 1;
    for(int l = 0; l < A.size()-1; l++){
        float pesoA = Sumatoria(A,A.size()-l-1,A.size());
        Acopia.pop_back();
        auto OPT = MinMatching(Acopia,Bcopia);
        if(peso2.second > OPT.second+pesoA/pesoB){
            peso2.second = OPT.second+pesoA/pesoB;
            peso2.first =  OPT.first;
            for(int k = A.size()-l; k < A.size();k++)
                peso2.first.push_back({k-1,B.size()-1});
        }
    }

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> peso3;

    Acopia = A;
    Bcopia = B;

    peso3.second = FLT_MAX; 
    
    Acopia.pop_back();
    float pesoA = A.back().second-A.back().first + 1;
    for(int i = 0; i < B.size()-1; i++){
        float pesoB = Sumatoria(B,B.size()-i-1,B.size());
        Bcopia.pop_back();
        auto OPT = MinMatching(Acopia,Bcopia);
        if(peso3.second > OPT.second+pesoA/pesoB){
            peso3.second = OPT.second+pesoA/pesoB;
            peso3.first =  OPT.first;
            for(int j = B.size()-i; j < B.size();j++)
                peso3.first.push_back({A.size()-1,j-1});
        }
    }

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> X = Min(peso2,peso3);
    X.first.push_back({A.size()-1,B.size()-1});

    return X;
}


int main( ) {
    vector<int> A = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0};
    vector<int> B = {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0};
    vector<pair<int,int>> DivisionesA;
    vector<pair<int,int>> DivisionesB;
    int p = 20;

    //--------------------------------------------------------//

    for (int i = 0; i < p; i++){
        if(A[i] == 1){
            int start = i;
            while ( A[i+1] == 1 ){ i++;}
            DivisionesA.push_back({start,i});
        }
    }

    cout << "Divisiones A:\n";
    for(auto i = DivisionesA.begin(); i != DivisionesA.end(); i++){
        cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }


    //--------------------------------------------------------//

    for (int i = 0; i < p; i++){
        if(B[i] == 1){
            int start = i;
            while ( B[i+1] == 1 ){ i++;}
            DivisionesB.push_back({start,i});
        }
    }

    cout << "Divisiones B:\n";
    for(auto i = DivisionesB.begin(); i != DivisionesB.end(); i++){
        cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }

    //--------------------------------------------------------//

    auto X = MinMatching(DivisionesA,DivisionesB);
    for(auto i = X.first.begin(); i != X.first.end(); i++){
        cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }
    return 0;
}