#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

template <class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element *next;
	Element *prev;

	//информация, хранимая в поле
	T field;

public:
	Element(T value)
	{
		field = value;
		next = NULL;
		prev = NULL;
	}

	//доступ к полю *next
	virtual Element *getNext() { return next; }
	virtual void setNext(Element *value) { next = value; }

	//доступ к полю *prev
	virtual Element *getPrevious() { return prev; }
	virtual void setPrevious(Element *value) { prev = value; }

	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	template <class T1>
	friend ostream &operator<<(ostream &ustream, Element<T1> &obj);
};

template <class T>
ostream &operator<<(ostream &ustream, Element<T> &obj)
{
	ustream << obj.field;
	return ustream;
}

template <class T>
class SortedQueue;

template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T> *head;
	Element<T> *tail;
	//для удобства храним количество элементов
	int num;

public:
	virtual int Number() { return num; }

	virtual Element<T> *getBegin() { return head; }

	virtual Element<T> *getEnd() { return tail; }

	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = tail = NULL;
		num = 0;
	}

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T> *push(T value) = 0;

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T> *pop() = 0;

	virtual ~LinkedListParent()
	{
		cout << "\nLinkedList class destructor";
		if (head != NULL)
		{
			Element<T> *current = head;
			Element<T> *temp = head->getNext();
			for (; current != tail; current = temp, temp = temp->getNext())
				delete current;
		}
		head = NULL;
		tail = NULL;
	}

	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T> *operator[](int i)
	{
		//индексация
		if (i < 0 || i > num)
			return NULL;
		int k = 0;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T> *cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	virtual SortedQueue<T> filter(bool (*condition)(T))
	{
		SortedQueue<T> result;
		Element<T> *p = head;
		while (true)
		{
			if (condition(p->getValue()))
				result.push(p->getValue());

			if (p == tail)
				break;

			p = p->getNext();
		}
		return result;
	}

	template <class T1>
	friend ostream &operator<<(ostream &ustream, LinkedListParent<T1> &obj);
	template <class T1>
	friend istream &operator>>(istream &ustream, LinkedListParent<T1> &obj);
};

template <class T>
ostream &operator<<(ostream &ustream, LinkedListParent<T> &obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T> *current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T> *current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
}

template <class T>
istream &operator>>(istream &ustream, LinkedListParent<T> &obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
    IteratedLinkedList() : LinkedListParent<T>() {}
    virtual ~IteratedLinkedList() {}

    class iterator : public std::iterator<std::input_iterator_tag, T>
    {
    private:
        //текущий элемент
        Element<T> *ptr;

    protected:
        Element<T> *getPtr()
        {
            return ptr;
        }

    public:
        //конструкторы
        iterator() { ptr = NULL; }
        iterator(Element<T> *p) { ptr = p; }
        iterator(const iterator &it) { ptr = it.ptr; }

        //методы работы с итераторами
        //присваивание
        iterator &operator=(const iterator &it)
        {
            ptr = it.ptr;
            return *this;
        }
        iterator &operator=(Element<T> *p)
        {
            ptr = p;
            return *this;
        }

        //проверка итераторов на равенство
        bool operator!=(iterator const &other) { return ptr != other.ptr; }
        bool operator==(iterator const &other) { return ptr == other.ptr; }
        //получить значение
        Element<T> &operator*()
        {
            if (ptr == NULL)
                throw invalid_argument("NULL pointer!");
            return *ptr;
        }
        //перемещение с помощью итераторов
        iterator &operator++()
        {
            if (ptr != NULL && ptr->getNext() != NULL)
                ptr = ptr->getNext();
            return *this;
        }
        iterator &operator++(int v)
        {
            if (ptr != NULL && ptr->getNext() != NULL)
                ptr = ptr->getNext();
            return *this;
        }
        iterator &operator--()
        {
            if (ptr != NULL && ptr->getPrevious() != NULL)
                ptr = ptr->getPrevious();
            return *this;
        }
        iterator &operator--(int v)
        {
            if (ptr != NULL && ptr->getPrevious() != NULL)
                ptr = ptr->getPrevious();
            return *this;
        }
    };

    iterator begin()
    {
        iterator it = LinkedListParent<T>::head;
        return it;
    }
    iterator end()
    {
        iterator it = LinkedListParent<T>::tail;
        return it;
    }

    template <class T1>
    friend ostream &operator<<(ostream &ustream, IteratedLinkedList<T1> &obj);
};

template <class T>
ostream &operator<<(ostream &ustream, IteratedLinkedList<T> &obj)
{
    if (typeid(ustream).name() == typeid(ofstream).name())
    {
        ustream << obj.num << "\n";
        auto p = obj.begin();
        while (true)
        {
            ustream << *p << " ";
            if (p == obj.end())
                break;
            ++p;
        }
        return ustream;
    }

    ustream << "\nLength: " << obj.num << "\n";
    int i = 0;
    for (auto p = obj.begin();; i++)
    {
        ustream << "arr[" << i << "] = " << *p << "\n";
        if (p == obj.end())
            break;
        ++p;
    }

    return ustream;
}

template <class T>
class Queue : public IteratedLinkedList<T>
{
public:
    Queue() : IteratedLinkedList<T>() {}
    virtual ~Queue() {}

    virtual Element<T> *push(T value) // Итератор использовать почти не нужно, ведь требуется менять tail
    {
        Element<T> *el = new Element<T>(value);
        auto pEnd = IteratedLinkedList<T>::end();

        if (pEnd == NULL)
        {
            LinkedListParent<T>::head = el;
        }
        else
        {
            LinkedListParent<T>::tail->setNext(el);
            el->setPrevious(LinkedListParent<T>::tail);
        }

        LinkedListParent<T>::tail = el;
        LinkedListParent<T>::num++;
        return el;
    }

    virtual Element<T> *pop()
    {
        auto pBegin = IteratedLinkedList<T>::begin();
        auto pEnd = IteratedLinkedList<T>::end();

        if (pBegin == NULL)
            return NULL;
        Element<T> *result = LinkedListParent<T>::head;

        if (pBegin == pEnd)
        {
            LinkedListParent<T>::head = NULL;
            LinkedListParent<T>::tail = NULL;
        }
        else
        {
            LinkedListParent<T>::head = LinkedListParent<T>::head->getNext();
            LinkedListParent<T>::head->setPrevious(NULL);
            result->setNext(NULL);
        }

        LinkedListParent<T>::num--;
        return result;
    }
};

template <typename T>
class SortedQueue : public Queue<T>
{
public:
    virtual Element<T> *push(T value)
    {
        auto p = IteratedLinkedList<T>::begin();
        auto pEnd = IteratedLinkedList<T>::end();
        Element<T> *elem = new Element<T>(value);

        if (p == NULL)
        {
            LinkedListParent<T>::head = elem;
            LinkedListParent<T>::tail = elem;
        }
        else if (p == pEnd)
        {
            if ((*pEnd).getValue() < value)
            {
                LinkedListParent<T>::head = elem;
                elem->setNext(LinkedListParent<T>::tail);
                LinkedListParent<T>::tail->setPrevious(elem);
            }
            else
            {
                LinkedListParent<T>::tail = elem;
                elem->setPrevious(LinkedListParent<T>::head);
                LinkedListParent<T>::head->setNext(elem);
            }
        }
        else
        {
            while (p != pEnd)
            {
                if ((*p).getValue() < value)
                    break;
                ++p;
            }

            if (p == IteratedLinkedList<T>::begin())
            {
                elem->setNext(LinkedListParent<T>::head);
                LinkedListParent<T>::head->setPrevious(elem);
                LinkedListParent<T>::head = elem;
            }
            else if (p == pEnd && (*pEnd).getValue() < value)
            {
                elem->setPrevious(LinkedListParent<T>::tail);
                LinkedListParent<T>::tail->setNext(elem);
                LinkedListParent<T>::tail = elem;
            }
            else
            {
                elem->setNext((*p).getPrevious()->getNext());
                elem->setPrevious((*p).getPrevious());
                elem->getPrevious()->setNext(elem);
                elem->getNext()->setPrevious(elem);
            }
        }

        LinkedListParent<T>::num++;

        return elem;
    }
};

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
                if (name == b.name)
                    return false;
                else
                    return name < b.name ? true : false;
            }
            else
                return year_of_present < b.year_of_present ? true : false;
        }
        else
            return count < b.count ? true : false;
    }

    friend std::ostream &operator<<(std::ostream &, const Book &);
};

std::ostream &operator<<(std::ostream &s, const Book &b)
{
    s << "\nSurname: " << b.surname << "\nName: " << b.name << "\nYear of present: " << b.year_of_present << "\nNum of pages: " << b.num_of_pages << "\nPublication type: " << b.type << "\nCirculation: " << b.count << "\n";
}

// True если тираж не меньше 2
bool cmp(Book b)
{
    return b.count >= 2;
}

int main()
{

    SortedQueue<int> Q;
    Q.push(1);
    Q.push(2);
    Q.push(3);
    cout << Q;
    cout << "\n";
    Element<int> *e1 = Q.pop();
    cout << "\nElement = " << e1->getValue();
    cout << Q;
    cout << "\nIndex in the Stack class: " << Q[1]->getValue();

    cout << Q;
    cout << "\nIterators:\n";
    auto it = Q.begin();
    while (it != Q.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << *it << " ";

    Book b1, b2, b3;
    b1.count = 3;
    b2.count = 2;
    b3.count = 1;

    SortedQueue<Book> BQ, FBQ;

    BQ.push(b1);
    BQ.push(b2);
    BQ.push(b3);

    FBQ = BQ.filter(cmp);

    cout << BQ;

    return 0;
}
