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

    if(DivisionesA.size() == 1 && DivisionesB.size() == 1){
        float pesoA = (DivisionesA[0].second-DivisionesA[0].first+1);
        float pesoB = (DivisionesB[0].second-DivisionesB[0].first+1);
        float peso = pesoA/pesoB;

        vector<pair <int, int>> X;
        X.push_back({0,0});

        M[DivisionesA.size()-1][DivisionesB.size()-1] = {X,peso};

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
        
        M[DivisionesA.size()-1][DivisionesB.size()-1] = {X,peso};

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

        M[DivisionesA.size()-1][DivisionesB.size()-1] = {X,peso};

        return {X,peso};
    }

    //-------------------------------------------------------//

    vector<pair <int, int>> Acopia;
    vector<pair <int, int>> Bcopia;

    vector<pair <int, int>> X1;
    pair<vector<pair <int, int>>, float> X2;

    for (int i = 0; i < DivisionesA.size()-1; i++)
    {
        float pesoA = Sumatoria(DivisionesA, 0, i+1);
        float pesoB = (DivisionesB[0].second-DivisionesB[0].first+1);
        float peso = pesoA/pesoB;
        X1.push_back({i,0});

        M[i][0] = {X1,peso};
    }
    
    X1.clear();

    for (int i = 0; i < DivisionesB.size()-1; i++)
    {
        float pesoB = Sumatoria(DivisionesB, 0, i+1);
        float pesoA = (DivisionesA[0].second-DivisionesA[0].first+1);
        float peso = pesoA/pesoB;
        X1.push_back({0,i});

        M[0][i] = {X1,peso};
    }

    for (int i = 1; i < DivisionesA.size(); i++)
    {
        for (int j = 1; j < DivisionesB.size(); j++)
        {
            vector<pair <int, int>> Acopia;
            vector<pair <int, int>> Bcopia;

            //--------------------------------------------------------//

            pair<vector<pair <int, int>>, float> peso1;

            Acopia = DivisionesA;
            Bcopia = DivisionesB;

            peso1.second = FLT_MAX; 
            
            int index_1;

            float pesoB = Sumatoria(DivisionesB, j, j+1);
            for(int l = 0; l < i; l++){
                float pesoA = Sumatoria(DivisionesA,i-l,i+1);
                auto OPT = M[i-l-1][j-1];
                if(peso1.second > OPT.second+pesoA/pesoB){
                    peso1.second = OPT.second+pesoA/pesoB;
                    peso1.first =  OPT.first;
                    index_1 = l;
                }
            }

            for(int k = i-index_1; k < i;k++)
                peso1.first.push_back({k,j});

            //--------------------------------------------------------//

            pair<vector<pair <int, int>>, float> peso2;

            Acopia = DivisionesA;
            Bcopia = DivisionesB;

            peso2.second = FLT_MAX; 
            
            int index_2;

            float pesoA = Sumatoria(DivisionesA,i,i+1);
            for(int l = 0; l < j; l++){
                float pesoB = Sumatoria(DivisionesB,j-l,j+1);
                auto OPT = M[i-1][j-l-1];
                if(peso2.second > OPT.second+pesoA/pesoB){
                    peso2.second = OPT.second+pesoA/pesoB;
                    peso2.first =  OPT.first;
                    index_2 = l;
                }
            }

            for(int k = j-index_2; k < j;k++)
                peso2.first.push_back({i,k});
            //--------------------------------------------------------//

            X2 = Min(peso1,peso2);
            X2.first.push_back({i,j});
            M[i][j] = X2;
        }
    }

    
    return M[DivisionesA.size()-1][DivisionesB.size()-1];
}


int main( ) {
    vector<int> A = {0,0,0,0,0,0,1,1,0,1,1,0,1,1,1};
    vector<int> B = {1,0,1,1,0,0,1,1,0,0,0,0,1,1,0};
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

    auto X = MinMatching(A,B);
    for(auto i = X.first.begin(); i != X.first.end(); i++){
        cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }
    cout << X.second << "\n";
    return 0;
}