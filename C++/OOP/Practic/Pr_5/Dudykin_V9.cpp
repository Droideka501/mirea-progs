#include <iostream>
#include <typeinfo>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <ctime>
#include <windows.h>

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
    int rows_1;
    int rows_2;
    int cols_1;
    int cols_2;

public:
    UnequalSize(const char *s, int Rows_1, int Cols_1) : Exception(s)
    {
        rows_1 = Rows_1;
        cols_1 = Cols_1;
    }

    UnequalSize(char *s, int Rows_1, int Cols_1, int Rows_2, int Cols_2) : Exception(s)
    {
        rows_1 = Rows_1;
        rows_2 = Rows_2;
        cols_1 = Cols_1;
        cols_2 = Cols_2;
    }
    UnequalSize(const char *s, int Rows_1, int Cols_1, int Rows_2, int Cols_2) : Exception(s)
    {
        rows_1 = Rows_1;
        rows_2 = Rows_2;
        cols_1 = Cols_1;
        cols_2 = Cols_2;
    }
    UnequalSize(const UnequalSize &e)
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
    int rows_index;
    int cols_index;

public:
    IndexOutOfBounds(char *s, int Rows_index, int Cols_index) : Exception(s)
    {
        rows_index = Rows_index;
        cols_index = Cols_index;
    }
    IndexOutOfBounds(const char *s, int Rows_index, int Cols_index) : Exception(s)
    {
        rows_index = Rows_index;
        cols_index = Cols_index;
    }
    IndexOutOfBounds(const IndexOutOfBounds &e)
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
    const char *object_type;

public:
    NotAMatrixType(char *s, const char *type) : Exception(s)
    {
        object_type = type;
    }
    NotAMatrixType(const char *s, const char *type) : Exception(s)
    {
        object_type = type;
    }
    NotAMatrixType(const NotAMatrixType &e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }
};

class NegativeIndexException : public IndexOutOfBounds
{
public:
    //конструкторы
    NegativeIndexException(char *s, int Row_index, int Col_index) : IndexOutOfBounds(s, Row_index, Col_index) {}
    NegativeIndexException(const char *s, int Row_index, int Col_index) : IndexOutOfBounds(s, Row_index, Col_index) {}
    NegativeIndexException(const NegativeIndexException &e) : IndexOutOfBounds(e) {}

    virtual void print()
    {
        cout << "NegativeIndexException: " << str << "; " << what() << "\n\n";
    }
};

class IndexTooLargeException : public IndexOutOfBounds
{
public:
    //конструкторы
    IndexTooLargeException(char *s, int Row_index, int Col_index) : IndexOutOfBounds(s, Row_index, Col_index) {}
    IndexTooLargeException(const char *s, int Row_index, int Col_index) : IndexOutOfBounds(s, Row_index, Col_index) {}
    IndexTooLargeException(const IndexTooLargeException &e) : IndexOutOfBounds(e) {}

    //вывод сообщения - переопределение виртуальной функции базового класса
    virtual void print()
    {
        cout << "IndexTooLargeException: " << str << "; " << what() << "\n\n";
    }
};

template <class T>
class BaseMatrix
{
protected:
    T **ptr;
    int height;
    int width;

public:
    BaseMatrix(int Height = 2, int Width = 2)
    {
        height = Height;
        width = Width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
            ptr[i] = new double[width];
    }

    BaseMatrix(const BaseMatrix &M)
    {
        height = M.height;
        width = M.width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new double[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = M.ptr[i][j];
        }
    }

    BaseMatrix(istream &s)
    {
        s >> height >> width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new double[width];
        }
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                s >> ptr[i][j];
            }
        }
    }

    ~BaseMatrix()
    {
        if (ptr != NULL)
        {
            for (int i = 0; i < height; i++)
                delete[] ptr[i];
            delete[] ptr;
            ptr = NULL;
        }
    }

    BaseMatrix operator=(BaseMatrix M)
    {
        if (typeid(M) != typeid(BaseMatrix))
        {
            throw NotAMatrixType("Type of object is not a Matrix", typeid(M).name());
        }
        else
        {
            if (M.height == height && M.width == width)
            {
                for (int i = 0; i < height; i++)
                    for (int j = 0; j < width; j++)
                        ptr[i][j] = M.ptr[i][j];
            }
            else
            {
                throw UnequalSize("Unequal size of matrices in operator =", height, width, M.height, M.width);
            }

            return *this;
        }
    }

    double *operator[](int index)
    {
        if (index < 0 || index >= height)
        {
            throw IndexOutOfBounds("Wrong index in operator[] ", index, -1);
        }
        return ptr[index];
    }

    double &operator()(int index_1, int index_2)
    {
        if (index_1 < 0 || index_2 < 0 || index_1 >= height || index_2 >= width)
        {
            throw IndexOutOfBounds("Wrong index in operator[] ", index_1, index_2);
        }
        return ptr[index_1][index_2];
    }

    //транспонирование
    BaseMatrix operator+()
    {
        if (width != height)
        {
            throw UnequalSize("Unequal size of matrix in operator +", height, width);
        }
        BaseMatrix res(width, height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                res.ptr[j][i] = ptr[i][j];
        return res;
    }

    BaseMatrix operator+(BaseMatrix M)
    {
        if (typeid(M) != typeid(BaseMatrix))
        {
            throw NotAMatrixType("Type of object is not a Matrix", typeid(M).name());
        }
        if (width != M.width || height != M.height)
        {
            throw UnequalSize("Unequal size of matrices in operator +", height, width, M.height, M.width);
        }
        BaseMatrix res = *this;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                res.ptr[i][j] += M.ptr[i][j];
        return res;
    }

    BaseMatrix operator+(double value)
    {
        if (width != height)
        {
            throw UnequalSize("Unequal size of matrices in operator +", height, width, 1, 1);
        }
        BaseMatrix res = *this;

        for (int i = 0; i < height; i++)
            res.ptr[i][i] += value;

        return res;
    }

    void print()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
                cout << ptr[i][j] << " ";
            cout << "\n";
        }
    }

    void resizeToOther(const BaseMatrix &M)
    {
        BaseMatrix temp(*this);

        for (int i = 0; i < height; i++)
        {
            delete[] ptr[i];
        }
        delete[] ptr;

        height = M.height;
        width = M.width;

        ptr = new double *[height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new double[width];
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i < temp.height && j < temp.width)
                {
                    ptr[i][j] = temp.ptr[i][j];
                }
                else
                {
                    ptr[i][j] = 0.0;
                }
            }
        }
    }
    template <class T1>
    friend ostream &operator<<(ostream &s, BaseMatrix<T1> &M);
    template <class T2>
    friend istream &operator>>(istream &s, BaseMatrix<T2> &M);
};

template <class T1>
ostream &operator<<(ostream &s, BaseMatrix<T1> &M)
{
    if (typeid(s) == typeid(ofstream))
    {
        s << M.height << " " << M.width << " ";
        for (int i = 0; i < M.height; i++)
        {
            for (int j = 0; j < M.width; j++)
            {
                s << M.ptr[i][j] << " ";
            }
        }
    }
    else
    {
        s << "Your matrix:\nsize: " << M.height << "x" << M.width << endl;
        for (int i = 0; i < M.height; i++)
        {
            for (int j = 0; j < M.width; j++)
            {
                s << M.ptr[i][j] << " ";
            }
            s << "\n";
        }
    }
    return s;
}

template <class T2>
istream &operator>>(istream &s, BaseMatrix<T2> &M)
{
    if (typeid(s) == typeid(ifstream))
    {
        int h, w;
        s >> h >> w;
        if (w != M.width || h != M.height)
        {
            for (int i = 0; i < M.height; i++)
            {
                delete[] M.ptr[i];
            }
            delete[] M.ptr;

            M.width = w;
            M.height = h;
            M.ptr = new T2 *[M.height];
            for (int i = 0; i < M.height; i++)
            {
                M.ptr[i] = new T2[M.width];
            }
        }
        else
        {
            for (int i = 0; i < M.height; i++)
            {
                for (int j = 0; j < M.width; j++)
                {
                    s >> M.ptr[i][j];
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < M.height; i++)
        {
            for (int j = 0; j < M.width; j++)
            {
                s >> M.ptr[i][j];
            }
        }
    }
    return s;
}

template <class T>
class Matrix : public BaseMatrix<T>
{
public:
    Matrix(int Height = 2, int Width = 2) : BaseMatrix<T>(Height, Width) {}
    Matrix(istream &s) : BaseMatrix<T>(s) {}
    Matrix(const Matrix &M)
    {
        if (typeid(M) != typeid(Matrix))
        {
            throw NotAMatrixType("Type of object is not a Matrix", typeid(M).name());
        }
        else
        {
            if (BaseMatrix<T>::ptr != NULL)
            {
                for (int i = 0; i < BaseMatrix<T>::height; i++)
                    delete[] BaseMatrix<T>::ptr[i];
                delete[] BaseMatrix<T>::ptr;
                BaseMatrix<T>::ptr = NULL;
            }
            else
            {
                BaseMatrix<T>::height = M.height;
                BaseMatrix<T>::width = M.width;
                BaseMatrix<T>::ptr = new double *[BaseMatrix<T>::height];
                for (int i = 0; i < BaseMatrix<T>::height; i++)
                {
                    BaseMatrix<T>::ptr[i] = new double[BaseMatrix<T>::width];
                    for (int j = 0; j < BaseMatrix<T>::width; j++)
                        BaseMatrix<T>::ptr[i][j] = M.ptr[i][j];
                }
            }
        }
    }
    ~Matrix() {}

    void generateRandMatrix(int max_rand = 100, unsigned int seed = time(NULL))
    {
        srand(seed);
        for (int i = 0; i < BaseMatrix<T>::height; i++)
        {
            for (int j = 0; j < BaseMatrix<T>::width; j++)
            {
                BaseMatrix<T>::ptr[i][j] = rand() % max_rand;
            }
        }
        Sleep(1000);
    }

    void saveMatrix(ostream &s)
    {
        s << *this;
    }
    template <class T1>
    friend void geometricMeanOfRows(Matrix<T1> &M, vector<double> &v);
};

template <class T>
void geometricMeanOfRows(Matrix<T> &M, vector<double> &v)
{

    if (typeid(M) != typeid(Matrix<T>))
    {
        throw NotAMatrixType("Type of object is not a Matrix", typeid(M).name());
    }
    else
    {
        for (int i = 0; i < M.height; i++)
        {
            double gm = 1;
            for (int j = 0; j < M.width; j++)
            {
                gm *= M.ptr[i][j];
            }
            v.push_back(pow(gm, 1.0 / M.width));
        }
    }
}

int main()
{
    try
    {
        Matrix<double> M(2, 3), M1, M2, M3;
        vector<double> v;

        M.generateRandMatrix();
        M1.generateRandMatrix();
        M2.generateRandMatrix();
        M3.generateRandMatrix();

        cout << M;
        geometricMeanOfRows(M, v);
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << " ";
        }
        cout << endl;

        cout << endl
             << "Testing fout\n";
        ofstream fout("text.txt");
        if (fout.is_open())
        {
            fout << M << M1 << M2 << M3;
            fout.close();
        }
        cout << "Done!";

        cout << endl
             << "Testing fin\n\n";
        ifstream fin;
        fin.open("text.txt");
        if (fin.is_open())
        {
            //fin >> M >> M2 >> M3 >> M1;
            // как было, но тоже рабочий вариант
            fin >> M;
            Matrix<double> MF1(fin), MF2, MF3;
            fin >> MF2 >> MF3;
            M1.resizeToOther(MF1);
            M1 = MF1;
            M2.resizeToOther(MF2);
            M2 = MF2;
            M3.resizeToOther(MF3);
            M3 = MF3;
            
            fin.close();
        }
        cout << M << endl
             << M1 << endl
             << M2 << endl
             << M3;
    }
    catch (NotAMatrixType e)
    {
        e.print();
    }
    catch (IndexOutOfBounds e)
    {
        e.print();
    }
    catch (UnequalSize e)
    {
        e.print();
    }
    catch (Exception e)
    {
        e.print();
    }

    return 0;
}
