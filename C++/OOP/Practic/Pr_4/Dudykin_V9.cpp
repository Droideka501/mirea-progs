#include <iostream>

using namespace std;

class BaseString
{
protected:
    char *p;
    int len;
    int capacity;

public:
    BaseString(char *ptr)
    {
        len = 0;
        for (int i = 0; ptr[i] != '\0'; i++)
        {
            len++;
        }
        capacity = (len >= 256) ? len << 1 : 256;

        p = new char[capacity];

        for (int i = 0; i < len; i++)
        {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }

    BaseString(const char *ptr)
    {
        len = 0;
        for (int i = 0; ptr[i] != '\0'; i++)
        {
            len++;
        }
        capacity = (len >= 256) ? len << 1 : 256;

        p = new char[capacity];

        for (int i = 0; i < len; i++)
        {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }

    BaseString(int Capacity = 256)
    {
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }

    BaseString(const BaseString &s)
    {
        capacity = s.capacity;
        p = new char[capacity];
        len = s.len;
        for (int i = 0; i < len; i++)
        {
            p[i] = s.p[i];
        }
        p[len] = '\0';
    }

    ~BaseString()
    {
        if (p != NULL)
            delete[] p;
        len = 0;
    }

    int Length() { return len; }
    int Capacity() { return capacity; }
    char *get() { return p; }
    char &operator[](int i) { return p[i]; }

    BaseString &operator=(const BaseString &s)
    {
        capacity = s.capacity;
        p = new char[capacity];
        len = s.len;
        for (int i = 0; i < len; i++)
        {
            p[i] = s.p[i];
        }
        p[len] = '\0';
        return *this;
    }

    BaseString operator+(const BaseString &s)
    {
        BaseString res;
        res.len = len + s.len;
        res.capacity = (res.len >= 256) ? capacity + s.capacity : 256;
        for (int i = 0; i < len; i++)
        {
            res.p[i] = p[i];
        }
        for (int i = len; i < res.len; i++)
        {
            res.p[i] = s.p[i - len];
        }
        return res;
    }

    virtual void print()
    {
        int i = 0;
        while (p[i] != '\0')
        {
            cout << p[i];
            i++;
        }
    }

    virtual bool IsPolindrom()
    {
        int j = len - 1;
        for (int i = 0; i < len / 2; i++)
        {
            if (p[i] == p[j])
            {
                j--;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};

class String : public BaseString
{
public:
    String(int Capacity = 256) : BaseString(Capacity) {}
    String(char *ptr) : BaseString(ptr) {}
    String(const char *s) : BaseString(s) {}
    String(const String &s)
    {
        delete[] p;
        capacity = s.capacity;
        p = new char[capacity];
        len = s.len;
        for (int i = 0; i < len; i++)
        {
            p[i] = s.p[i];
        }
        p[len] = '\0';
    }

    ~String() {}

    int IndexOf(char c)
    {
        for (int i = len - 1; i >= 0; i--)
        {
            if (p[i] == c)
            {
                return i;
            }
        }
        return -1;
    }
};

int main()
{
    if (true)
    {
        BaseString s("teset");
        std::cout << s.IsPolindrom() << std::endl;
        // s.print();
        BaseString s1 = s;
        // s1.print();
        BaseString s2;
        s2 = s + s1;
        // s2 = s + s1;
        s2.print();
        std::cout << "\n";

        String str(s.get());
        str.print();
        std::cout << "\n";
        String st("sadsasd");
        str = st;
        std::cout << str.IndexOf('s');
        // s1 = s2 + s;
    }
    return 0;
}
