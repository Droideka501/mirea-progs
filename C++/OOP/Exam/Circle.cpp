#include <cmath>
#include <iostream>

using namespace std;

class Circle
{
public:
    double x, y, r;

    Circle()
    {
        x = 0;
        y = 0;
        r = 0;
    }

    Circle(double X, double Y, double R)
    {
        x = X;
        y = Y;
        r = R;
    }

    Circle(const Circle &p)
    {
        x = p.x;
        y = p.y;
        r = p.r;
    }

    ~Circle() { /**/}

    bool operator==(Circle &p)
    {
        return +(*this) == +p ? true : false;
    }

    double operator+()
    {
        const double pi = 3.14;
        return pi * r * r;
    }


    friend bool isIn(Circle p, Circle point);
};

double radius(double x, double y)
{
    return sqrt(x * x + y * y);
}

bool isIn(Circle p, Circle point)
{
    return sqrt((point.x-p.x)*(point.x-p.x) + (point.y-p.y)*(point.y-p.y)) < p.r;
}

int main()
{
    Circle p, p2, p3;
    p = Circle(1, 1, 3);
    p2 = Circle(2, 0, 4);

    double square = +p;

    bool a = p2 == p;
    bool b = isIn(p, Circle(1, 1, 0));
    bool d = isIn(p, Circle(3, 4, 0));
    std::cout << a << " " << b << " " << square << " " << d;
}