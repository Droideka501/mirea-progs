﻿// TestGraph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

bool HamiltonPath(vector<vector<int>> &mat, vector<bool> &visited, vector<int> &path, int curr)
{
	path.push_back(curr);
	//путь содержит все вершины: если есть связь последней вершины с исходной, цикл найден
	//если нет, откатываемся на шаг назад

	if (path.size() == mat.size())
	{
		return true;
	}

	//вершина использована в пути
	visited[curr] = true;
	//проверить всех непосещенных соседей вершины curr

	for (int i = 0; i < mat.size(); i++)
	{
		if (mat[curr][i] > 0 && !visited[i])
		{
			if (HamiltonPath(mat, visited, path, i))
				return true;
		}
	}

	//этот путь не подходит, убираем вершину и откатываемся
	visited[curr] = false;
	path.pop_back();
	return false;
}

bool HamiltonCircle(vector<vector<int>> &mat, vector<bool> &visited, vector<int> &path, int curr)
{
	path.push_back(curr);
	//путь содержит все вершины: если есть связь последней вершины с исходной, цикл найден
	//если нет, откатываемся на шаг назад

	if (path.size() == mat.size())
	{
		if (mat[path[0]][path[path.size() - 1]] > 0;)
		{
			return true;
		}
		path.pop_back();
		return false;
	}

	//вершина использована в пути
	visited[curr] = true;
	//проверить всех непосещенных соседей вершины curr

	for (int i = 0; i < mat.size(); i++)
	{
		if (mat[curr][i] > 0 && !visited[i])
		{
			if (HamiltonCircle(mat, visited, path, i))
			{
				return true;
			}
		}
	}

	//этот путь не подходит, убираем вершину и откатываемся
	visited[curr] = false;
	path.pop_back();
	return false;
}

int main()
{

	vector<vector<int>> mat =
		{
			{0, 1, 0, 0, 0, 0},
			{1, 0, 1, 0, 0, 0},
			{0, 1, 0, 1, 1, 0},
			{0, 0, 1, 0, 1, 0},
			{0, 0, 1, 1, 0, 1},
			{0, 0, 0, 0, 1, 0}};
	vector<bool> visited(6, 0);
	vector<int> path;

	cout << "\nHamilton: " << HamiltonPath(mat, visited, path, 0);

	char c1;
	cin >> c1;

	char c;
	std::cin >> c;
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