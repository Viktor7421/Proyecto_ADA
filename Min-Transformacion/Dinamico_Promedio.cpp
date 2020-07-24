#include "iostream"
#include <utility> 
#include <vector> 
#include "../Min-Matching/Dinamico_Promedio.cpp"
using namespace std;


pair<vector<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>>, float> PromMinTransformacion(vector<vector<int>> A, vector<vector<int>> B)
{
    vector<vector<pair<vector<pair <int, int>>, vector<pair <int, int>>>>> matchings;
    float peso = 0;
    if(A.size() == B.size())
    {
        for (int i = 0; i < A.size(); i++)
        {
            auto matching = PromMinMatching(A[i],B[i]);
            matchings.push_back(matching.first);
            peso += matching.second;
            matching.first.clear();
        }
    } 
    else
    {
        cout << "ERROR_A.size() == B.size()";
    }

    return {matchings, peso};
}

/*
int main() {
    vector<vector<int>> A = {{1,1,1,0,1,0,1,1,0,1},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
    vector<vector<int>> B = {{0,0,0,0,0,0,0,0,0,0},{0,0,1,1,0,0,1,1,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
    auto X = MinTransformacion(A,B);
    for(auto k = X.first.begin(); k != X.first.end(); k++){
        for(auto i = (*k).begin(); i != (*k).end(); i++){
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
        }
        cout << "---------\n";
    }
    cout << X.second << "\n";
    return 0;
}
*/