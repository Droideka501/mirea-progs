#include <iostream>

class A1
{
protected:
    int a1;

public:
    A1(int V1 = 0)
    {
        a1 = V1;
        std::cout << "\nClass A1 constructor";
    }
    virtual void print() { std::cout << "\nVariable of A1 class"; }
    virtual void show() { std::cout << "\na1 = " << a1; }
};

class B1 : virtual public A1
{
protected:
    int b1;

public:
    B1(int V1 = 0, int V2 = 0) : A1(V2)
    {
        b1 = V1;
        std::cout << "\nClass B1 constructor";
    }
    virtual void print() { std::cout << "\nVariable of B1 class"; }
    virtual void show() { std::cout << "\nb1 = " << b1 << ", a1 =" << a1; }
};

class B2 : virtual public A1
{
protected:
    int b2;

public:
    B2(int V1 = 0, int V2 = 0) : A1(V2)
    {
        b2 = V1;
        std::cout << "\nClass B2 constructor";
    }
    virtual void print() { std::cout << "\nVariable of B2 class"; }
    virtual void show() { std::cout << "\nb2 = " << b2 << ", a1 = " << a1; }
};

class B3 : virtual public A1
{
protected:
    int b3;

public:
    B3(int V1 = 0, int V2 = 0) : A1(V2)
    {
        b3 = V1;
        std::cout << "\nClass B3 constructor";
    }
    virtual void print() { std::cout << "\nVariable of B3 class"; }
    virtual void show() { std::cout << "\nb3 = " << b3 << ", a1 = " << a1; }
};

class C1 : virtual public B1, virtual public B2, virtual public B3
{
protected:
    int c1;

public:
    C1(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0) : B1(V2), B2(V3), B3(V4)
    {
        c1 = V1;
        std::cout << "\nClass C1 constructor";
    }
    virtual void print() { std::cout << "\nVariable of C1 class"; }
    virtual void show() { std::cout << "\nc1 = " << c1 << ", b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << ", a1 = " << a1; }
};

class C2 : virtual public B1, virtual public B2, virtual public B3
{
protected:
    int c2;

public:
    C2(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0) : B1(V2), B2(V3), B3(V4)
    {
        c2 = V1;
        std::cout << "\nClass C2 constructor";
    }
    virtual void print() { std::cout << "\nVariable of C2 class"; }
    virtual void show() { std::cout << "\nc2 = " << c2 << ", b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << ", a1 = " << a1; }
};

int main()
{
    C1 test_1(2, 1, 3, 1);
    test_1.show();
    test_1.print();
    A1 *ptr = &test_1;
    ptr->show();
    ptr->print();

    return 0;
}