#include "Exception.h"

using namespace std;

class BaseMatrix
{
protected:
	double** ptr;
	int height;
	int width;
public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		height = Height;
		width = Width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];
	}

	BaseMatrix(const BaseMatrix& M)
	{
        height = M.height;
		width = M.width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++){
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
        if(M.height == height && M.width == width){
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    ptr[i][j] = M.ptr[i][j];

        }else{
            throw UnequalSize("Unequal size of matrices in operator =", height, width, M.height, M.width);
        }

        return *this;
    }

    double* operator[](int index)
    {
        if(index < 0 || index >= height){
            throw IndexOutOfBounds("Wrong index in operator[] ", index, -1);
        }
        return ptr[index];
    }

    double& operator()(int index_1, int index_2)
    {
        if(index_1 < 0 || index_2 < 0 || index_1 >= height || index_2 >= width){
            throw IndexOutOfBounds("Wrong index in operator[] ", index_1, index_2);
        }
        return ptr[index_1][index_2];
    }

    BaseMatrix operator+()
    {
        if(width != height)
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
        if(width != M.width || height != M.height)
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
        if(width != height){
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

};


int main()
{
    try
    {
        BaseMatrix M1, M2(2, 3), M;
        M = +M2;
        M1.print();
    }
    catch(IndexOutOfBounds e)
    {
        e.print();
    }
    catch(UnequalSize e)
    {
        e.print();
    }
    catch(Exception e)
    {
        e.print();
    }

	return 0;
}

