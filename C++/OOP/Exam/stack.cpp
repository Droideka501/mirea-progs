using namespace std;
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>

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
class Stack : public ForwardList<T>
{
protected:
	int length;

public:
	Stack() : ForwardList<T>() { length = 0; }
	~Stack()
	{
		Element<T> *p = ForwardList<T>::head;
		Element<T> *temp = p;
		for (; p != NULL; p = temp)
		{
			temp = p->getNext();
			delete p;
		}
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

	Element<T> *push(T value)
	{
		Element<T> *new_el = new Element<T>(value);
		Element<T> *p = ForwardList<T>::head;
		if (p == NULL)
		{
			ForwardList<T>::head = new_el;
		}
		else
		{
			while (p->getNext() != NULL)
			{
				p++;
			}

			p->setNext(new_el);
		}
		length++;
		return new_el;
	}

	Element<T> *pop()
	{
		Element<T> *p = ForwardList<T>::head;
		while (p->getNext() != NULL)
		{
			p++;
		}
		Element<T> *res = p;
		predessesor(p)->setNext(NULL);
		length--;
		return res;
	}

	Element<T> *find(T value)
	{
		Element<T> *p = ForwardList<T>::head;
		while (p->getData() != value)
		{
			p = p->getNext();
			if(p == NULL)
			{
				return NULL;
			}
			
		}
		return p;
	}

	T &operator[](int index)
	{
		Element<T> *p = ForwardList<T>::head;
		for (int i = 0; i <= index; i++)
		{
			p = p->getNext();
		}
		return p->getData();
	}

	template <class T1>
	friend ostream &operator<<(ostream &s, Stack<T1> &l);
};

template <class T>
ostream &operator<<(ostream &s, Stack<T> &l)
{
	Element<T> *p = l.ForwardList<T>::head;
	s << l.predessesor(p)->getData() << " ";
	p = l.predessesor(p);
	while (p != l.ForwardList<T>::head)
	{
		s << l.predessesor(p)->getData() << " ";
	}
	return s;
}

int main()
{

	Stack<int> l;
	for (int i = 10; i > 0; i--)
	{

		l.push(i);
	}

	Element<int> *p = l.find(3);

	cout << *l.predessesor(p);

	return 0;
}
