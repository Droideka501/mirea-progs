using namespace std;

#include <iostream>

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
    void setInfo(T Info) { info = Info; }
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
    virtual Element<T> *push(T value) = 0;

    //добавить элемент в середину списка
    virtual Element<T> *insert(T value, Element<T> *predessesor = NULL) = 0;

    //поиск элемента в списке
    virtual Element<T> *find(T value) = 0;

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

    void filter(bool (*cmp)(T), LinkedList<T> *dest)
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
        if (index > LinkedList<T>::count || index < 0L)
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
        if ()

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
};

class SupClass
{
public:
    int data;
    int key;
    SupClass()
    {
        key = 0;
        data = 1;
        cout << "\nSupClass default constructor";
    }
    SupClass(int k, int v = 0)
    {
        key = k;
        data = v;
        cout << "\nSupClass constructor";
    }

    ~SupClass() { cout << "\nSupClass destructor"; }

    friend ostream &operator<<(ostream &s, SupClass &value);
    friend int compare(SupClass s1, SupClass s2);
};

ostream &operator<<(ostream &s, SupClass &value)
{
    s << value.key << ", " << value.data;
    return s;
}

int compare(SupClass s1, SupClass s2)
{
    if (s1.key == s2.key)
        return 0;
    else
        s1.key < s2.key ? -1 : 1;
}

int even(SupClass s1)
{
    s1.key % 2 == 0 ? 1 : 0;
}

int main()
{
    Stack<int> s;
    for (int i = 0; i < 10; i++)
    {
        s.push(i);
    }
    cout << s << endl;
    s.pop();
    cout << s << endl;
    cout << s.find(2) << endl;
    cout << s[5];

    return 0;
}