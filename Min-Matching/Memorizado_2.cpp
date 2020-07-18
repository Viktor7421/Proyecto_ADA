#include "iostream"
#include <utility> 
#include <vector> 
#include <limits.h>
#include <float.h>
using namespace std;

int n;
int m;
pair<vector<pair <int, int>>, float>** M;

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
    
    if(M[A.size()-1][B.size()-1].second != -1){
        return M[A.size()-1][B.size()-1];
    }

    //--------------------------------------------------------//
    
    else if(A.size() == 1 && B.size() == 1){
        float pesoA = (A[0].second-A[0].first+1);
        float pesoB = (B[0].second-B[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair <int, int>> X;
        X.push_back({0,0});

        M[A.size()-1][B.size()-1] = {X,peso};

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
        
        M[A.size()-1][B.size()-1] = {X,peso};

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

        M[A.size()-1][B.size()-1] = {X,peso};

        return {X,peso};
    }

    //--------------------------------------------------------//

    vector<pair <int, int>> Acopia = A;
    vector<pair <int, int>> Bcopia = B;

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> peso1;

    Acopia = A;
    Bcopia = B;

    peso1.second = FLT_MAX; 
    
    Bcopia.pop_back();
    float pesoB = B.back().second-B.back().first + 1;
    for(int i = 0; i < A.size()-1; i++){
        float pesoA = Sumatoria(A,A.size()-i-1,A.size());
        Acopia.pop_back();
        auto OPT = MinMatching(Acopia,Bcopia);
        if(peso1.second > OPT.second+pesoA/pesoB){
            peso1.second = OPT.second+pesoA/pesoB;
            peso1.first =  OPT.first;
            for(int j = A.size()-i; j < A.size();j++)
                peso1.first.push_back({j-1,B.size()-1});
        }
    }

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> peso2;

    Acopia = A;
    Bcopia = B;

    peso2.second = FLT_MAX; 
    
    Acopia.pop_back();
    float pesoA = A.back().second-A.back().first + 1;
    for(int i = 0; i < B.size()-1; i++){
        float pesoB = Sumatoria(B,B.size()-i-1,B.size());
        Bcopia.pop_back();
        auto OPT = MinMatching(Acopia,Bcopia);
        if(peso2.second > OPT.second+pesoA/pesoB){
            peso2.second = OPT.second+pesoA/pesoB;
            peso2.first =  OPT.first;
            for(int j = B.size()-i; j < B.size();j++)
                peso2.first.push_back({A.size()-1,j-1});
        }
    }

    //--------------------------------------------------------//

    pair<vector<pair <int, int>>, float> X = Min(peso1,peso2);
    X.first.push_back({A.size()-1,B.size()-1});
    M[A.size()-1][B.size()-1] = X;

    return X;
}


int main( ) {
    vector<int> A = {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0};
    vector<int> B = {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0};
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

    M = new pair<vector<pair <int, int>>, float>* [DivisionesA.size()];
    for(int i = 0; i < DivisionesA.size(); i++) {
        M[i] = new pair<vector<pair <int, int>>, float>[DivisionesB.size()];  
    }

    for(int i = 0; i < DivisionesA.size(); i++){
        for(int j = 0; j < DivisionesB.size(); j++){
            M[i][j].second = -1; 
        }
    }

    //--------------------------------------------------------//

    auto X = MinMatching(DivisionesA,DivisionesB);
    for(auto i = X.first.begin(); i != X.first.end(); i++){
        cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }
    return 0;
}