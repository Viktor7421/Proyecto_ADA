#include "iostream"
#include <utility> 
#include <vector> 
using namespace std;

vector<pair <int, int>> MinMatching(vector<int> A, vector<int> B, int p){
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

    vector<pair <int, int>> X;
    X.push_back({0,0});

    for(int i = 1, j = 1; i <= DivisionesA.size();){
        if (i == DivisionesA.size() && j < DivisionesB.size()){
            X.push_back({i-1,j});
            j++;
        } else if (i < DivisionesA.size()) {
            int P_A = DivisionesA[i].second-DivisionesA[i].first + 1;
            int P_B1 = DivisionesB[j-1].second-DivisionesB[j-1].first + 1;
            int P_B2 = DivisionesB[j].second-DivisionesB[j].first + 1;
            if(P_A/P_B1 < P_A/P_B2){
                X.push_back({i,j-1});
            } else {
                X.push_back({i,j});
                j++;
            }
            i++;
        } else {
            i++;
        }
    }

    return X;
}


int main( ) {
    vector<int> A = {0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0};
    vector<int> B = {0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0};
    auto X = MinMatching(A,B,20);
    for(auto i = X.begin(); i != X.end(); i++){
        cout << '(' << (*i).first << ',' << (*i).second << ")\n";
    }
    return 0;
}