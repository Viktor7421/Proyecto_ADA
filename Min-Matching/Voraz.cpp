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

// pair<pair<vector<pair <int, int>>, pair <int, int>>, float>
pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> MinMatching(vector<int> A, vector<int> B){
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

    float peso = 0;
    vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>> X;
    //vector<pair <int, int>> X;
    vector<pair <int, int>> tempA;
    vector<pair <int, int>> tempB;

    while (DivisionesA.size() > DivisionesB.size())
    {

        pair <int, int> Ai = DivisionesA.back();
        tempA.push_back(Ai);
        DivisionesA.pop_back();
        peso += (Ai.second-Ai.first+1);
        
        if(DivisionesA.size() == DivisionesB.size()){

            pair <int, int> Ai = DivisionesA.back(); 
            tempA.push_back(Ai);
            DivisionesA.pop_back();
            pair <int, int> Bi = DivisionesB.back();
            tempB.push_back(Bi); 
            DivisionesB.pop_back();
            peso = float(peso + (Ai.second-Ai.first+1))/float(Bi.second-Bi.first+1);
            X.push_back({tempA,tempB});

        }
    }

    tempA.clear();
    tempB.clear();
    
    while (DivisionesA.size() < DivisionesB.size())
    {

        pair <int, int> Bi = DivisionesB.back(); 
        tempB.push_back(Bi);
        DivisionesB.pop_back();
        peso += (Bi.second-Bi.first+1);
        
        if(DivisionesA.size() == DivisionesB.size()){
            pair <int, int> Ai = DivisionesA.back(); 
            tempA.push_back(Ai);
            DivisionesA.pop_back();
            pair <int, int> Bi = DivisionesB.back(); 
            tempB.push_back(Bi);
            DivisionesB.pop_back();
            peso = float(Ai.second-Ai.first+1)/float(peso+(Bi.second-Bi.first+1));
            X.push_back({tempA,tempB});
        }
    }

    while(!DivisionesA.empty() || !DivisionesB.empty())
    {
        vector<pair <int, int>> tempA;
        vector<pair <int, int>> tempB;

        pair <int, int> Ai = DivisionesA.back(); 
        tempA.push_back(Ai);
        DivisionesA.pop_back();
        pair <int, int> Bi = DivisionesB.back(); 
        tempB.push_back(Bi);
        DivisionesB.pop_back();
        peso += float(Ai.second-Ai.first+1)/float(Bi.second-Bi.first+1);
        X.push_back({tempA,tempB});
    }

    DivisionesA.clear();
    DivisionesB.clear();

    return {X,peso};
}

/*int main( ) {
    vector<int> A = {1,0,1,1,1,0,1,1,0,1};
    vector<int> B = {0,0,1,1,0,0,1,1,0,0};
    auto X = MinMatching(A,B);
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