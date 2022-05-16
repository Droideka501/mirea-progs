#include "Exception.h"

class BaseMatrix
{
protected:
    double **ptr;
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
        if (typeid(M) != typeid(Matrix))
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
        if (typeid(M) != typeid(Matrix))
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

    friend ostream &operator<<(ostream &s, BaseMatrix &M);
    friend istream &operator>>(istream &s, BaseMatrix &M);
};

ostream &operator<<(ostream &s, BaseMatrix &M)
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

istream &operator>>(istream &s, BaseMatrix &M)
{
    if (typeid(s) == typeid(ifstream))
    {
        int h, w;
        s >> h >> w;
        if (w != M.width || h != M.height)
        {
            throw UnequalSize("Matrices of unequal sizes while reading file", h, w, M.height, M.width);
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

ostream &manipV9(ostream &s)
{
    s.setf(ios_base::scientific);
    return s;
}

class Matrix : public BaseMatrix
{
public:
    Matrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width) {}
    Matrix(const Matrix &M)
    {
        if (typeid(M) != typeid(Matrix))
        {
            throw NotAMatrixType("Type of object is not a Matrix", typeid(M).name());
        }
        else
        {
            if (ptr != NULL)
            {
                for (int i = 0; i < height; i++)
                    delete[] ptr[i];
                delete[] ptr;
                ptr = NULL;
            }
            else
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
        }
    }
    ~Matrix() {}

    void generateRandMatrix(int max_rand = 100)
    {
        srand(time(0));
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ptr[i][j] = rand() % max_rand;
            }
        }
    }
    friend void geometricMeanOfRows(Matrix &M);
};

void geometricMeanOfRows(Matrix &M)
{

    if (typeid(M) != typeid(Matrix))
    {
        throw NotAMatrixType("Type of object is not a Matrix", typeid(M).name());
    }
    else
    {
        vector<double> v;
        for (int i = 0; i < M.height; i++)
        {
            double gm = 1;
            for (int j = 0; j < M.width; j++)
            {
                gm *= sqrt(M.ptr[i][j]);
            }
            v.push_back(gm);
        }
    }
}

int main()
{
    try
    {
        BaseMatrix M1, M2(2, 3), M;
        // M = +M2;
        // cin >> M2;
        // M1.print();

        Matrix m(2, 3);
        vector<double> v;
        m.generateRandMatrix();
        cout << m;
        geometricMeanOfRows(m);
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << " ";
        }
        cout << endl;

        ofstream fout("text.txt");

        if (fout.is_open())
        {
            fout << m;
            fout.close();
        }

        ifstream fin;
        fin.open("text.txt");

        if (fin.is_open())
        {
            fin >> m;
            fin.close();
        }
        cout << m;
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
