// Inhearitance_Array.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>

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
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	MyArrayParent(double* arr, int len)
	{
		capacity = (len >= 1000) ? len << 1 : 1000;
		count = len;
		ptr = new double[capacity];
		for(int i = 0; i < len; i++){
			ptr[i] = arr[i];
		}
	}

	MyArrayParent(const MyArrayParent& A)
	{
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
	virtual void push(double value)
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
		if (count < 0){
            delete[] ptr;
        }
	}

	double& operator[](int index)
	{
		if(index >= count){
			std::cout << "ERROR: index is out of range" << std::endl;
		}else{
			return ptr[index];
		}
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
		cout << "\nMyArray, size: " << count<<", values: {";
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

	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) {}
	MyArrayChild(double* arr, int len) : MyArrayParent(arr, len) {}
	

	~MyArrayChild() {}


	virtual int IndexOf(double value, bool bFindFromStart = true)
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


	virtual void InsertAt(double value, int index = -1)
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
	void RemoveAt(int index = -1)
	{
		if(index == -1){
			this->RemoveLastValue();
		}
		if(index <= count){
			if(index > -1){
				for(int i = index; i < count-1; i++){
					ptr[i] = ptr[i + 1];
				}
				count--;
			}
			if(index < -1){
				std::cout << "\nERROR: invalid index\n";
			}
		}else{
			std::cout << "\nERROR: index is out of range\n";
		}		
	}

	//поиск элемента
	//void IndexOf(double value, bool bFindFromStart = true);

	//вставка элемента
	//void InsertAt(double value, int index = -1);

	//выделение подпоследовательности
	//MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)

	//добавление элемента в конец
	//operator + ?

};

class MySortedArray : public MyArrayChild
{
    protected:
        int BinSearch(double value, int left, int right)
        {

            int middle = (left+right)/2;

            if(fabs(value - ptr[middle]) < 0.0001){
                return middle;
            }
            if(middle == left){
                if(fabs(value - ptr[middle]) < 0.0001){
                    return right;
                }
                return -1;
            }
            
            if (ptr[middle] > value){
                return BinSearch(value, left, middle-1);
            }
            if (ptr[middle] < value){
                return BinSearch(value, middle+1, right);
            }
        }

        int BinSearch2(double value, int left, int right)
        {

            int middle = (left+right)/2;

            if(fabs(value - ptr[middle]) < 0.0001){
                return middle;
            }
            if(middle == left){
                if(fabs(value - ptr[middle]) < 0.0001){
                    return right;
                }
                return left;
            }
            
            if (ptr[middle] > value){
                return BinSearch2(value, left, middle-1);
            }
            if (ptr[middle] < value){
                return BinSearch2(value, middle+1, right);
            }
        }

    public:
        MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) {}
        ~MySortedArray() {}

        int IndexOf(double value, bool bFindFromStart = true)
        {
            return BinSearch2(value, 0, count);
        }

        void push(double value)
        {
            if(count == 0){
                MyArrayParent::push(value);
                return;
            }
            if(count == 1){
                if(value < ptr[0]){
                    InsertAt(value, 0);
                }else{
                    MyArrayParent::push(value);
                }
                return;
            }
            int index = BinSearch2(value, 0, count);
            InsertAt(value, index);
        }

};



void swapInArray(double* arr, int indexLeft, int indexRight)
{
	double temp = arr[indexLeft];
	arr[indexLeft] = arr[indexRight];
	arr[indexRight] = temp;
}

int main()
{
    
	MyArrayParent* arr;
	//указатель тепа child
	MySortedArray ptr;
	//объект типа sorted
	arr = &ptr;
	//указателю присвоили ссылку на объект

	int i = 0;
	for (i = 9; i >= 0; i--)
	{
		arr->push(i + 1);
	}
	arr->print();
	MySortedArray A;
	for (i = 9; i >= 0; i--)
	{
		A.push(i + 1);
	}
	A.print();
	cout << "\n";
	//cout << arr->IndexOf(1) << "\n";
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
