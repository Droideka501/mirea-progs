#include "Tools.h"

class radiusVector
{
private:
    int x;
    int y;

public:
    radiusVector(int X = 0, int Y = 0)
    {
        x = X;
        y = Y;
    }

    radiusVector(const radiusVector &P)
    {
        x = P.x;
        y = P.y;
    }

    int getX() { return x; }
    int getY() { return y; }
    bool operator==(const radiusVector &v) { return (x == v.x && y == v.y); }

    bool isEqualNorm(const radiusVector &v2) { return (x == v2.x && y == v2.y || x == v2.y && y == v2.x); }
    

    int Norm(char* type_of_norming = "euclidian") 
    {
        if(type_of_norming == "euclidian")
        {
            return sqrt(x*x + y*y);
        }else if(1) return 0;
    }
    
    
};