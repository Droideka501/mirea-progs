#include "libs.h"

class Exception : public exception
{
protected:
	//сообщение об ошибке
	char *str;

public:
	Exception(const char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	Exception(char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	Exception()
	{
		str = NULL;
	}
	Exception(const Exception &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
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
	int rows_1; int rows_2; int cols_1; int cols_2;
public:
	UnequalSize(const char* s, int Rows_1, int Cols_1) : Exception(s)
	{
		rows_1 = Rows_1; cols_1 = Cols_1;
	}
	
	UnequalSize(char* s, int Rows_1, int Cols_1, int Rows_2, int Cols_2) : Exception(s)
	{
		rows_1 = Rows_1; rows_2 = Rows_2; cols_1 = Cols_1; cols_2 = Cols_2;
	}
	UnequalSize(const char* s, int Rows_1, int Cols_1, int Rows_2, int Cols_2) : Exception(s)
	{
		rows_1 = Rows_1; rows_2 = Rows_2; cols_1 = Cols_1; cols_2 = Cols_2;
	}
	UnequalSize(const UnequalSize& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "UnequalSize: " << str << "; " << what();
	}

};

class IndexOutOfBounds : public Exception
{
protected:
	int rows_index; int cols_index;
public:
	IndexOutOfBounds(char* s, int Rows_index, int Cols_index) : Exception(s)
	{
		rows_index = Rows_index; cols_index = Cols_index;
	}
	IndexOutOfBounds(const char* s, int Rows_index, int Cols_index) : Exception(s)
	{
		rows_index = Rows_index; cols_index = Cols_index;
	}
	IndexOutOfBounds(const IndexOutOfBounds& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "IndexOutOfBounds: " << str << "; " << what();
	}

};

class NotAMatrixType : public Exception
{
protected:
	const char* object_type;	
public:
	NotAMatrixType(char* s, const char* type) : Exception(s)
	{
		object_type = type;
	}
	NotAMatrixType(const char* s, const char* type) : Exception(s)
	{
		object_type = type;
	}
	NotAMatrixType(const NotAMatrixType& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}
};


/*
class NegativeIndex : public IndexOutOfBounds
{

};

class IndexOutOfRange : public IndexOutOfBounds
{

};
*/