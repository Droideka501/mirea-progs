#include <iostream>
#include <typeinfo>
#include <stdarg.h>

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
/*
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
int main()
{
    printf("%d, %c, %lf, %%", 1, 2, 3., 4);
    // double b = product(2.0, 2.5, 2.0, 5.0, 6.0, 0.0);
    return 0;
}