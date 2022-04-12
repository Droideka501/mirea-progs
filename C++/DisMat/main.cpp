#include "DisMath.h"
 
int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector <std::vector <int>> edges(n);
    std::vector <bool> mark(n, false);
    std::vector <int> d(n);

    for(int i = 0; i < m; i++){
        int a, b;
        std::cin >> a >> b;
        edges[a-1].push_back(b-1);
    }
    
    if(m >= n){
        std::cout << "NO";
        return 0;
    }
    
    /*
    int count_comp = 0;
    {
        std::vector <bool> sub_mark = mark;
        for(int i = 0; i < sub_mark.size(); i++){
            if(sub_mark[i] == 0){
                DFS(i, edges, sub_mark);
                count_comp++;
            }

        }
    }
    std::cout << count_comp << std::endl;
    */


    for(int i = 0; i < mark.size(); i++){
        std::vector <bool> sub_mark = mark;
        int count_edges = 0, count_nodes = 0;
        if(mark[i] == 0){
            DFS(i, edges, mark);
            for(int j = i; j < mark.size(); j++){
                if(mark[j] != sub_mark[j])
                    count_edges += edges[j].size();
                    count_nodes++;
            }
        }
        if(count_edges >= count_nodes && count_nodes != 0){
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}


/*----------------------------------------------------------------
for(int i = 0; i < edges.size(); i++){
        for(int j = 0; j <edges[i].size(); j++){
            std::cout << edges[i][j] << " ";
        }
        std::cout << std::endl;
    }
*/