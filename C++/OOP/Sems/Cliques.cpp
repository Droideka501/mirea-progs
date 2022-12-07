// Cliques.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> difference(vector<int> s1, vector<int> s2)
{
	vector<int> res;
	set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(res));
	return res;
}

vector<int> setunion(vector<int> s1, vector<int> s2)
{
	vector<int> res;
	auto it = s1.begin();
	while (it != s1.end())
		res.push_back(*it++);
	it = s2.begin();
	while (it != s2.end())
		res.push_back(*it++);
	return res;
}

vector<int> intersection(vector<int> s1, vector<int> s2)
{
	vector<int> res;
	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(res));
	return res;
}

void print_vector(vector<int> V)
{
	if (V.size() == 0)
	{
		cout << "empty;";
		return;
	}
	for (int i = 0; i < V.size()-1; i++)
		cout << V[i] << ", ";
	cout << V[V.size() - 1] << ";";
}

void bronKerbosch(vector<vector<int>>& matrix, vector<int> R, vector<int> P, vector<int> X, int depth = 0) 
{
	cout << "\nCall "<<depth<<" R: "; print_vector(R);  cout << " P: ";  print_vector(P); cout << " X: "; print_vector(X);
	if (P.empty() && X.empty())
	{
		cout << "\nClique found: ";
		auto it = R.begin();
		while (it != R.end())
			cout << *it++ << " ";
	}
	auto v = P.begin();
	while (!P.empty() && v != P.end()) 
	{
		vector<int> singleton = { (*v) };
		vector<int> friends;

		for(int i = 0; i < matrix.size();i++)
		{
			if(matrix[*v][i] > 0)
			{
				friends.push_back(i);
			}
		}

		vector<int> R1 = setunion(R, singleton);
		vector<int> P1 = intersection(P, friends);
		vector<int> X1 = intersection(X, friends);

		bronKerbosch(matrix, R1, P1, X1, depth+1);

		P = difference(P, singleton);
		X = setunion(X, singleton);
		
		if (!P.empty())
			v = P.begin();
	}
}

int main()
{
	vector<vector<int>> matrix = 
	{
		{0, 1, 1, 0, 0, 0},
		{1, 0, 1, 1, 0, 0 },
		{1, 1, 0, 0, 0, 0 },
		{0, 1, 0, 0, 1, 1 },
		{0, 0, 0, 1, 0, 1 },
		{0, 0, 0, 1, 1, 0 }
	};
	vector<int> P;
	for (int i = 0; i < 6; i++)
		P.push_back(i);
	vector<int> R; vector<int> X;
	bronKerbosch(matrix, R, P, X);
	char c; cin >> c;
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
