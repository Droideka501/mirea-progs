#include <cmath>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <set>
    
void vectorMatrixPrint(const std::vector<std::vector <int>>& v)
{
    for(int i = 0; i < v.size(); i++){
        if(v[i].size() == 0){
            std::cout << "empty" << std::endl;
        }else{
            for(int j = 0; j < v[i].size(); j++){
                std::cout << v[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

void vectorIntPrint(const std::vector<int>& v)
{
    for(int i = 0; i < v.size(); i++){
            std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void vectorBoolPrint(const std::vector<bool>& v)
{
    for(int i = 0; i < v.size(); i++){
            std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}