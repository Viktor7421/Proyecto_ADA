#include "iostream"
#include <utility> 
#include <vector> 
using namespace std;

// pair<pair<vector<pair <int, int>>, pair <int, int>>, float>
pair<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>, float> MinMatching(vector<int> A, vector<int> B, int p){
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
    vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>> X;
    //vector<pair <int, int>> X;
    vector<pair <int, int>> tempA;
    vector<pair <int, int>> tempB;

    while (DivisionesA.size() > DivisionesB.size())
    {
        //X.push_back({DivisionesA.size()-1,DivisionesB.size()-1});

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
        //X.push_back({DivisionesA.size()-1,DivisionesB.size()-1});

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

    while(!DivisionesA.empty())
    {
        //X.push_back({DivisionesA.size()-1,DivisionesB.size()-1});
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

    return {X,peso};
}

/*int main( ) {
    vector<int> A = {1,0,1,1,1,0,1,1,0,1};
    vector<int> B = {0,0,1,1,0,0,1,1,0,0};
    auto X = MinMatching(A,B,A.size());
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