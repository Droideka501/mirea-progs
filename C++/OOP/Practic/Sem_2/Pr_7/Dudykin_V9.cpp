#include <iostream>
#include <typeinfo>
#include <stdarg.h>
#include <string>
#include <cstring>

using namespace std;


int Max(int n, ...)
{
    int *p = &n;
    int m = *++p;
    for (int i = 0; i < n - 1; i++)
    {
        p++;
        if (m < *p)
        {
            m = *p;
        }
    }
    return m;
}
/*
double product(double arg, ...)
{
    double *ptr = &arg;
    double res = arg;
    while (*++ptr != 0.0)
    {
        cout << res << " " << *ptr << endl;
        res *= *ptr;
    }
    return res;
}

void my_printf(char *s, ...)
{
    va_list l;
    va_start(l, s);
    char *p = s;
    int n_value;
    Fraction F;
    while (*p)
    {
        if (*p == '%')
        {
            switch (*++p)
            {
            case 'd':
                n_value = va_arg(l, int);
                printf("%d", n_value);
                break;
            case 'F':
                F = va_arg(l, Fraction);
                printf("%d/%d", F.numerator(), F.denominator());
                break;
            default:
                printf("%");
                printf("%c", *p);
            }
            *p++;
        }
    }
    va_end(l);
}
*/

string add(string s, ...)
{
    string res("");
    string *ptr = &s;
    while (*ptr != "\0")
    {
        res += *ptr;
        ptr++;
    }
    return res;
}
/*
string add(const char *str, ...)
{
    string res = "";
    char *t = const_cast<char *>(str);
    char **s = &t;
    // int temp = 0;
    while (**s != '\n')
    {
        string t(*s);
        res += t;
        /*
        if(te == 1)
        {
            s+=24;
        }
        s++;
        // temp++;
    }
    return res;
}
*/
template <class T>
T Min(T arg, ...)
{
    T *p = &arg;
    T min_ = *p;
    while (*p != static_cast<T>(1e-19))
    {
        p++;
        if (*p < min_)
        {
            min_ = *p;
        }
    }

    return min_;
}

int main()
{
    //cout << Max(10);
    
    //cout << Min<double>(4., 2., 1., -100., 3., 1e-19) << endl;
    cout << Min<int>(2, 1, 5, -100, 7, 8, 31, 13, 123, 123, 131234, 12312, 1231, 1e-19) << endl;

    // printf("%d, %c, %lf, %%", 1, 2, 3., 4);
    //  double b = product(2.0, 2.5, 2.0, 5.0, 6.0, 0.0);

    // const char *s1("asd"), *s2("ahshd"), *s3("mnwer"), *s4("\n");

    //cout << add("Sadfasd");

    // cout << s; //&v[0] << " " << &v[1];
    return 0;
}