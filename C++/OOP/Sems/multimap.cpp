#include <iostream>
#include <fstream>

using namespace std;

#include <map>

class test_class
{
public:
	int k, v;
	test_class(int K, int V) { k = K; v = V; }
	int operator<(test_class& t)
	{
		cout << "\nOperator< is working";
		if (k < t.k) return true;
		if (k > t.k) return false;
		return v < t.v;
	}

	friend ostream& operator<<(ostream& s, test_class& t)
	{
		s << t.k << ": " << t.v;
		return s;
	}
};

int main()
{
	multimap<string, int> marks2;
	marks2.insert(marks2.begin(), { "Petrov", 5 });
	marks2.insert(marks2.begin(), { "Petrov", 4 });
	marks2.insert(marks2.begin(), { "Ivanov", 4 });
	marks2.insert(marks2.begin(), { "Ivanov", 3 });
	marks2.insert(marks2.begin(), { "Nikolaev", 3 });
	marks2.insert(marks2.begin(), { "Nikolaev", 5 });
	marks2.insert(marks2.begin(), { "Kuznetsov", 5 });
	marks2.insert(marks2.begin(), { "Kuznetsov",  4 });

	cout << "\nMultimap:\n";
	//итератор пробегает по map
	multimap<string, int>::iterator it_m2 = marks2.begin();
	while (it_m2 != marks2.end())
	{
		//перемещение по списку с помощью итератора, нет операции [i]
		cout << "Key: " << it_m2->first << ", value: " << it_m2->second << "\n";
		it_m2++;
	}

	//поиск по multimap
	it_m2 = marks2.find("Ivanov");
	cout << "\nMultimap Find:\n"<< "Key: " << it_m2->first << ", value: " << it_m2->second << "\n";
	it_m2++; cout << "Key: " << it_m2->first << ", value: " << it_m2->second << "\n";

	cout << "\n-----\n";
	multimap<int, test_class> test;
	test.insert(test.begin(), { 5, test_class(5, 25) });
	test.insert(test.begin(), { 5, test_class(5, 125) });
	test.insert(test.begin(), { 4, test_class(4, 16) });
	test.insert(test.begin(), { 4, test_class(4, 64) });
	test.insert(test.begin(), { 3, test_class(3, 9) });
	test.insert(test.begin(), { 3, test_class(3, 27) });
	test.insert(test.begin(), { 2, test_class(2, 4) });
	test.insert(test.begin(), { 2, test_class(2, 8) });
	cout << "\nMultimap test_class:\n";
	//итератор пробегает по map
	multimap<int, test_class>::iterator it_m3 = test.begin();
	while (it_m3 != test.end())
	{
		//перемещение по списку с помощью итератора, нет операции [i]
		cout << "Key: " << it_m3->first << ", value: " << it_m3->second << "\n";
		it_m3++;
	}
}


