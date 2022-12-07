using namespace std;
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>

class Exception : public exception
{
protected:
	//сообщение об ошибке
	char *str;

public:
	Exception(const char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	Exception(char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	Exception()
	{
		str = NULL;
	}
	Exception(const Exception &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class IndexOutOfBoundsException : public Exception
{
protected:
	int index;

public:
	IndexOutOfBoundsException(char *s, int Index) : Exception(s)
	{
		index = Index;
	}
	IndexOutOfBoundsException(const char *s, int Index) : Exception(s)
	{
		index = Index;
	}
	IndexOutOfBoundsException(const IndexOutOfBoundsException &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "IndexOutOfBounds: " << str << "; " << what();
	}
};

class ListIsEmptyException : public Exception
{
protected:
public:
	ListIsEmptyException(char *s) : Exception(s) {}
	ListIsEmptyException(const char *s) : Exception(s) {}
	ListIsEmptyException(const ListIsEmptyException &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "ListIsEmptyException: " << str << "; " << what();
	}
};

template <class T>
class Element
{
protected:
	Element *next;
	T info;

public:
	Element(T data)
	{
		next = NULL;
		info = data;
	}

	Element(Element *Next, T data)
	{
		next = Next;
		info = data;
	}

	template <class T1>
	friend ostream &operator<<(ostream &s, Element<T1> &el);

	Element *getNext() { return next; }
	void setNext(Element *value) { next = value; }

	T &getData() { return info; }
	void setData(T value) { info = value; }
};

template <class T1>
ostream &operator<<(ostream &s, Element<T1> &el)
{
	s << el.info;
	return s;
}

template <class T>
class ForwardList
{
protected:
	Element<T> *head;

public:
	ForwardList()
	{
		head = NULL;
	}

	virtual Element<T> *pop() = 0;
	virtual Element<T> *push(T value) = 0;

	virtual T &operator[](int index) = 0;

	template <class T1>
	friend ostream &operator<<(ostream &s, ForwardList<T1> &el);

	virtual ~ForwardList()
	{
	}
};

template <class T>
class SortedList : public ForwardList<T>
{
protected:
	int length;

public:
	SortedList() : ForwardList<T>() { length = 0 }
	~SortedList()
	{
		Element<T> *p = ForwardList<T>::head;
		Element<T> *temp = p;
		for (; p != NULL; p = temp)
		{
			temp = p->getNext();
			delete p;
		}
	}

	Element<T> *push(T value)
	{
		Element<T> *p = ForwardList<T>::head;
		Element<T> *new_el = new Element<T>(value);
		if (p == NULL)
		{
			ForwardList<T>::head = new_el;
			new_el->setNext(new_el);
		}
		else
		{
			if (value <= p->getData())
			{
				new_el->setNext(p);
				ForwardList<T>::head = new_el;
			}
			else
			{
				while (value > p->getData())
				{
					p = p->getNext();
					if (p == ForwardList<T>::head)
					{
						break;
					}
				}
				Element<T> *predessesor = this->predessesor(p);
				predessesor->setNext(new_el);
				new_el->setNext(p);
			}
		}
		length++;
		return new_el;
	}

	Element<T> *pop()
	{
		if (ForwardList<T>::head == NULL)
		{
			throw ListIsEmptyException("Error pop, list is empty");
		}
		Element<T> *p = ForwardList<T>::head;
		Element<T> *res = predessesor(p);
		predessesor(res)->setNext(p);
		length--;
		return res;
	}

	Element<T> *find(T value)
	{
		Element<T> *p = ForwardList<T>::head;
		while (p->getData() != value)
		{
			p = p->getNext();
		}
		return p;
	}

	Element<T> *predessesor(Element<T> *current)
	{
		Element<T> *p = ForwardList<T>::head;
		Element<T> *predessesor = p;
		while (p != current)
		{
			predessesor = p;
			p = p->getNext();
		}
		return predessesor;
	}

	T &operator[](int index)
	{
		if (index < 0 || index >= length)
		{
			throw IndexOutOfBoundsException("Index out of boubds", index);
		}
		Element<T> *p = ForwardList<T>::head;
		for (int i = 0; i <= index; i++)
		{
			p = p->getNext();
		}
		return p->getData();
	}

	template <class T1>
	friend ostream &operator<<(ostream &s, SortedList<T1> &l);
};

template <class T>
ostream &operator<<(ostream &s, SortedList<T> &l)
{
	Element<T> *p = l.ForwardList<T>::head;
	s << l.predessesor(p)->getData() << " ";
	p = l.predessesor(p);
	while (p != l.ForwardList<T>::head)
	{
		cout << "Done";
		s << l.predessesor(p)->getData() << " ";
	}
	return s;
}

int main()
{
	try
	{
		SortedList<int> l;
		for (int i = 10; i > 0; i--)
		{
			l.push(i);
		}
		Element<int> *p = l.find(3);
		cout << *l.predessesor(p);
	}
	catch(IndexOutOfBoundsException &e)
	{
		e.print();
	}
	catch(ListIsEmptyException &e)
	{
		e.print();
	}
	catch(Exception &e)
	{
		e.print();
	}
	return 0;
}
