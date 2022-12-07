// MaxFlow.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INFINITY 10000 // условное число, обозначающее бесконечность

void FillVectorWith(vector<int>& v, int value, int size = 0)
{
	if (size != 0)
	{
		v.resize(0);
		for (int i = 0; i < size; i++)
			v.push_back(value);
	}
	for (int i = 0; i < v.size(); i++)
		v[i] = value;
}

void FillMatrixWith(vector<vector<int> >& matrix, int value, int width = 0, int height = 0)
{
	if (width != 0 && height != 0)
	{
		matrix.resize(0);
		int i, j;
		for (i = 0; i < height; i++)
		{
			vector<int> v1;
			for (j = 0; j < width; j++)
			{
				v1.push_back(value);
			}
			matrix.push_back(v1);
		}
	}
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			matrix[i][j] = value;
	}
}

int FindPath(vector<vector<int> >& f, vector<vector<int> >& c, int source, int target, int vertices) // source - исток, target - сток
{
	int i;
	int CurVertex;
	// Flow - значение потока через данную вершину на данном шаге поиска
	// Link[i] хранит номер предыдущей вешины на пути i -> исток
	vector<int> Flow; FillVectorWith(Flow, 0, vertices);
	vector<int> Link; FillVectorWith(Link, -1, vertices);
	Flow[source] = INFINITY;
	while (??)
	{
		
	}

	if (Link[target] == -1) return 0;
	CurVertex = target;
	while (CurVertex != source)
	{
		f[Link[CurVertex]][CurVertex] += Flow[target];
		CurVertex = Link[CurVertex];
	}
	return Flow[target];
}

// основная функция поиска максимального потока
int MaxFlow(vector<vector<int> >& f, vector<vector<int> >& c, int source, int target, int vertices) // source - исток, target - сток
{
	FillMatrixWith(f, 0);
	int MaxFlow = 0;
	int AddFlow;
	do
	{
		AddFlow = FindPath(f, c, source, target, vertices);
		MaxFlow += AddFlow;
	} while (AddFlow > 0);
	return MaxFlow;
}

int main()
{
	int source = 0; //откуда?
	int target = 5; //куда?
	int vertices = 6; // число вершин в графе

	vector<vector<int> > c =
	{
	{	0, 16, 0, 0, 13, 0 },
	{	0, 0, 12, 0, 6, 0 },
	{	0, 0, 0, 0, 9, 20 },
	{	0, 0, 7, 0, 0, 4 },
	{	0, 0, 0, 14, 0, 0 },
	{	0, 0, 0, 0, 0, 0 },
	};
	vector<vector<int> > f;
	// f[i][j] - поток, текущий от вершины i к j
	// c[i][j] - максимальная величина потока, способная течь по ребру (i,j)
	FillMatrixWith(f, 0, vertices, vertices);

	// набор вспомогательных переменных, используемых функцией FindPath - обхода в ширину

	// поиск пути, по которому возможно пустить поток алгоритмом обхода графа в ширину
	// функция ищет путь из истока в сток, по которому еще можно пустить поток,
	// считая вместимость ребера (i,j) равной c[i][j] - f[i][j]



	cout<<"\nResult: "<<MaxFlow(f, c, source, target, vertices);
	char c1; cin >> c1;
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
