#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

void DFS(int start, std::vector<std::vector<int>> &edges, std::vector<bool> &mark)
{
    std::stack<int> s;
    s.push(start);
    mark[start] = 1;
    while (!s.empty())
    {
        int v = s.top();
        s.pop();
        for (int i = 0; i < edges[v].size(); ++i)
        {
            if (mark[edges[v][i]] == 0)
            {
                s.push(edges[v][i]);
                mark[edges[v][i]] = 1;
            }
        }
    }
}

void BFS(int start, std::vector<std::vector<int>> &edges, std::vector<bool> &mark, std::vector<int> &dist)
{
    std::queue<int> q;
    q.push(start);
    dist[start] = 0;
    mark[start] = 1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int i = 0; i < edges[v].size(); ++i)
        {
            if (mark[edges[v][i]] == 0)
            {
                dist[edges[v][i]] = dist[v] + 1;
                mark[edges[v][i]] = 1;
                q.push(edges[v][i]);
            }
        }
    }
}

void Dijkstra(int start, std::vector<std::vector<int>> &edges, std::vector<int> &dist)
{
    queue<int> q;
	q.push(start);
	dist[start] = 0;

	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();

		for (int i = 0; i < 7; i++)
		{
			//есть ребро vertex->i, в i не заходили
			if (edges[vertex][i] > 0 &&
				dist[vertex] + edges[vertex][i] < dist[i])
			{
				dist[i] = dist[vertex] + edges[vertex][i];
				q.push(i);
			}
		}

}


int main()
{

	vector<vector<int> > mat =
	{
	{ 0, 1, 1, 0, 0, 0, 1 }, // матрица смежности
	{ 1, 0, 1, 1, 0, 0, 0 },
	{ 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0 }
	};

	vector <int> used(7, 0);
	vector <int> dist(7, __DBL_HAS_INFINITY__;


	return 0;
}
