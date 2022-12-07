#include <cmath>
#include <iostream>

class Point
{
public:
    double x, y;

    Point()
    {
        x = 0;
        y = 0;
    }

    Point(double X, double Y)
    {
        x = X;
        y = Y;
    }

    Point(const Point &p)
    {
        x = p.x;
        y = p.y;
    }

    ~Point() {}

    double len()
    {
        return sqrt(x * x + y * y);
    }

    bool operator<(Point &p) { return len() < p.len() ? true : false; }

    bool operator<(double r) { return x < r ? true : false; }

    friend bool operator<(double r, Point p); 
};

bool operator<(double r, Point p) { return p.x < r; }

int main()
{
    Point p, p2, p3;
    p = Point(1, 1);
    p2 = Point(2, 2);

    bool a = p2 < p;
    bool b = p < p2;
    bool c = 2 < p;
    bool d = p < 2;
    std::cout << a << " " << b << " " << c << " " << d;
}