#include <iostream>
#include <string>

using namespace std;

template <class T>
class Element
{
protected:
    Element *next;
    Element *prev;
    T info;

public:
    Element(T &data)
    {
        next = prev = NULL;
        info = data;
    }

    Element(Element *Next, Element *Prev, T &data)
    {
        next = Next;
        prev = Prev;
        info = data;
    }

    Element(const Element &el)
    {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }

    T getInfo() { return info; }
    Element *getNext() { return next; }
    Element *getPrev() { return prev; }
    void setInfo(T &Info) { info = Info; }
    void setNext(Element *Next) { next = Next; }
    void setPrev(Element *Prev) { prev = Prev; }

    template <class T1>
    friend ostream &operator<<(ostream &s, Element<T1> &el);
};

template <class T1>
ostream &operator<<(ostream &s, Element<T1> &el)
{
    s << el.info;
    return s;
}

template <class T>
class LinkedList
{
protected:
    Element<T> *head;
    Element<T> *tail;
    int count;

public:
    LinkedList()
    {
        head = tail = NULL;
        count = 0;
    }

    //удалить первый/последний элемент и вернуть удаленное значение
    virtual Element<T> *pop() = 0;

    //добавить элемент в список
    virtual Element<T> *push(T &value) = 0;

    //добавить элемент в середину списка
    virtual Element<T> *insert(T &value, Element<T> *predessesor = NULL) = 0;

    virtual Element<T> *remove(T &value, Element<T> *predessesor = NULL) = 0;


    //поиск элемента в списке
    virtual Element<T> *find(T &value) = 0;

    //получить первый/последний элемент списка
    // virtual Element<T> *front(T value) = 0;
    // virtual Element<T> *back(T value) = 0;

    //доступ по индексу
    virtual Element<T> &operator[](int index) = 0;

    //доработать деструктор
    virtual ~LinkedList()
    {
        Element<T> *p = head;
        Element<T> *temp = p;
        for (; p != NULL; p = temp)
        {
            temp = p->getNext();
            delete p;
        }
    }

    virtual int size() { return count; }

    /*
    virtual void filter(bool (*cmp)(T), LinkedList<T> *dest)
    {
        for (Element<T> *current = head; current != NULL; current = current->getNext())
        {
            if (cmp(current->getInfo()))
            {
                dest->push(current->getInfo());
            }
        }
    }
    */

    template <class T1>
    friend ostream &operator<<(ostream &s, LinkedList<T1> &el);
};

template <class T1>
ostream &operator<<(ostream &s, LinkedList<T1> &el)
{
    s << "{";
    Element<T1> *p = el.head;
    while (p != NULL)
    {
        s << p->getInfo() << ", ";
        p = p->getNext();
    }
    s << "}";
    return s;
}

bool f(int v)
{
    return (v < 5);
}

template <class T>
class Stack : public LinkedList<T>
{
public:
    Stack() : LinkedList<T>() {}
    virtual ~Stack() {}

    virtual Element<T> *pop()
    {
        if (LinkedList<T>::head == NULL)
        {
            return NULL;
        }
        Element<T> *res = LinkedList<T>::tail;
        if (LinkedList<T>::head == LinkedList<T>::tail)
        {
            LinkedList<T>::head = NULL;
            LinkedList<T>::tail = NULL;
        }
        else
        {

            Element<T> *p = LinkedList<T>::head;
            while (p->getNext() != LinkedList<T>::tail)
            {
                p = p->getNext();
            }

            p->setNext(NULL);
            LinkedList<T>::tail = p;
        }
        LinkedList<T>::count--;
        return res;
    }

    virtual Element<T> *push(T &value)
    {
        if (LinkedList<T>::tail == NULL)
        {
            LinkedList<T>::tail = new Element<T>(value);
            LinkedList<T>::head = LinkedList<T>::tail;
        }
        else
        {
            Element<T> *new_el = new Element<T>(value);
            LinkedList<T>::tail->setNext(new_el);
            LinkedList<T>::tail = LinkedList<T>::tail->getNext();
        }
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }

    virtual Element<T> *insert(T &value, Element<T> *predessesor = NULL)
    {
        if (LinkedList<T>::head == NULL || predessesor == LinkedList<T>::tail)
        {
            if (predessesor != NULL)
                return NULL; // throw...;
            return push(value);
        }

        Element<T> *new_el = new Element<T>(value);

        if (predessesor == NULL)
        {
            new_el->setNext(LinkedList<T>::head);
            LinkedList<T>::head = new_el;
        }
        else
        {
            new_el->setNext(predessesor->getNext());
            predessesor->setNext(new_el);
        }
        LinkedList<T>::count++;
        return new_el;
    }

    virtual Element<T> *find(T &value)
    {
        Element<T> *p = LinkedList<T>::head;

        while (p != NULL)
        {
            if (p->getInfo() == value)
                return p;
            p = p->getNext();
        }
        return NULL;
    }

    virtual Element<T> *find(int (*cmp)(T))
    {
        Element<T> *p = LinkedList<T>::head;

        while (p != NULL)
        {
            if (cmp(p->getInfo()) == 1)
            {
                return p;
            }
            p = p->getNext();
        }
        return NULL;
    }

    virtual Element<T> *find_r(T &value, Element<T> *current = NULL)
    {
        if (current == NULL)
            current = LinkedList<T>::head;
        if (current->getInfo() == value)
            return current;
        if (current->getNext())
            return find_r(value, current->getNext());
        else
            return NULL;
    }

    virtual Element<T> *find(T key, int (*cmp)(T))
    {
        Element<T> *p = LinkedList<T>::head;

        while (p != NULL)
        {
            if (cmp(key) == 0)
            {
                return p;
            }
            p = p->getNext();
        }
        return NULL;
    }

    virtual Element<T> &operator[](int index)
    {
        if (LinkedList<T>::head == NULL)
        {
            // throw;
        }
        if (index > LinkedList<T>::count || index < 0)
        {
            // throw;
        }
        Element<T> *p = LinkedList<T>::head;
        for (int i = 0; i < index; i++)
        {
            p = p->getNext();
        }
        return *p;
    }
};

template <class T>
class DoubleSidesStack : public Stack<T>
{
public:
    virtual Element<T> *push(T &value)
    {
        Element<T> *old_tail = LinkedList<T>::tail;
        Element<T> *p = Stack<T>::push(value);
        p->setPrev(old_tail);
        return p;
    }

    virtual Element<T> *pop()
    {
        if (LinkedList<T>::head == LinkedList<T>::tail)
        {
            return NULL;
        }
        Element<T> *new_tail = LinkedList<T>::tail->getPrev();
        Element<T> *res = LinkedList<T>::tail;
        new_tail->setNext(NULL);
        res->setPrev(NULL);
        LinkedList<T>::tail = new_tail;
        LinkedList<T>::count--;
        return res;
    }

    virtual Element<T> *insert(T &value, Element<T> *predessesor = NULL)
    {
        if (predessesor == LinkedList<T>::tail)
        {
            return push(value);
        }
        Element<T> *inserted = Stack<T>::insert(value, predessesor);
        if (inserted == NULL)
        {
            return NULL;
        }
        inserted->setPrev(predessesor);
        inserted->getNext()->setPrev(inserted);
        return inserted;
    }

    virtual Element<T> *remove(T value, Element<T> *predessesor = NULL)
    {
        
    }

    virtual Element<T> &operator[](int index)
    {
        if (LinkedList<T>::head == NULL)
        {
            // throw Exception("List is empty");
        }
        if (index > LinkedList<T>::count || index < 0)
        {
            // throw Exception("Index out of range");
        }
        if (index+1 <= LinkedList<T>::count / 2)
        {
            Element<T> *p = LinkedList<T>::head;
            for (int i = 0; i < index; i++)
            {
                p = p->getNext();
            }
            return *p;
        }
        else
        {
            Element<T> *p = LinkedList<T>::tail;
            for (int i = LinkedList<T>::count; i != index+1; i--)
            {
                p = p->getPrev();
            }
            return *p;
        }
    }

    template <class T1>
    friend ostream operator<<(ostream &s, const DoubleSidesStack<T1> &stack);
};

template <class T3>
ostream operator<<(ostream &s, const DoubleSidesStack<T3> &stack)
{
}

class Car   
{
private:
    string brand;
    string color;
    string serial_num;
    int num_of_doors;
    int year_of_present;
    int price;

public:
    Car(string brand_ = "unknown", string color_ = "unknown", string serial_num_ = "unknown", int num_of_doors_ = 0, int year_of_present_ = 0, int price_ = 0)
    {
        brand = brand_;
        color = color_;
        serial_num = serial_num_;
        num_of_doors = num_of_doors_;
        year_of_present = year_of_present_;
        price = price_;
        cout << "\nSupClass constructor";
    }

    ~Car() { cout << "\nSupClass destructor"; }

    string getBrand() { return brand; }
    string getColor() { return color; }
    string getSerialNum() { return serial_num; }
    int getNumOfdoors() { return num_of_doors; }
    int getYearOfPresent() { return year_of_present; }
    int getPrice() { return price; }

    bool operator==(const Car &rhs)
    {
        if (*this == rhs)
            return true;
        return false;
    }
    
    friend ostream &operator<<(ostream &s, Car &value);
};


ostream &operator<<(ostream &s, Car &value)
{
    s << "\n\tInfo about car";
    s << "\n-------------------------------\n";
    s << "Brand of car: " << value.getBrand() << "\n";
    s << "Color: " << value.getColor() << "\n";
    s << "Serial number: " << value.getSerialNum() << "\n";
    s << "Number of car's doors: " << value.getNumOfdoors() << "\n";
    s << "Year of present: " << value.getYearOfPresent() << "\n";
    s << "Price: " << value.getPrice() << "\n";
    s << "-------------------------------\n";

    return s;
}

int main()
{
    Car c1("first"), c2("second"), c3("third"), c4("fourth");

    DoubleSidesStack<Car> s;
    s.push(c1);
    s.push(c2);
    s.push(c3);
    s.push(c4);
    // cout << s << endl;
    // s.pop();
    for (int i = 0; i < s.size(); i++)
    {
        cout << s[i] << endl;
    }
    return 0;
}