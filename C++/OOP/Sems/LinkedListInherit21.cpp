// LinkedListInherit21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
using namespace std;

#include <iostream>

template<class T>
class Element
{
	//protected:
public:
	//переместить в protected
	Element* next;
	Element* prev;
	T info;

	Element(T data)
	{
		next = prev = NULL;
		info = data;
	}

	Element(Element* Next, Element* Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}

	Element(const Element& el)
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, Element<T1>& el);

};

template<class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << el.info;
	return s;
}

template<class T>
class LinkedList
{
	//protected:
public:
	//переместить в protected
	Element<T>* head;
	Element<T>* tail;
	int count;

	LinkedList()
	{
		head = tail = NULL;
		count = 0;
	}

	//удалить первый/последний элемент и вернуть удаленное значение
	virtual Element<T>* pop() = 0;
	//добавить элемент в список
	virtual Element<T>* push(T value) = 0;
	//получить первый/последний элемент списка
	//virtual Element<T>* front(T value) = 0;
	//virtual Element<T>* back(T value) = 0;

	//доступ по индексу
	//virtual Element<T>& operator[](int index) = 0;

	template<class T1>
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);

	//доработать деструктор
	virtual ~LinkedList() 
	{ 
		
	}
};

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
