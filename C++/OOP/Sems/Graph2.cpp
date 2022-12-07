// TestGraph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class Edge
{
public:
	int from, to, weight;
	Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
	Edge(const Edge &E)
	{
		from = E.from;
		to = E.to;
		weight = E.weight;
	}
	int operator<(Edge &E)
	{
		return (weight < E.weight);
	}
	friend ostream &operator<<(ostream &s, Edge &e);
};

ostream &operator<<(ostream &s, Edge &e)
{
	s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
	return s;
}

int main()
{

	vector<vector<int>> mat =
		{
			{0, 3, 1, 3, 0, 0, 0},
			{3, 0, 0, 3, 0, 0, 0},
			{1, 0, 0, 1, 0, 0, 0},
			{3, 3, 1, 0, 1, 0, 0},
			{0, 0, 0, 1, 0, 1, 2},
			{0, 0, 0, 0, 1, 0, 3},
			{0, 0, 0, 0, 2, 3, 0}};

	// used[i] = 0 вершина еще не появлялась при обработке
	vector<int> dist(7, -1);
	vector<int> used(7, 0);

	// BFS
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	int step = 0;

	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();

		for (int i = 0; i < 7; i++)
		{
			//есть ребро vertex->i, в i не заходили
			if (mat[vertex][i] > 0 &&
				dist[vertex] + mat[vertex][i] < dist[i])
			{
				dist[i] = dist[vertex] + mat[vertex][i];
				q.push(i);
			}
		}

		//обработка вершины закончена
		// if (dist[vertex] < 0) dist[vertex] = step;
		step++;
	}

	std::vector<std::vector<int>> mat1 =
		{
			{0, 1, 2, 3, 4, 5, 0},
			{1, 0, 0, 0, 0, 2, 0},
			{2, 0, 0, 0, 0, 0, 0},
			{3, 0, 0, 0, 3, 0, 0},
			{4, 0, 0, 3, 0, 0, 0},
			{5, 2, 0, 0, 0, 0, 5},
			{0, 0, 0, 0, 0, 5, 0}};
	int mst_weight = 0;

	std::cout << "\nMinimum spanning tree weight: " << mst_weight << endl;

	mst_weight = 0; //Текущий вес остова.

	vector<Edge> edges;		 //рассматриваемые ребра
	vector<Edge> tree_edges; //ребра в минимальном остове

	edges.push_back(Edge(0, 0, 0)); //Начнём с вершины 0.

	while (!edges.empty())
	{
		auto min = min_element(edges.begin(), edges.end());
		int to = min->to;
		int from = min->from;
		int w = min->weight;
		mst_weight += w;
		edges.erase(min);

		if (used[to])
			continue;
		used[to] = 1;

		tree_edges.push_back(Edge(from, to, w));

		for (int i = 0; i < mat1[0].size(); i++)
		{
			if (mat1[to][i] > 0 && !used[i])
			{
				edges.push_back(Edge(to, i, mat1[to][i]))
			}
		}
	}

	std::cout << "\nMinimum spanning tree weight: " << mst_weight << endl;
	for (int i = 1; i < tree_edges.size(); i++)
	{
		cout << "\nEdge " << i << " ";
		cout << tree_edges[i];
	}

	char c;
	cin >> c;
	return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
