#include <cmath>
#include <iostream>
#define M_PI (3.141592653589793)
#define M_2PI (2. * M_PI)

using namespace std;

int Cubic(double *x, double a, double b, double c)
{
	double q, r, r2, q3;
	q = (a * a - 3. * b) / 9.;
	r = (a * (2. * a * a - 9. * b) + 27. * c) / 54.;
	r2 = r * r;
	q3 = q * q * q;
	if (r2 < q3)
	{
		double t = acos(r / sqrt(q3));
		a /= 3.;
		q = -2. * sqrt(q);
		x[0] = q * cos(t / 3.) - a;
		x[1] = q * cos((t + M_2PI) / 3.) - a;
		x[2] = q * cos((t - M_2PI) / 3.) - a;
		return (3);
	}
	else
	{
		double aa, bb;
		if (r <= 0.)
			r = -r;
		aa = -pow(r + sqrt(r2 - q3), 1. / 3.);
		if (aa != 0.)
			bb = q / aa;
		else
			bb = 0.;
		a /= 3.;
		q = aa + bb;
		r = aa - bb;
		x[0] = q - a;
		x[1] = (-0.5) * q - a;
		x[2] = (sqrt(3.) * 0.5) * fabs(r);
		if (x[2] == 0.)
			return (2);
		return (1);
	}
}

double det(double **T, int N)
{
	double det__;
	int sub_j, s;
	double **subT; // Субматрица как набор ссылок на исходную матрицу
	switch (N)
	{
	case 1:
		return T[0][0];
	case 2:
		return T[0][0] * T[1][1] - T[0][1] * T[1][0];
	default:
		if (N < 1)
			return nan("1");		// Некорректная матрица
		subT = new double *[N - 1]; // Массив ссылок на столбцы субматрицы
		det__ = 0;
		s = 1; // Знак минора
		for (int i = 0; i < N; i++)
		{
			sub_j = 0;
			for (int j = 0; j < N; j++)		  // Заполнение субматрицы ссылками на исходные столбцы
				if (i != j)					  // исключить i строку
					subT[sub_j++] = T[j] + 1; // здесь + 1 исключает первый столбец
			det__ = det__ + s * T[i][0] * det(subT, N - 1);
			s = -s;
		}
		delete[] subT;
		return det__;
	}
}

class MyArrayParent
{
protected:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double *ptr;

public:
	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100)
	{
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	MyArrayParent(double *arr, int len)
	{
		capacity = (len >= 1000) ? len << 1 : 1000;
		count = len;
		ptr = new double[capacity];
		for (int i = 0; i < len; i++)
		{
			ptr[i] = arr[i];
		}
	}

	MyArrayParent(const MyArrayParent &A)
	{
		capacity = A.capacity;
		count = A.count;
		ptr = new double[capacity];
		for (int i = 0; i < count; i++)
		{
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
		else
		{
			std::cout << "ERROR: invalid index";
		}
	}

	//добавление в конец нового значения
	virtual void push(double value)
	{
		if (count < capacity)
		{
			ptr[count++] = value;
		}
		else
		{
			double *res = new double[capacity * 2];
			for (int i = 0; i < count; i++)
			{
				res[i] = ptr[i];
			}
			res[count + 1] = value;
			delete[] ptr;
			ptr = res;
		}
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count >= 0)
		{
			ptr[--count] = 0;
		}
		if (count < 0)
		{
			delete[] ptr;
		}
	}

	double &operator[](int index)
	{
		if (index >= count)
		{
			std::cout << "ERROR: index is out of range" << std::endl;
		}
		else
		{
			return ptr[index];
		}
	}

	MyArrayParent operator=(const MyArrayParent &A)
	{
		if (capacity != A.capacity)
		{
			delete[] ptr;
			capacity = A.capacity;
			ptr = new double[A.capacity];
			count = A.count;
			for (int i = 0; i < count; i++)
				ptr[i] = A.ptr[i];
		}

		if (capacity == A.capacity)
		{
			count = A.count;
			for (int i = 0; i < count; i++)
				ptr[i] = A.ptr[i];
		}
		return *this;
	}

	void print()
	{
		cout << "\nMyArray, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}

	virtual int IndexOf(double value, bool bFindFromStart = true) {}
	virtual void RemoveAt(int index = -1) {}
	virtual void InsertAt(double value, int index = -1) {}

	virtual int TypeOfSurface()
	{
		if (count > 10)
		{
			std::cout << "\nERROR: not a surface\n";
			return 0;
		}
		else
		{
			double **k4 = new double *[4];
			k4[0] = new double[4]{ptr[0], ptr[3], ptr[5], ptr[6]};
			k4[1] = new double[4]{ptr[3], ptr[1], ptr[4], ptr[7]};
			k4[2] = new double[4]{ptr[5], ptr[4], ptr[2], ptr[8]};
			k4[3] = new double[4]{ptr[6], ptr[7], ptr[8], ptr[9]};
			double K4 = det(k4, 4);

			double **i3 = new double *[3];
			i3[0] = new double[3]{ptr[0], ptr[3], ptr[5]};
			i3[1] = new double[3]{ptr[3], ptr[1], ptr[4]};
			i3[2] = new double[3]{ptr[5], ptr[4], ptr[2]};
			double I3 = det(i3, 3);

			double **i2_0 = new double *[2];
			i2_0[0] = new double[2]{ptr[0], ptr[3]};
			i2_0[1] = new double[2]{ptr[3], ptr[1]};
			double **i2_1 = new double *[2];
			i2_1[0] = new double[2]{ptr[0], ptr[5]};
			i2_1[1] = new double[2]{ptr[5], ptr[2]};
			double **i2_2 = new double *[2];
			i2_2[0] = new double[2]{ptr[1], ptr[4]};
			i2_2[1] = new double[2]{ptr[4], ptr[2]};
			double I2 = det(i2_0, 2) + det(i2_1, 2) + det(i2_2, 2);

			double I1 = ptr[0] + ptr[1] + ptr[2];

			if (I3 != 0)
			{
				double lyambda[3] = {};
				Cubic(lyambda, I1, I2, I3);

				if (K4 / I3 > 0)
				{
					bool checker = false;
					for (int i = 0; i < 3; i++)
					{
						if (lyambda[i] > 0)
							checker = true;
					}
					if (!checker)
					{
						// std::cout << "\nIt is ellipsoid";
						return 1;
					}
					for (int i = 0; i < 3; i++)
					{
						if (lyambda[i] < 0)
							checker = true;
					}
					if (!checker)
					{
						// std::cout << "\nIt is imaginary ellipsoid";
						return -1;
					}
					int c = 0;
					for (int i = 0; i < 3; i++)
					{
						if (lyambda[i] > 0)
							c++;
					}
					if (c == 1)
					{
						// std::cout << "\nIt is single-cavity hyperboloid";
						return 2;
					}
					if (c == 2)
					{
						// std::cout << "\nIt is bicuspid hyperboloid";
						return 3;
					}
				}
				else if (K4 / I3 < 0)
				{
					bool checker = false;
					for (int i = 0; i < 3; i++)
					{
						if (lyambda[i] > 0)
							checker = true;
					}
					if (!checker)
					{
						// std::cout << "\nIt is ellipsoid";
						return 1;
					}
					for (int i = 0; i < 3; i++)
					{
						if (lyambda[i] < 0)
							checker = true;
					}
					if (!checker)
					{
						// std::cout << "\nIt is imaginary ellipsoid";
						return -1;
					}
					int c = 0;
					for (int i = 0; i < 3; i++)
					{
						if (lyambda[i] < 0)
							c++;
					}
					if (c == 1)
					{
						// std::cout << "\nIt is single-cavity hyperboloid";
						return 2;
					}
					if (c == 2)
					{
						// std::cout << "\nIt is bicuspid hyperboloid";
						return 3;
					}
				}
				else if (K4 != 0)
				{
					bool checker = false;
					for (int i = 0; i < 3; i++)
					{
						if (lyambda[i] == 0)
							checker = true;
					}
					if (!checker)
					{
						// std::cout << "\nIt is imaginary cone";
						return -4;
					}
					int c = 0;
					for (int i = 0; i < 3; i++)
					{
						if (lyambda[i] > 0)
							c++;
					}
					if (c == 1 || c == 2)
					{
						// std::cout << "\nIt is cone";
						return 4;
					}
				}
			}
			else if (I3 == 0 && K4 != 0)
			{
				int lyambda[2] = {};
				for (int count = 0; count != 1;)
				{
					int l = 0;
					if (l * l - I1 * l + I2 == 0)
					{
						lyambda[count] = l;
						count++;
					}
					l++;
				}
				int c = 0;
				for (int i = 0; i < 3; i++)
				{
					if (lyambda[i] > 0)
						c++;
				}
				if (c == 0 || c == 2)
				{
					// std::cout << "\nIt is elliptical paraboloid";
					return 5;
				}
				if (c == 1)
				{
					// std::cout << "\nIt is hyperbolic paraboloid";
					return 6;
				}

			} /*else if(I3 == 0 && K4 == 0 && I2 != 0){ // недоделаны некоторые поверхности
				 int lyambda[2] = {};
				 for(int count = 0; count != 1;)
				 {
					 int l = 0;
					 if(l*l -I1*l + I2 == 0)
					 {
						 lyambda[count] = l;
						 count++;
					 }
					 l++;
				 }
				 int c = 0;
				 for(int i = 0; i < 3; i++){
					 if(lyambda[i] > 0)
						 c++;
				 }
				 if(c == 0 || c == 2){
					 std::cout << "It is elliptical paraboloid";
					 return;
				 }

			 }*/
		}
	}
};

class MyArrayChild : public MyArrayParent
{
public:
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) {}
	MyArrayChild(double *arr, int len) : MyArrayParent(arr, len) {}

	~MyArrayChild() {}

	int IndexOf(double value, bool bFindFromStart = true)
	{
		if (bFindFromStart)
		{
			for (int i = 0; i < count; i++)
				if (ptr[i] == value)
					return i;

			return -1;
		}
		else
		{
			for (int i = count; i > 0; i--)
				if (ptr[i] == value)
					return i;
			return -1;
		}
	}

	void InsertAt(double value, int index = -1)
	{
		if (index == -1 || index > capacity)
		{
			push(value);
			return;
		}
		if (count < capacity)
		{
			for (int i = count; i > index; i--)
			{
				ptr[i] = ptr[i - 1];
			}
			ptr[index] = value;
			count++;
		}
	}

	//удаление элемента
	void RemoveAt(int index = -1)
	{
		if (index == -1)
		{
			this->RemoveLastValue();
		}
		else
		{
			if (index <= count)
			{
				if (index > -1)
				{
					for (int i = index; i < count - 1; i++)
					{
						ptr[i] = ptr[i + 1];
					}
					count--;
				}
				if (index < -1)
				{
					std::cout << "\nERROR: invalid index\n";
				}
			}
			else
			{
				std::cout << "\nERROR: index is out of range\n";
			}
		}
	}

	//выделение подпоследовательности
	MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)
	{
		if (Length == -1)
		{
			MyArrayChild res(1);
			res.push(ptr[StartIndex]);
			return res;
		}
		MyArrayChild res(Length);
		for (int i = StartIndex; i < StartIndex + Length; i++)
		{
			res.push(ptr[i]);
		}
		return res;
	}
};

class MySortedArray : public MyArrayChild
{
protected:
	int BinSearch(double value, int left, int right)
	{

		int middle = (left + right) / 2;

		if (fabs(value - ptr[middle]) < 0.0001)
		{
			return middle;
		}
		if (middle == left)
		{
			if (fabs(value - ptr[middle]) < 0.0001)
			{
				return right;
			}
			return -1;
		}

		if (ptr[middle] > value)
		{
			return BinSearch(value, left, middle - 1);
		}
		if (ptr[middle] < value)
		{
			return BinSearch(value, middle + 1, right);
		}
	}

	int BinSearch2(double value, int left, int right)
	{

		int middle = (left + right) / 2;

		if (fabs(value - ptr[middle]) < 0.0001)
		{
			return middle;
		}
		if (middle == left)
		{
			if (fabs(value - ptr[middle]) < 0.0001)
			{
				return right;
			}
			return left;
		}

		if (ptr[middle] > value)
		{
			return BinSearch2(value, left, middle - 1);
		}
		if (ptr[middle] < value)
		{
			return BinSearch2(value, middle + 1, right);
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
		if (count == 0)
		{
			MyArrayParent::push(value);
			return;
		}
		if (count == 1)
		{
			if (value < ptr[0])
			{
				InsertAt(value, 0);
			}
			else
			{
				MyArrayParent::push(value);
			}
			return;
		}
		int index = BinSearch2(value, 0, count);
		InsertAt(value, index);
	}
};

void swapInArray(double *arr, int indexLeft, int indexRight)
{
	double temp = arr[indexLeft];
	arr[indexLeft] = arr[indexRight];
	arr[indexRight] = temp;
}

int main()
{

	MyArrayParent *arr;
	MyArrayChild arr_1;
	MySortedArray ptr_1;
	MySortedArray ptr_2;
	MySortedArray ptr_3;
	arr = &ptr_1;

	for (int i = 0; i < 10; i++)
	{
		arr_1.push(i + 1);
	}

	MyArrayChild arr_2(arr_1.SubSequence(1, 2));
	arr_2.print();

	for (int i = 10; i > 0; i--)
	{
		arr->push(i);
	}
	arr->print();
	std::cout << "\n"
			  << arr->IndexOf(3);
	ptr_2 = ptr_1;
	ptr_2.print();
	arr->RemoveAt(2);
	arr->print();
	arr->InsertAt(3, 2);
	arr->print();

	arr = &ptr_3;
	for (int i = 10; i > 0; i--)
	{
		arr->push(i % 5);
	}
	std::cout << arr->TypeOfSurface();

	return 0;
}
