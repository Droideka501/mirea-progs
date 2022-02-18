#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector <std::vector <int>> roads(n, std::vector<int>(n)); 

    int min_costs_counter = 10000;
 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cin >> roads[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        roads[i][i] = 10000;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 1; k < n; k++){
                int temp = roads[i][j] + roads[(i+k)%n][j] + roads[(i+k)%n][i];
                if (temp < min_costs_counter) min_costs_counter = temp;
            }
        }
    }

    std::cout << min_costs_counter;
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