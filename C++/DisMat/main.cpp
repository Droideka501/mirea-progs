//#include <iostream>
#include "DisMath.h"
#include <cmath>
#include <vector>
#include <set>

const int MOD = 1e9 + 7;
 
int main()
{
    int n, n1, n2;
    std::cin >> n >> n1 >> n2;

    std::vector <int> tree(n+1);
    tree[1] = 0;
    for(int i = 2; i < n+1; i++){
        std::cin >> tree[i];
    }

    std::set<int> checker;

    checker.insert(n1);
    while(tree[n1]){
        checker.insert(tree[n1]);
        n1 = tree[n1];
    }
    
    if(checker.count(n2)){
        std::cout << n2;
        return 0;
    }
    
    while(tree[n2]){
        int t = tree[n2];
        if(checker.count(t)){
            std::cout << tree[n2];
            return 0;
        }
        n2 = tree[n2];
    }
}