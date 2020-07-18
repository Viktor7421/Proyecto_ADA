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

vector<int> RestBinario(vector<int> X, int min, int max){
    for(int i = min; i < max; i++){
        X.pop_back();
    }
    return X;
}

pair<vector<pair <int, int>>, float> Min(pair<vector<pair <int, int>>, float> A, pair<vector<pair <int, int>>, float> B){
    pair<vector<pair <int, int>>, float> X;
    X.second = FLT_MAX;
    if(X.second >= A.second){X = A;}
    if(X.second >= B.second){X = B;}
    return X;
}


pair<vector<pair <int, int>>, float> MinMatching(vector<int> A, vector<int> B){

    //--------------------------------------------------------//

    vector<pair<int,int>> DivisionesA = Divisiones(A);
    vector<pair<int,int>> DivisionesB = Divisiones(B);

    //--------------------------------------------------------//

    if(DivisionesA.size() == 1 && DivisionesB.size() == 1){
        float pesoA = (DivisionesA[0].second-DivisionesA[0].first+1);
        float pesoB = (DivisionesB[0].second-DivisionesB[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair <int, int>> X;
        X.push_back({0,0});

        return {X,peso};
    }

    //--------------------------------------------------------//

    else if(DivisionesA.size() == 1){
        float pesoB = Sumatoria(DivisionesB);
        float pesoA = (DivisionesA[0].second-DivisionesA[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair <int, int>> X;
        for(int i = 0; i < DivisionesB.size(); i++){
            X.push_back({0,i});
        }

        return {X,peso};
    }

    //--------------------------------------------------------//

    else if(DivisionesB.size() == 1){
        float pesoA = Sumatoria(DivisionesA);
        float pesoB = (DivisionesB[0].second-DivisionesB[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair <int, int>> X;
        for(int i = 0; i < DivisionesA.size(); i++){
            X.push_back({i,0});
        }

        return {X,peso};
    }

    //--------------------------------------------------------//

    vector<pair <int, int>> Acopia;
    vector<pair <int, int>> Bcopia;

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> peso1;

    Acopia = DivisionesA;
    Bcopia = DivisionesB;

    peso1.second = FLT_MAX; 
    
    int index_1;

    Bcopia.pop_back();
    float pesoB = DivisionesB.back().second-DivisionesB.back().first + 1;
    for(int l = 0; l < DivisionesA.size()-1; l++){
        float pesoA = Sumatoria(DivisionesA,DivisionesA.size()-l-1,DivisionesA.size());
        Acopia.pop_back();
        auto binarioA = RestBinario(A,Acopia.back().second+1,A.size());
        auto binarioB = RestBinario(B,Bcopia.back().second+1,B.size());
        auto OPT = MinMatching(binarioA,binarioB);
        if(peso1.second > OPT.second+pesoA/pesoB){
            peso1.second = OPT.second+pesoA/pesoB;
            peso1.first =  OPT.first;
            index_1 = l;
        }
    }

    for(int k = DivisionesA.size()-index_1; k < DivisionesA.size();k++)
            peso1.first.push_back({k-1,DivisionesB.size()-1});

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> peso2;

    Acopia = DivisionesA;
    Bcopia = DivisionesB;

    peso2.second = FLT_MAX; 
    
    int index_2;

    Acopia.pop_back();
    Bcopia.pop_back();
    float pesoA = DivisionesA.back().second-DivisionesA.back().first + 1;
    for(int l = 1; l < DivisionesB.size()-1; l++){
        float pesoB = Sumatoria(DivisionesB,DivisionesB.size()-l-1,DivisionesB.size());
        Bcopia.pop_back();
        auto binarioA = RestBinario(A,Acopia.back().second+1,A.size());
        auto binarioB = RestBinario(B,Bcopia.back().second+1,B.size());
        auto OPT = MinMatching(binarioA,binarioB);
        if(peso2.second > OPT.second+pesoA/pesoB){
            peso2.second = OPT.second+pesoA/pesoB;
            peso2.first =  OPT.first;
            index_2 = l;
        }
    }

    for(int k = DivisionesB.size()-index_2; k < DivisionesB.size();k++)
        peso2.first.push_back({DivisionesA.size()-1,k-1});

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> X = Min(peso1,peso2);
    X.first.push_back({DivisionesA.size()-1,DivisionesB.size()-1});

    return X;
}


int main( ) {
    vector<int> A = {0,0,0,0,0,0,1,1,0,1,1,0,1,1,1};
    vector<int> B = {1,0,1,1,0,0,1,1,0,0,0,0,1,1,0};
    
    vector<pair<int,int>> DivisionesA = Divisiones(A);
    vector<pair<int,int>> DivisionesB = Divisiones(B);

    auto X = MinMatching(A,B);
    for(auto i = X.first.begin(); i != X.first.end(); i++){
        cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }
    cout << X.second << "\n";
    return 0;
}