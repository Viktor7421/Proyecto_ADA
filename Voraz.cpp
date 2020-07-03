#include "iostream"
#include <utility> 
#include <vector> 
using namespace std;

pair<vector<pair <int, int>>, float> MinMatching(vector<int> A, vector<int> B, int p){
    vector<pair<int,int>> DivisionesA;
    vector<pair<int,int>> DivisionesB;
    
    for (int i = 0; i < p; i++){
        if(A[i] == 1){
            int start = i;
            while ( A[i+1] == 1 ){ i++;}
            DivisionesA.push_back({start,i});
        }
    }

    for (int i = 0; i < p; i++){
        if(B[i] == 1){
            int start = i;
            while ( B[i+1] == 1 ){ i++;}
            DivisionesB.push_back({start,i});
        }
    }

    float peso = 0;
    vector<pair <int, int>> X;

    while (DivisionesA.size() > DivisionesB.size())
    {
        X.push_back({DivisionesA.size()-1,DivisionesB.size()-1});
        
        pair <int, int> Ai = DivisionesA.back(); 
        DivisionesA.pop_back();
        peso += (Ai.second-Ai.first+1);
        
        if(DivisionesA.size() == DivisionesB.size()){
            X.push_back({DivisionesA.size()-1,DivisionesB.size()-1});

            pair <int, int> Ai = DivisionesA.back(); 
            DivisionesA.pop_back();
            pair <int, int> Bi = DivisionesB.back(); 
            DivisionesB.pop_back();
            peso = float(peso + (Ai.second-Ai.first+1))/float(Bi.second-Bi.first+1);
        }
        cout << peso << "\n";
    }
    
    while (DivisionesA.size() < DivisionesB.size())
    {
        X.push_back({DivisionesA.size()-1,DivisionesB.size()-1});

        pair <int, int> Bi = DivisionesB.back(); 
        DivisionesB.pop_back();
        peso += (Bi.second-Bi.first+1);
        
        if(DivisionesA.size() == DivisionesB.size()){
            pair <int, int> Ai = DivisionesA.back(); 
            DivisionesA.pop_back();
            pair <int, int> Bi = DivisionesB.back(); 
            DivisionesB.pop_back();
            peso = float(Ai.second-Ai.first+1)/float(peso+(Bi.second-Bi.first+1));
        }
        cout << peso << "\n";
    }

    while(!DivisionesA.empty())
    {
        X.push_back({DivisionesA.size()-1,DivisionesB.size()-1});

        pair <int, int> Ai = DivisionesA.back(); 
        DivisionesA.pop_back();
        pair <int, int> Bi = DivisionesB.back(); 
        DivisionesB.pop_back();
        peso += float(Ai.second-Ai.first+1)/float(Bi.second-Bi.first+1);
        cout << peso << "\n";
    }

    return {X,peso};
}


int main( ) {
    vector<int> A = {1,1,1,0,1,0,1,1,0,1,1,0,1,1,1};
    vector<int> B = {0,0,0,0,0,0,1,1,0,0,0,0,1,1,0};
    auto X = MinMatching(A,B,A.size());
    for(auto i = X.first.begin(); i != X.first.end(); i++){
        cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }
    cout << X.second << "\n";
    return 0;
}