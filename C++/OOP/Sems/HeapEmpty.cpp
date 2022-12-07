// Heap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>

using namespace std;

template <class T>
class Node
{
private:
	T value;

public:
	//установить данные в узле
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	//сравнение узлов
	int operator<(Node N)
	{
		return (value < N.getValue());
	}

	int operator>(Node N)
	{
		return (value > N.getValue());
	}

	//вывод содержимого одного узла
	void print()
	{
		cout << value;
	}
};

template <class T>
void print(Node<T> *N)
{
	cout << N->getValue() << "\n";
}

//куча (heap)
template <class T>
class Heap
{
protected:
	//массив
	Node<T> *arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;

	void SiftUp(int index = -1)
	{
		if (len == 0)
		{
			return;
		}
		if (index == -1)
		{
			index = len - 1;
		}
		int parent_index = GetParentIndex(index);
		if (parent_index < 0)
		{
			return;
		}
		//нужно сравнить элементы и при необходимости произвести просеивание вверх

		if (arr[index] > arr[parent_index])
		{
			Swap(parent_index, index);
			SiftUp(parent_index);
		}
		else
		{
			return;
		}
	}

	//восстановление свойств кучи после удаления или добавления элемента
	void Heapify(int index = 0)
	{
		//то же, что и SiftDown
		//нужно сравнить элементы и при необходимости произвести просеивание вниз
		if (int index < 0 || index >= len)
		{
			return;
		}

		int left = GetLeftChildIndex(index);
		int right = GetRightChildIndex(index);
		int max = -1;

		if (left >= len)
		{
			return;
		}
		if (right >= len)
		{
			max = left;
		}
		else
		{
			max = arr[left] > arr[right] ? left : right;
		}
		if (arr[max] > arr[index])
		{
			Swap(max, index);
			Heapify(max);
		}
		else
		{
			return;
		}
	}

public:
	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	/*
	Node<T>& operator[](int index)
	{
		if (index < 0 || index >= len)
			;//?

		return arr[index];
	}
	*/

	//конструктор
	Heap<T>(int MemorySize = 100)
	{
		arr = new Node<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}

	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 <= 0 || index1 >= len)
			;
		if (index2 <= 0 || index2 >= len)
			;
		//здесь нужна защита от дурака

		Node<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	//скопировать данные между двумя узлами
	void Copy(Node<T> *dest, Node<T> *source)
	{
		dest->setValue(source->getValue());
	}

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	Node<T> *GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return &arr[index * 2 + 1];
	}

	Node<T> *GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака

		return &arr[index * 2 + 2];
	}

	Node<T> *GetParent(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}

	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index << 1 >= len)
			;
		//здесь нужна защита от дурака
		return index * 2 + 1;
	}

	int GetRightChildIndex(int index)
	{
		if (index < 0 || index << 1 >= len)
			;
		//здесь нужна защита от дурака

		return index * 2 + 2;
	}

	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}

	//просеить элемент вверх

	//удобный интерфейс для пользователя
	template <class T>
	void push(T v)
	{
		Node<T> *N = new Node<T>;
		N->setValue(v);
		push(N);
	}

	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	template <class T>
	void push(Node<T> *N)
	{
		//добавить элемент и включить просеивание
		if (len < size)
		{
			arr[len] = *N;
			len++;
			SiftUp();
		}
	}

	Node<T> *ExtractMax()
	{
		if (len == 0)
		{
			return NULL;
		}

		Node<T> *res = new Node<T>(Copy(res, &arr[0]));

			Swap(0, len - 1);
		len--;
		Heapify();

		return res;
	}

	//перечислить элементы кучи и применить к ним функцию
	void Straight(void (*f)(Node<T> *))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}

	//перебор элементов, аналогичный проходам бинарного дерева
	void PreOrder(void (*f)(Node<T> *), int index = 0)
	{
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void InOrder(void (*f)(Node<T> *), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void PostOrder(void (*f)(Node<T> *), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
	}
};

int main()
{
	Heap<int> Tree;

	Tree.push(1);
	Tree.push(-1);
	Tree.push(-2);
	Tree.push(2);
	Tree.push(5);
	Tree.push(6);
	Tree.push(-3);
	Tree.push(-4);
	Tree.push(4);
	Tree.push(3);

	cout << "\n-----\nStraight:";
	void (*f_ptr)(Node<int> *);
	f_ptr = print;
	Tree.Straight(f_ptr);
	cout << "\n-----\nExtractMax:";
	int i = 0;
	while (i < Tree.getCount())
	{
		Node<int> *N = Tree.ExtractMax();
		N->print();
		delete N;
		cout << "\n";
	}

	char c;
	cin >> c;
	return 0;
}
