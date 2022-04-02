#include "DisMath.h"

const int MOD = 1e9 + 7;
 
int main()
{
    int n, s;
    std::cin >> n >> s;

    std::vector <std::vector <int>> edges(n, std::vector <int>(n));
    std::vector <bool> mark(n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int x;
            std::cin >> x;
            edges[i].push_back(x);
        }
    }
    DFS(s, edges, mark);
    int count = 0;
    for(int i = 0; i < mark.size(); i++){
        if(mark[i])
            count++;
    }

    std::cout << count;
}