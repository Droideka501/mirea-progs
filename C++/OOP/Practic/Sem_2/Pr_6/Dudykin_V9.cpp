#include <iostream>
#include <string>
#include <typeinfo>
#include <fstream>

using namespace std;

ostream &my_manip(ostream &s)
{
    s.fill('%');
    s.setf(ios::right);
    return s;
}

template <class T>
class Element
{
protected:
    Element *next;
    Element *prev;
    T info;

public:
    Element(T data)
    {
        next = prev = NULL;
        info = data;
    }

    Element(Element *Next, Element *Prev, T data)
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

    virtual int size() { return count; }

    virtual Element<T> *pop() = 0;

    virtual Element<T> *push(T value) = 0;

    virtual Element<T> *insert(T value, Element<T> *predessesor = NULL) = 0;

    virtual Element<T> *remove(Element<T> *predessesor = NULL) = 0;

    virtual Element<T> *find(T value) = 0;

    virtual Element<T> &operator[](int index) = 0;

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

    template <class T1>
    friend ostream &operator<<(ostream &s, LinkedList<T1> &list);
};

template <class T1>
ostream &operator<<(ostream &s, LinkedList<T1> &list)
{
    s << "{";
    Element<T1> *p = list.head;
    while (p != NULL)
    {
        T1 info = p->getInfo();
        s << info << ", ";
        p = p->getNext();
    }
    s << "}";
    return s;
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

    virtual Element<T> *push(T value)
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

    virtual Element<T> *insert(T value, Element<T> *predessesor = NULL)
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

    virtual Element<T> *find(T value)
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

    virtual Element<T> *find_r(T value, Element<T> *current = NULL)
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
    virtual Element<T> *push(T value)
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

    virtual Element<T> *insert(T value, Element<T> *predessesor = NULL)
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

    virtual Element<T> *remove(Element<T> *predessesor = NULL)
    {

        if (predessesor == LinkedList<T>::tail)
        {
            return NULL;
        }
        Element<T> *removed = LinkedList<T>::head;
        if (predessesor == NULL)
        {
            LinkedList<T>::head = removed->getNext();
            removed->getNext()->setPrev(predessesor);
        }
        else
        {
            removed = predessesor->getNext();
            predessesor->setNext(removed->getNext());
            predessesor->getNext()->setPrev(predessesor);
        }
        return removed;
    }

    virtual Element<T> *find(T key)
    {
        Element<T> *p = LinkedList<T>::head;

        while (p != NULL)
        {
            if (p->getInfo() == key)
            {
                return p;
            }
            p = p->getNext();
        }
        return NULL;
    }

    virtual void filter(bool (*cmp)(T), DoubleSidesStack<T> *dest)
    {
        for (Element<T> *current = LinkedList<T>::head; current != NULL; current = current->getNext())
        {
            if (cmp(current->getInfo()))
            {
                dest->push(current->getInfo());
            }
        }
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
        if (index + 1 <= LinkedList<T>::count / 2)
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
            for (int i = LinkedList<T>::count; i != index + 1; i--)
            {
                p = p->getPrev();
            }
            return *p;
        }
    }
    /*
    template <class T1>
    friend ostream operator<<(ostream &s, const DoubleSidesStack<T1> &stack);
    */
};
/*
template <class T3>
ostream operator<<(ostream &s, const DoubleSidesStack<T3> &stack)
{

}
*/

template <class T>
class List : public DoubleSidesStack<T>
{

public:
    virtual Element<T> *push(T value)
    {
        Element<T> *new_el = new Element<T>(value);
        if (LinkedList<T>::head == NULL)
        {
            LinkedList<T>::head = new_el;
            LinkedList<T>::tail = LinkedList<T>::head;
        }
        else
        {
            LinkedList<T>::head->setPrev(new_el);
            new_el->setNext(LinkedList<T>::head);
            LinkedList<T>::head = new_el;
        }
        return new_el;
    }

    virtual Element<T> *pop()
    {
        Element<T> *new_el = DoubleSidesStack<T>::pop();
        return new_el;
    }

    virtual Element<T> *find(string key)
    {
        Element<T> *p = LinkedList<T>::head;
        while (p != NULL)
        {
            if (p->getInfo() == key)
            {
                return p;
            }
            p = p->getNext();
        }
        return NULL;
    }

    template <class Key>
    void filter(Key key, List<T> &filtered)
    {
        Element<T> *p = LinkedList<T>::head;
        while (p != NULL)
        {
            if (p->getInfo() == key)
            {
                filtered.push(p->getInfo());
            }
            p = p->getNext();
        }
    }

    template <class Key>
    void filter(Key key, bool (*cmp)(T, Key), List<T> &filtered)
    {
        Element<T> *p = LinkedList<T>::head;
        while (p != NULL)
        {
            if (cmp(p->getInfo(), key))
            {
                filtered.push(p->getInfo());
            }
            p = p->getNext();
        }
    }

    virtual int size() { return LinkedList<T>::count; }

    virtual void operator=(const List<T> &list)
    {
        Element<T> *p = LinkedList<T>::head;
        Element<T> *temp = p;
        for (; p != NULL; p = temp)
        {
            temp = p->getNext();
            delete p;
        }

        LinkedList<T>::head = LinkedList<T>::tail = NULL;
        LinkedList<T>::count = 0;

        Element<T> *ptr = list.LinkedList<T>::head;
        while (ptr != NULL)
        {
            this->push(ptr->getInfo());
            ptr = ptr->getNext();
        }
    }

    virtual Element<T> &operator[](unsigned int index)
    {
        if (LinkedList<T>::head == NULL)
        {
            // throw Exception("List is empty");
        }
        if (index > LinkedList<T>::count)
        {
            // throw Exception("Index out of range");
        }
        if (index + 1 <= LinkedList<T>::count / 2)
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
            for (int i = LinkedList<T>::count; i != index + 1; i--)
            {
                p = p->getPrev();
            }
            return *p;
        }
    }

    void saveList(string fileName)
    {
        ofstream fout(fileName);
        if (fout.is_open())
        {
            fout << LinkedList<T>::count << "\n";
            Element<T> *pom = LinkedList<T>::head;
            T info;
            for (int i = 0; i < LinkedList<T>::count; i++)
            {
                info = pom->getInfo();
                fout << info << "\n";
                pom = pom->getNext();
            }
            fout.close();
        }
    }
    void loadList(string fileName)
    {
        ifstream fin;
        fin.open(fileName);
        if (fin.is_open())
        {
            int ct;
            fin >> ct;

            if (ct != LinkedList<T>::count)
            {
                LinkedList<T>::count = 0;
                if (LinkedList<T>::head != NULL)
                {
                    Element<T> *current = LinkedList<T>::head;
                    Element<T> *temp = LinkedList<T>::head->getNext();
                    for (; current != LinkedList<T>::tail; current = temp, temp = temp->getNext())
                    {
                        delete current;
                    }
                }
                LinkedList<T>::head = NULL;
                LinkedList<T>::tail = NULL;
                T val;
                for (int i = 0; i < ct; i++)
                {
                    fin >> val;
                    push(val);
                }
            }
            else
            {
                Element<T> *pom = LinkedList<T>::head;
                T val;
                for (int i = 0; i < LinkedList<T>::count; i++)
                {
                    fin >> val;
                    pom->setInfo(val);
                    pom = pom->getNext();
                }
            }
            fin.close();
        }
    }
    

    template <class T1>
    friend ostream &operator<<(ostream &s, List<T1> &list);
};

template <class T4>
ostream &operator<<(ostream &s, List<T4> &list)
{
    s << "\n\tYour list of " << typeid(T4).name() << "\n{";
    Element<T4> *p = list.LinkedList<T4>::head;
    while (p != NULL)
    {
        T4 info = p->getInfo();
        s << info << ", ";
        p = p->getNext();
    }
    s << "}\n\tend of list";
    return s;
}

class Car
{
private:
    string brand;
    string color;
    string serial_num;
    int num_of_doors;
    int year_of_present;
    double price;

public:
    Car(string brand_ = "unknown", string color_ = "unknown", string serial_num_ = "unknown", int num_of_doors_ = 0, int year_of_present_ = 0, int price_ = 0)
    {
        brand = brand_;
        color = color_;
        serial_num = serial_num_;
        num_of_doors = num_of_doors_;
        year_of_present = year_of_present_;
        price = price_;
    }

    Car(const Car &car)
    {
        brand = car.brand;
        color = car.color;
        serial_num = car.serial_num;
        num_of_doors = car.num_of_doors;
        year_of_present = car.year_of_present;
        price = car.price;
    }

    ~Car() {}

    string getBrand() { return brand; }
    string getColor() { return color; }
    string getSerialNum() { return serial_num; }
    int getNumOfdoors() { return num_of_doors; }
    int getYearOfPresent() { return year_of_present; }
    double getPrice() { return price; }

    bool operator==(const Car &obj)
    {
        if (*this == obj)
            return true;
        return false;
    }

    bool operator==(const string &num)
    {
        if (serial_num == num)
            return true;
        return false;
    }

    bool operator==(const double &num)
    {
        if (price == num)
            return true;
        return false;
    }

    friend ostream &operator<<(ostream &s, Car &value);
    friend istream &operator>>(istream &s, Car &value);
};

ostream &operator<<(ostream &s, Car &value)
{
    if (typeid(s) == typeid(ifstream))
    {
        s << value.getBrand() << " " << value.getColor() << " " << value.getSerialNum() << " " << value.getNumOfdoors() << " " << value.getYearOfPresent() << " " << value.getPrice();
    }
    else
    {
        s << my_manip << "\n\tInfo about car";
        s << my_manip << "\n-------------------------------\n";
        s << my_manip << "Brand of car: " << value.getBrand() << "\n";
        s << my_manip << "Color: " << value.getColor() << "\n";
        s << my_manip << "Serial number: " << value.getSerialNum() << "\n";
        s << my_manip << "Number of car's doors: " << value.getNumOfdoors() << "\n";
        s << my_manip << "Year of present: " << value.getYearOfPresent() << "\n";
        s << my_manip << "Price: " << value.getPrice() << "\n";
        s << my_manip << "-------------------------------\n";
    }
    return s;
}

istream &operator>>(istream &s, Car &value)
{
    string brand, color, ser_num;
    double price;
    int num_doors, year;
    s >> brand >> color >> ser_num >> ser_num >> num_doors >> year >> price;
    value = Car(brand, color, ser_num, num_doors, year, price);
}

int main()
{
    Car c1("first", "green", "XM0601", 4, 2023, 1.5e+7), c2("second", "red", "XM0602", 4, 2024, 1.6e+7), c3("third", "blue", "XM0603", 4, 2025, 1.4e+7), c4("fourth", "yellow", "XM0604", 4, 2023, 1.6e+7);

    LinkedList<double> *list;

    list = new DoubleSidesStack<double>();
    for (int i = 0; i < 10; i++)
        list->push(i * 2 - 1);

    //cout << *list;

    DoubleSidesStack<double> *castedList = dynamic_cast<DoubleSidesStack<double> *>(list);
    cout << (castedList->find(5)) << endl;

    delete list;
    return 0;
    DoubleSidesStack<Car> s;
    s.push(c1);
    s.push(c2);
    s.push(c3);
    s.push(c4);
    // cout << s << endl;

    List<Car> l, l2, l3;
    l.push(c1);
    l.push(c2);
    l.push(c3);
    l.push(c4);

    cout << l << endl;

    cout << "\n Found \n"
         << *l.find("XM0601") << endl;

    l.filter<double>(1.6e+7, l2);
    cout << l2;

    l.pop();
    cout << l;

    cout << l2;
    l2.saveList("list.txt");
    l3.loadList("list.txt");
    cout << l3;

    cout.width(10);
    cout << my_manip << endl << 1e-10;

    // s.pop();
    /*
    for (int i = 0; i < s.size(); i++)
    {
        cout << s[i] << endl;
    }*/
    return 0;
}