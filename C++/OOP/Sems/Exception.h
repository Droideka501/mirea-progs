#include <iostream>
#include <typeinfo>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

class Exception : public exception
{
protected:
	//сообщение об ошибке
	char *str;

public:
	Exception(const char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception()
	{
		str = NULL;
	}
	Exception(const Exception &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class UnequalSize : public Exception
{
protected:
	int rows_1, rows_2, cols_1, cols_1, cols_2;
public:
	UnequalSize(char* s, int Rows_1, int Rows_2, int Cols_1, int Cols_2) : Exception(s)
	{
		rows_1 = Rows_1; rows_2 = Rows_2; cols_1 = Cols_1; cols_2 = Cols_2;
	}
	UnequalSize(const char* s, int Rows_1, int Rows_2, int Cols_1, int Cols_2) : Exception(S)
	{
		rows_1 = Rows_1; rows_2 = Rows_2; cols_1 = Cols_1; cols_2 = Cols_2;
	}
	UnequalSize(const UnequalSize& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}

	void print()
	{
		cout << "UnequalSize: " << str << "; " << what();
	}

};

class IndexOutOfBounds : public Exception
{
};

/*
//теперь наследуем ошибки от Exception
class DivisionByZero : public Exception
{
	//деление на 0
private:
	//числитель
	int numerator;

public:
	//конструктор
	DivisionByZero(int Numerator) : Exception("attempt to divide by zero")
	{
		numerator = Numerator;
	}

	// get-тер - получение числителя извне
	int getNumerator() { return numerator; }

	//вывод сообщения - переопределение виртуальной функции базового класса
	void print()
	{
		cout << "Exception: " << str << ", numerator = " << numerator << "; " << what();
		//также можно воспользоваться функцией вывода базового класса и потом дописать числитель
		//из-за того, что она называется так же, как эта функция, указываем класс, откуда её берём
		// Exception::print();
		// cout << ", numerator = " << numerator;
	}
};

class NegativeDenominator : public Exception
{
	//отрицательный знаменатель
private:
	//исходная дробь
	//числитель
	int numerator;
	//знаменатель
	int denominator;
	//значение, которое пытались установить
	int value;

public:
	//конструктор
	NegativeDenominator(int Numerator, int Denominator, int Value) : Exception("attempt to set negative denominator")
	{
		numerator = Numerator;
		denominator = Denominator;
		value = Value;
	}

	// get-теры - получение дроби извне
	int getNumerator() { return numerator; }
	int getDenominator() { return denominator; }
	//получение значения, которое пытались установить в знаменатель
	int getValue() { return value; }

	//вывод сообщения
	void print()
	{
		cout << "Exception: " << str << ", value = " << value << ", Fraction = " << numerator << "/" << denominator << "; " << what();
		//также можно воспользоваться функцией вывода базового класса и потом дописать числитель
		//из-за того, что она называется так же, как эта функция, указываем класс, откуда её берём
		// Exception::print();
		// cout << ", value = " << value << ", Fraction = "<<numerator<<"/"<<denominator;
	}
};

class Fraction
{
private:
	//числитель
	int numerator;
	//знаменатель
	int denominator;

public:
	// get-теры - получение значений числителя и знаменателя извне
	int getNumerator() { return numerator; }
	int getDenominator() { return denominator; }

	//установка числителя
	void setNumerator(int value) { numerator = value; }

	//умножение
	Fraction operator*(Fraction F)
	{
		Fraction Res;
		Res.numerator = numerator * F.numerator;
		Res.denominator = denominator * F.denominator;
		return Res;
	}

	//вывод
	void print()
	{
		cout << numerator << "/" << denominator;
	}

	//конструктор
	Fraction(int Numerator = 0, int Denominator = 1)
	{
		if (Denominator == 0)
			throw DivisionByZero(Numerator);
		if (Denominator < 0)
			throw NegativeDenominator(0, 1, Denominator);

		//здесь всё хорошо
		numerator = Numerator;
		denominator = Denominator;
	}

	// set-тер для знаменателя
	void setDenominator(int value)
	{
		if (value == 0)
			throw DivisionByZero(numerator);
		if (value < 0)
			throw NegativeDenominator(numerator, denominator, value);

		//здесь всё хорошо
		denominator = value;
	}
};

int main()
{
	//здесь всё хорошо
	Fraction F1(1, 2);
	Fraction F2(1, 3);
	Fraction F3 = F1 * F2;
	F3.print();

	//а здесь сгенерируем исключение
	try
	{
		Fraction G(1, 0);
		//сюда мы уже не попадём
		Fraction H = G * F1;
		H.print();
	}
	catch (DivisionByZero d)
	{
		//здесь обрабатываем исключение
		cout << "\nDivision by zero exception has been caught:\n";
		d.print();
	}
	catch (NegativeDenominator n)
	{
		//здесь обрабатываем исключение
		cout << "\nNegative denominator exception has been caught:\n";
		n.print();
	}
	// catch для всех ошибок таких типов, которые мы спроектировали сами, - в случае, если нет конкретики
	catch (Exception e)
	{
		//здесь обрабатываем исключение
		cout << "\nException has been caught: ";
		e.print();
	}
	// catch, который среагирует на любые ошибки, - закроет всё, что не обработали предыдущие блоки catch
	catch (...)
	{
		//здесь обрабатываем исключение
		cout << "\nSomething has happened";
	}

	//вторая попытка
	try
	{
		F1.setDenominator(-1);
		//сюда мы уже не попадём
		F3 = F1 * F2;
		F3.print();
	}
	// catch для всех ошибок таких типов, которые мы спроектировали сами, - в случае, если нет конкретики
	catch (Exception e)
	{
		//здесь обрабатываем исключение
		cout << "\nException has been caught: ";
		e.print();
	}
	//просмотр дошёл до catch(...) - срабатывает он
	catch (...)
	{
		//здесь обрабатываем исключение
		cout << "\nSomething has happened";
	}
	char c3;
	std::cin >> c3;
	return 0;
}
*/