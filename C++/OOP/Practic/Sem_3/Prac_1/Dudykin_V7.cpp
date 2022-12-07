#include <list>
#include <iostream>
#include <cmath>
#include <string>

template <template <class T, class Alloc = std::allocator<T>> class Container, class T>
void push(Container<T> &l, T value)
{
    if (l.empty())
    {
        l.insert(l.end(), value);
        return;
    }

    auto p = l.begin();

    while (p != l.end() && *p < value)
    {
        p++;
    }
    l.insert(p, value);
}

template <template <class T, class Alloc = std::allocator<T>> class Container, class T>
T pop(Container<T> &sourse)
{
    if (sourse.empty())
    {
        throw std::invalid_argument("Is empty!");
    }
    auto p = sourse.end();
    p--;
    T value = *p;
    sourse.erase(p);

    return value;
}

template <class T>
bool condition(T value)
{
    return value < -value;
}

template <template <class T, class Alloc = std::allocator<T>> class Container, class T>
void filter(Container<T> &sourse, Container<T> &result, bool (*cmp)(T))
{
    auto p = sourse.begin();

    while (p != sourse.end())
    {
        if (cmp(*p))
        {
            push(result, *p);
        }
        p++;
    }
}

template <template <class T, class Alloc = std::allocator<T>> class Container, class T>
void print(Container<T> &sourse)
{
    for (auto it = sourse.begin(); it != sourse.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

enum Type
{
    none,
    ebook,
    book,
    audiobook
};

class Book
{

public:
    std::string surname;
    std::string name;
    int year_of_present;
    std::string publisher;
    unsigned int num_of_pages;
    Type type;
    int count;

    Book(std::string surname_ = "Unknown", std::string name_ = "Unknown",
         int year_of_present_ = 0, std::string publisher_ = "Unknown",
         unsigned int num_of_pages_ = 0, Type type_ = none, int count_ = 0)
    {
        surname = surname_;
        name = name_;
        year_of_present = year_of_present_;
        publisher = publisher_;
        num_of_pages = num_of_pages_;
        type = type_;
        count = count_;
    }

    Book(const Book &book)
    {
        surname = book.surname;
        name = book.name;
        year_of_present = book.year_of_present;
        publisher = book.publisher;
        num_of_pages = book.num_of_pages;
        type = book.type;
        count = book.count;
    }

    bool operator<(Book &b)
    {
        if (count == b.count)
        {
            if (year_of_present == b.year_of_present)
            {
                if (name == b.name) return false;
                else return name < b.name ? true : false;
            }
            else return year_of_present < b.year_of_present ? true : false;
        }
        else return count < b.count ? true : false;
    }

    friend std::ostream& operator<<(std::ostream&, const Book &);
};

std::ostream& operator<<(std::ostream& s, const Book &b)
{
    s << 
    "\nSurname: " << b.surname <<
    "\nName: " << b.name <<
    "\nYear of present: " << b.year_of_present <<
    "\nNum of pages: " << b.num_of_pages <<
    "\nPublication type: " << b.type <<
    "\nCirculation: " << b.count << "\n";
}


//True если тираж не меньше 2
bool cmp(Book b)
{
    return b.count >= 2;
}

int main()
{
    std::list<int> l;
    std::list<int>::iterator p1 = l.begin();

    Book b1, b2, b3;
    b1.count = 3;
    b2.count = 2;
    b3.count = 1;

    std::list<Book> bl, bl2;

    push(bl, b1);
    push(bl, b2);
    push(bl, b3);

    print(bl); 

    filter(bl, bl2, cmp);
    std::cout << "Filtered list:\n";
    print(bl2);

    std::cout << "Deleted item:\n" << pop(bl);

    //print(bl);

    /*
    for (int i = -5; i < 6; i++)
    {
        push(l, int(i * (pow(-1, i))) * 10);
        std::cout << int(i * (pow(-1, i))) << " ";
    }
    std::cout << "\n";

    print(l);

    std::list<int> res, null_con;
    filter(l, res, condition);
    print(res);

    std::cout << pop(l) << "\n";
*/
    // Денис Андреевич, на char все работает!
    // По идее все работает.
    return 0;
}