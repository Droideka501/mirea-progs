#include <iostream>
#include <vector>

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector <std::vector <int>> roads(n, std::vector<int>(m)); 

    int min_costs_counter = 10000;
 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            roads[i][j] == 0;
        }
    }


    int t;
    std::cin >> t;
    for(int i = 0; i < t; i++)
    {
        int x, y;
        std::cin >> x >> y;
        roads[x][y] = 1;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            std::cout << roads[i][j] << " ";
        }
        std::cout << "\n";
    }

    
}


 /*
    for(int i = 0; i < n; i++){
        int min_1 = 1000;
        int iter1 = 0;
        for(int j = 0; j < n; j++){
            if (roads[i][j] < min_1 && roads[i][j] != 0){
                min_1 = roads[i][j];
                iter1 = j;
            }
        }
        int min_2 = 1000;
        int iter2 = 0;
        for(int j = 0; j < n; j++){
            if (roads[j][iter1] < min_2 && roads[j][iter1] != 0 && roads[j][iter1] != min_1){
                min_2 = roads[j][iter1];
                iter2 = j;
            }
        }
        int temp = min_1 + min_2 + roads[i][iter2];
        if (temp < min_costs_counter) min_costs_counter = temp;
    }*/