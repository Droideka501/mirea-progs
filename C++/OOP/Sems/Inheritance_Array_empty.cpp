// Inhearitance_Array.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

class MyArrayParent
{
protected:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;
public:
	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100)
	{
		cout << "\nMyArrayParent constructor";
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor";
		capacity = (len >= 1000) ? len << 1 : 1000;
		count = len;
		ptr = new double[capacity];
		for(int i = 0; i < len; i++){
			ptr[i] = arr[i];
		}
	}

	MyArrayParent(const MyArrayParent& A)
	{
		cout << "\nCopy constructor";
		capacity = A.capacity;
		count = A.count;
		ptr = new double[capacity];
		for(int i = 0; i < count; i++){
			ptr[i] = A.ptr[i];
		}
	}

	//деструктор
	~MyArrayParent()
	{
		cout << "\nMyArrayParent destructor";
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}

	//обращение к полям
	int Capacity() { return capacity; }
	int Size() { return count; }
	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		//сгенерировать исключение, если индекс неправильный
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		//сгенерировать исключение, если индекс неправильный
	}

	//добавление в конец нового значения
	void push(double value)
	{
		if(count < capacity){
			ptr[count++] = value;
		}else{
			double* res = new double[capacity*2];
			for(int i = 0; i < count; i++){
				res[i] = ptr[i];
			}
			res[count+1] = value;
			delete[] ptr;
			ptr = res; 
		}
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count >= 0){
			ptr[--count] = 0;
		}
		//что делаем, если пуст?
	}

	double& operator[](int index)
	{
		//перегрузка оператора []
	}

	/*MyArrayParent& operator=(const Vector& V)
	{
		//оператор =
		//arr1 = arr2 = arr3; где arr_i - объекты нашего класса
	}

	MyArrayParent(const Vector& V)
	{
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
	}*/

	MyArrayParent operator=(const MyArrayParent& A)
	{
		if(capacity == A.capacity)
		{
			count = A.count;
			for(int i = 0; i < count; i++)
				ptr[i] = A.ptr[i];
		}
		return *this;
	}

	void print()
	{
		cout << "\nMyArrParent, size: " << count<<", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}



};

class MyArrayChild : public MyArrayParent
{
public:
	//используем конструктор родителя. Нужно ли что-то ещё?
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }
	MyArrayChild(double* arr, int len) : MyArrayParent(arr, len) {}
	

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n";  }


	int IndexOf(double value, bool bFindFromStart = true)
	{
		if (bFindFromStart)
		{
			for(int i = 0; i < count; i++)
				if(ptr[i] == value)
					return i;
			
			return -1;
		}else{
			for(int i = count; i > 0; i--)
				if(ptr[i] == value)
					return i;
			return -1;
		}
	}


	void InsertAt(double value, int index = -1)
	{
		if(index == -1 || index > capacity)
		{
			push(value);
			return;
		}
		if(count < capacity)
		{
			for(int i = count; i > index; i--){
				ptr[i] = ptr[i - 1];
			}
			ptr[index] = value;
			count++;
			
		}
	}

	//удаление элемента
	//void RemoveAt(int index = -1);

	//поиск элемента
	//void IndexOf(double value, bool bFindFromStart = true);

	//вставка элемента
	//void InsertAt(double value, int index = -1);

	//выделение подпоследовательности
	//MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)

	//добавление элемента в конец
	//operator + ?

};

void swapInArray(double* arr, int indexLeft, int indexRight)
{
	double temp = arr[indexLeft];
	arr[indexLeft] = arr[indexRight];
	arr[indexRight] = temp;
}

int main()
{
	//MyArrayParent arr;
	if (true)
	{
		MyArrayChild arr;
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			arr.push(i + 1);
		}
		arr.print();
		cout << "\n";
		//cout << "\n" << sp << "\n";
	}
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
