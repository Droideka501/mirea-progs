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
    bool operator==(const radiusVector &P) { return (x == P.x && y == P.y || x == P.y && y == P.x); }

    int Norm(char* type_of_norming = "euclidian") 
    {
        if(type_of_norming == "euclidian")
        {
            return sqrt(x*x + y*y);
        }else if(1) return 0;
    }
    
    
};