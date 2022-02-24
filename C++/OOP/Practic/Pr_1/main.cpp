#include <iostream>

class Matrix2x2
{
    private:
        double m_11;
        double m_12;
        double m_21;
        double m_22;

    public:
        Matrix2x2(bool single = false)
        {
            if(single) {
                this -> m_11 = this -> m_22 = 1;
                this -> m_12 = this -> m_21 = 0;
            }else{
                this -> m_11 = this -> m_12 = this -> m_21 = this -> m_22 = 0;
            }
            //std::cout << "\nCreated null matrix";
        }

        Matrix2x2(double c_11, double c_12, double c_21, double c_22)
        {
            this -> m_11 = c_11;
            this -> m_12 = c_12;
            this -> m_21 = c_21;
            this -> m_22 = c_22;

        }

        ~Matrix2x2(){ std::cout << "Ta vse ok!\n"; }

        void print()
        {
            std::cout << "\nYour matrix\n" << m_11 << " " << m_12 << "\n" << m_21 << " " << m_22 << "\n\n";
        }

        Matrix2x2 operator=(Matrix2x2 M)
        {
            this -> m_11 = M.m_11;
            this -> m_12 = M.m_12;
            this -> m_21 = M.m_21;
            this -> m_22 = M.m_22;

        }

        Matrix2x2 operator*(double c)
        {
            Matrix2x2 res;

            res.m_11 = this -> m_11 * c;
            res.m_12 = this -> m_12 * c;
            res.m_21 = this -> m_21 * c;
            res.m_22 = this -> m_22 * c;

            return res;
        }

        Matrix2x2 operator*(Matrix2x2 M)
        {
            Matrix2x2 res;

            res.m_11 = this -> m_11 * M.m_11 + this -> m_12 * M.m_21;
            res.m_12 = this -> m_11 * M.m_21 + this -> m_12 * M.m_22;
            res.m_21 = this -> m_21 * M.m_11 + this -> m_22 * M.m_21;
            res.m_22 = this -> m_21 * M.m_21 + this -> m_12 * M.m_22;

            return res;
        }
        
        friend Matrix2x2 operator*(double c, Matrix2x2 M);

};

Matrix2x2 operator*(double c, Matrix2x2 M)
{
    Matrix2x2 res;

    res.m_11 = M.m_11 * c;
    res.m_12 = M.m_12 * c;
    res.m_21 = M.m_21 * c;
    res.m_22 = M.m_22 * c;

    return res; 
}


int main (){
    
    Matrix2x2 M = Matrix2x2(2, 2, 2, 2);
    Matrix2x2 A = Matrix2x2(1, 2, 3, 4);
    M.print();
    M = M*2;
    M.print();
    A = 2 * A;
    A.print();
    M = M*A;
    M.print();
    
    std::cout << "Done!\n";

}