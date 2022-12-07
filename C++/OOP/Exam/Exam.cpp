#include <iostream>

class Matrix3x3
{
public:
    double **ptr;

    Matrix3x3()
    {
        ptr = new double *[3];
        for (int i = 0; i < 3; i++)
        {
            ptr[i] = new double[3];
        }
    }

    Matrix3x3(const Matrix3x3 &M)
    {
        *ptr = new double[3];
        for (int i = 0; i < 3; i++)
        {
            ptr[i] = new double[3];
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                ptr[i][j] = M.ptr[i][j];
            }
        }
    }

    ~Matrix3x3()
    {
        for (int i = 0; i < 3; i)
        {
            delete[] ptr[i];
        }
        delete[] ptr;
    }

    bool isSim()
    {
        bool res = true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (ptr[i][j] != ptr[j][i])
                {
                    std::cout << "Matrix is not sim" << std::endl;
                    res = false;
                    return res;
                }
            }
        }
        std::cout << "Matrix is sim" << std::endl;
        return res;
    }

    friend std::istream &operator>>(std::istream &s, Matrix3x3 &M);
    friend std::ostream &operator<<(std::ostream &s, const Matrix3x3 &M);
};

std::istream &operator>>(std::istream &s, Matrix3x3 &M)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            s >> M.ptr[i][j];
        }
    }
    return s;
}

std::ostream &operator<<(std::ostream &s, const Matrix3x3 &M)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            s << M.ptr[i][j] << " ";
        }
        s << std::endl;
    }
    return s;
}

int main()
{
    Matrix3x3 M;
    std::cin >> M;
    std::cout << M.isSim() << std::endl;
    std::cout << M;
    return 0;
}