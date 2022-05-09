#include "DisMath.h"

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> edges(n * m);
    std::vector<bool> mark(n, false);
    std::vector<int> d(n);

    for (int i = 0; i < edges.size(); i++)
    {
        if (i < (n * m) - (m - 1))
        {
            edges[i].push_back(i - m);
        }
        if (i > m - 1)
        {
            edges[i].push_back(i + m);
        }
        if (i > 0)
        {
            edges[i].push_back(i + 1);
        }
        if (i < n * m)
        {
            edges[i].push_back(i - 1);
        }
    }

    for (int i = 0; i < n*m; i++)
    {
        char c;
        std::cin >> c;
        if (c == '.')
        {
            if (i < (n * m) - (m - 1))
        {
            edges[i-m].push_back(0);
        }
        if (i > m - 1)
        {
            edges[i+m].push_back(i + m);
        }
        if (i > 0)
        {
            edges[i].push_back(i + 1);
        }
        if (i < n * m)
        {
            edges[i].push_back(i - 1);
        }
        }
    }

    for (int i = 0; i < mark.size(); i++)
    {
        std::vector<bool> sub_mark = mark;
        int count_comp = 0;
        if (mark[i] == 0)
        {
            DFS(i, edges, mark);
            count_comp++;
        }
    }
    return 0;
}