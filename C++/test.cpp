using namespace std;

#include <typeinfo>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>

ostream& my_manip(ostream& s)
{
	s.setf(ios::showpoint);
	s.precision(2);
	return s;
}

template<class T>
class Element
{
protected:
	Element* next;
	Element* prev;
	T info;
public:


	Element(T data)
	{
		next = prev = NULL;
		info = data;
	}

	Element(Element* Next, Element* Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}

	Element(const Element& el)
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}

	Element<T>* getNext() {
		return next;
	}

	void setNext(Element* Next) {
		next = Next;
	}

	Element<T>* getPrev() {
		return prev;
	}

	void setPrev(Element* Prev) {
		prev = Prev;
	}

	T getInfo() {
		return info;
	}

	void setInfo(T Info) {
		info = Info;
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, Element<T1>& el);

};

template <class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << " ";
	my_manip(s);
	s << el.info;
	return s;
}

template<class T>
class LinkedList
{
protected:

	Element<T>* head;
	Element<T>* tail;
	int count;

public:

	LinkedList()
	{
		cout << "\nLinkedList class constructor";
		head = tail = NULL;
		count = 0;
	}

	LinkedList(T* arr, int len)
	{
		Element<T>* current = new Element<T>(arr[0]);
		head = current;
		for (int i = 1; i < len; i++)
		{
			current = current->getNext();
			current = new Element<T>(arr[i]);
		}
		tail = current;
		count = len;
	}

	virtual ~LinkedList()
	{
		cout << "\nLinkedList class destructor";
		if (head != NULL)
		{
			Element<T>* current = head;
			Element<T>* temp = head->getNext();
			for (; current != tail; current = temp, temp = temp->getNext())
				delete current;
		}
		head = NULL; tail = NULL;
	}

	virtual Element<T>* operator[](int index) = 0;
	virtual Element<T>* push(T value) = 0;
	virtual Element<T>* pop() = 0;
	virtual Element<T>* insert(T value, Element<T>* predecessor = NULL) = 0;
	virtual Element<T>* find(T value) = 0;
	virtual Element<T>* find(T value, Element<T>* el) = 0;
	virtual Element<T>* remove(T value) = 0;
	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest) = 0;
	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest, Element<T>* cur) = 0;
	virtual void filter(T, LinkedList<T>* dest, bool more) = 0;
	virtual void filter(T, LinkedList<T>* dest, Element<T>* cur, bool more) = 0;

	bool isEmpty() { return (LinkedList<T>::count == 0); }

	virtual void save(string fileName)
	{
		ofstream fout(fileName);
		if (fout.is_open())
		{
			fout << count << "\n";
			Element<T>* pom = head;
			T info;
			for (int i = 0; i < count; i++)
			{
				info = pom->getInfo();
				fout << info << "\n";
				pom = pom->getNext();
			}
			fout.close();
		}
	}
	virtual void load(string fileName)
	{
		ifstream fin;
		fin.open(fileName);
		if (fin.is_open())
		{
			int ct;
			fin >> ct;

			if (ct != count)
			{
				count = 0;
				if (head != NULL)
				{
					Element<T>* current = head;
					Element<T>* temp = head->getNext();
					for (; current != tail; current = temp, temp = temp->getNext())
						delete current;
				}
				head = NULL; tail = NULL;
				T val;
				for (int i = 0; i < ct; i++)
				{
					fin >> val;
					push(val);
				}
			}
			else {
				Element<T>* pom = head;
				T val;
				for (int i = 0; i < count; i++)
				{
					fin >> val;
					pom->setInfo(val);
					pom = pom->getNext();
				}
			}
			fin.close();
		}
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
	template <class T1>
	friend istream& operator>>(istream& s, LinkedList<T1>& el);
};

template<class T1>
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
	Element<T1>* current;
	s << "\n{";
	for (current = el.head; current != NULL; current = current->getNext())
		s << *current << "; ";
	s << "}";
	return s;
}

template <class T1>
istream& operator>>(istream& s, LinkedList<T1>& el)
{
	cout << "\nList size is: " << el.count << ". Enter " << el.count << " values: ";
	Element<T1>* p = el.head;
	T1 v;
	for (int i = 0; i < el.count; i++)
	{
		s >> v;
		p->setInfo(v);
		p = p->getNext();
	}
	return s;
}

// Класс Односвязный Стек
template<class T>
class Stack : public LinkedList<T>
{
public:
	Stack() : LinkedList<T>()
	{
		cout << "\nStack class constructor";
	}

	virtual ~Stack()
	{
		cout << "\nStack class destructor";
	}

	virtual Element<T>* operator[](int index)
	{
		Element<T>* current = LinkedList<T>::head;

		for (int i = 0;
			current != NULL && i < index;
			current = current->getNext(), i++);

		return current;
	}

	//Добавление элемента в конец списка
	virtual Element<T>* push(T value)
	{
		if (LinkedList<T>::head == NULL)
		{
			LinkedList<T>::tail = new Element<T>(value);
			LinkedList<T>::head = LinkedList<T>::tail;
		}
		else
		{
			LinkedList<T>::tail->setNext(new Element<T>(value));
			LinkedList<T>::tail = LinkedList<T>::tail->getNext();
		}
		LinkedList<T>::count++;
		return LinkedList<T>::tail;
	}

	//Удаление элемента из начала списка
	virtual Element<T>* pop()
	{
		if (LinkedList<T>::tail == NULL)
			return NULL;
		Element<T>* res = LinkedList<T>::tail;
		if (LinkedList<T>::head == LinkedList<T>::tail)
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
		else
		{
			Element<T>* current;
			for (current = LinkedList<T>::head;
				current->getNext() != LinkedList<T>::tail; current = current->getNext());
			LinkedList<T>::tail = current;
			LinkedList<T>::tail->setNext(NULL);
		}
		LinkedList<T>::count--;
		return res;
	}

	//Вставка нового элемента в произвольное место списка
	virtual Element<T>* insert(T value, Element<T>* predecessor = NULL)
	{
		if (LinkedList<T>::head == NULL)
		{
			return push(value);
		}
		if (predecessor == NULL)
		{
			Element<T>* newElem = new Element<T>(value);
			newElem->setNext(LinkedList<T>::head);
			LinkedList<T>::head = newElem;
			LinkedList<T>::count++;
			return newElem;
		}
		Element<T>* newElem = new Element<T>(value);
		Element<T>* successor = predecessor->getNext();
		predecessor->setNext(newElem);
		newElem->setNext(successor);
		if (predecessor == LinkedList<T>::tail)
			LinkedList<T>::tail = LinkedList<T>::tail->getNext();
		LinkedList<T>::count++;
		return newElem;
	}

	virtual Element<T>* find(T value) {
		Element<T>* p = LinkedList<T>::head;
		while (p != NULL) {
			if (p->getInfo() == value)
				return p;
			p = p->getNext();
		}
		return NULL;
	}

	virtual Element<T>* find(T value, Element<T>* el)
	{
		if (el->getInfo() == value || el == NULL)
			return el;
		return find(value, el->getNext());
	}

	//Удаление элемента из любого места списка
	virtual Element<T>* remove(T value)
	{
		Element<T>* p = LinkedList<T>::head;
		if (p == NULL) return p;
		if (p->getInfo() == value)
		{
			LinkedList<T>::head = p->getNext();
			p->setNext(NULL);
			LinkedList<T>::count--;
			return p;
		}
		for (; p->getNext() != NULL && p->getNext()->getInfo() != value; p = p->getNext());
		if (p->getNext()->getInfo() == value)
		{
			Element<T>* res = p->getNext();
			p->setNext(res->getNext());
			res->setNext(NULL);
			LinkedList<T>::count--;
			return res;
		}
		return NULL;
	}

	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest)
	{
		for (Element<T>* cur = LinkedList<T>::head; cur != NULL; cur = cur->getNext())
			if (cmp(cur->getInfo()))
				dest->push(cur->getInfo());
	}

	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest, Element<T>* cur)
	{
		if (cur == NULL) return;
		if (cmp(cur->getInfo()))
			dest->push(cur->getInfo());
		return filter(cmp, dest, cur->getNext());
	}

	virtual void filter(T check, LinkedList<T>* dest, bool more)
	{
		for (Element<T>* cur = LinkedList<T>::head; cur != NULL; cur = cur->getNext())
		{
			if (cur->getInfo() > check && more)
				dest->push(cur->getInfo());
			if (cur->getInfo() < check && !more)
				dest->push(cur->getInfo());
		}
	}

	virtual void filter(T check, LinkedList<T>* dest, Element<T>* cur, bool more)
	{
		if (cur == NULL) return;
		if (cur->getInfo() > check && more)
			dest->push(cur->getInfo());
		if (cur->getInfo() < check && !more)
			dest->push(cur->getInfo());
		return filter(check, dest, cur->getNext(), more);
	}
};

template<class T>
class DoubleSidedStack : public Stack<T>
{
public:
	DoubleSidedStack() : Stack<T>()
	{
		cout << "\nDoubleSidedStack class constructor";
	}
	virtual ~DoubleSidedStack()
	{
		cout << "\nDoubleSidedStack class destructor";
	}

	virtual Element<T>* operator[](int index)
	{
		Element<T>* current;
		if (index < LinkedList<T>::count / 2)
		{
			current = LinkedList<T>::head;
			for (int i = 0;
				current != NULL && i < index;
				current = current->getNext(), i++);
			return current;
		}
		else
		{
			current = LinkedList<T>::tail;
			for (int i = LinkedList<T>::count - 1;
				current != NULL && i > index;
				current = current->getPrev(), i--);
			return current;
		}
		return current;
	}

	//Добавление элемента в конец списка
	virtual Element<T>* push(T value)
	{
		Element<T>* tail_predecessor_push = LinkedList<T>::tail;
		Element<T>* res = Stack<T>::push(value);
		res->setPrev(tail_predecessor_push);
		return res;
	}

	//Удаление элемента из начала списка
	virtual Element<T>* pop()
	{
		if (LinkedList<T>::tail == LinkedList<T>::head)
			return Stack<T>::pop();
		Element<T>* res = LinkedList<T>::tail;
		LinkedList<T>::tail = LinkedList<T>::tail->getPrev();
		LinkedList<T>::tail->setNext(NULL);
		res->setPrev(NULL);
		LinkedList<T>::count--;
		return res;
	}

	//Вставка нового элемента в произвольное место списка
	virtual Element<T>* insert(T value, Element<T>* predecessor = NULL)
	{
		if (LinkedList<T>::head == NULL)
		{
			return push(value);
		}
		if (predecessor == NULL)
		{
			Stack<T>::insert(value);
			LinkedList<T>::head->getNext()->setPrev(LinkedList<T>::head);
			return LinkedList<T>::head;
		}
		Element<T>* successor = predecessor->getNext();
		Element<T>* inserted = Stack<T>::insert(value, predecessor);
		if (successor != NULL) successor->setPrev(inserted);
		inserted->setPrev(predecessor);
		return inserted;
	}

	//Удаление элемента из любого места списка
	virtual Element<T>* remove(T value)
	{
		Element<T>* p = LinkedList<T>::head;
		if (p == NULL) return p;
		if (p->getInfo() == value)
		{
			Stack<T>::remove(value);
			LinkedList<T>::head->setPrev(NULL);
			if (LinkedList<T>::count == 1)
				LinkedList<T>::tail->setPrev(NULL);
			return p;
		}
		for (; p->getNext() != NULL && p->getNext()->getInfo() != value; p = p->getNext());
		if (p->getNext()->getInfo() == value)
		{
			Element<T>* res = p->getNext();
			p->setNext(res->getNext());
			if (res->getNext() != NULL) res->getNext()->setPrev(p);
			if (res->getNext() == NULL) LinkedList<T>::tail = p;
			res->setNext(NULL);
			res->setPrev(NULL);
			LinkedList<T>::count--;
			return res;
		}
		return NULL;
	}

	// find и filter ищет по значению, поэтому нет смысла переопределять его для DoubleSidedStack
}; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// lfdfmsdklmkvnankdg'kjgagjagjakgja'

template <class T>
class GovStack : protected DoubleSidedStack<T>
{
public:
	GovStack() : DoubleSidedStack<T>() {}
	virtual ~GovStack() {}

	virtual Element<T>* operator[](int index)
	{
		return DoubleSidedStack<T>::operator[](index);
	}

	//добавление в начало
	virtual Element<T>* push(T value) {
		Element<T>* p = new Element<T>(value);
		if (LinkedList<T>::count == 0)
		{
			LinkedList<T>::head = LinkedList<T>::tail = p;
			LinkedList<T>::count++;
			return p;
		}
		p->setNext(LinkedList<T>::head);
		if (p->getNext() != NULL) LinkedList<T>::head->setPrev(p);
		LinkedList<T>::head = p;
		LinkedList<T>::count++;
		return p;
	}

	//Удаление с конца
	virtual Element<T>* pop()
	{
		if (LinkedList<T>::count == 0) return NULL;
		Element<T>* res = LinkedList<T>::tail;
		if (LinkedList<T>::count == 1)
		{
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
		}
		res->getPrev()->setNext(NULL);
		LinkedList<T>::tail = res->getPrev();
		res->setPrev(NULL);
		LinkedList<T>::count--;
		return res;
	}

	virtual Element<T>* insert(T value, Element<T>* predecessor = NULL) {
		return DoubleSidedStack<T>::insert(value, predecessor);
	}

	virtual Element<T>* remove(T value) {
		return DoubleSidedStack<T>::remove(value);
	}

	//поиск по численности населения
	virtual Element<T>* find(T value)
	{
		Element<T>* p = LinkedList<T>::head;
		for (; p->getInfo().name != value.name && p != NULL; p = p->getNext());
		return p;
	}

	virtual Element<T>* find(T value, Element<T>* el)
	{
		if (el->getInfo().name == value.name || el == NULL)
			return el;
		return find(value, el->getNext());
	}

	Element<T>* find(string Name)
	{
		Element<T>* p = LinkedList<T>::head;
		for (; p->getInfo().name != Name && p != NULL; p = p->getNext());
		return p;
	}

	Element<T>* find(string Name, Element<T>* el)
	{
		if (el->getInfo().name == Name || el == NULL)
			return el;
		return find(Name, el->getNext());
	}

	//фильтр по языку

	virtual void filter(T check, LinkedList<T>* dest, bool more = false)
	{
		for (Element<T>* cur = LinkedList<T>::head; cur != NULL; cur = cur->getNext())
		{
			if (cur->getInfo().square > check.square && more)
				dest->push(cur->getInfo());
			if (cur->getInfo().square < check.square && !more)
				dest->push(cur->getInfo());
		}
	}

	virtual void filter(T check, LinkedList<T>* dest, Element<T>* cur, bool more = false)
	{
		if (cur == NULL) return;
		if (cur->getInfo().square > check.square && more)
			dest->push(cur->getInfo());
		if (cur->getInfo().square < check.square && !more)
			dest->push(cur->getInfo());
		return filter(check, dest, cur->getNext(), more);
	}

	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest)
	{
		for (Element<T>* cur = LinkedList<T>::head; cur != NULL; cur = cur->getNext())
			if (cmp(cur->getInfo()))
				dest->push(cur->getInfo());
	}

	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest, Element<T>* cur)
	{
		if (cur == NULL) return;
		if (cmp(cur->getInfo()))
			dest->push(cur->getInfo());
		return filter(cmp, dest, cur->getNext());
	}

	virtual void save(string fileName)
	{
		ofstream fout(fileName);
		if (fout.is_open())
		{
			fout << LinkedList<T>::count << "\n";
			Element<T>* p = LinkedList<T>::head;
			T info;
			for (int i = 0; i < LinkedList<T>::count; i++)
			{
				info = p->getInfo();
				fout << info << "\n";
				p = p->getNext();
			}
			fout.close();
		}
	}
	virtual void load(string fileName)
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
					Element<T>* current = LinkedList<T>::head;
					Element<T>* temp = LinkedList<T>::head->getNext();
					for (; current != LinkedList<T>::tail; current = temp, temp = temp->getNext())
						delete current;
				}
				LinkedList<T>::head = NULL; LinkedList<T>::tail = NULL;
				T v;
				for (int i = 0; i < ct; i++)
				{
					fin >> v;
					push(v);
				}
			}
			else {
				Element<T>* p = LinkedList<T>::head;
				T v;
				for (int i = 0; i < LinkedList<T>::count; i++)
				{
					fin >> v;
					p->setInfo(v);
					p = p->getNext();
				}
			}
			fin.close();
		}
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, GovStack<T1>& el);
	template <class T1>
	friend istream& operator>>(istream& s, GovStack<T1>& el);
};

template<class T1>
ostream& operator<<(ostream& s, GovStack<T1>& el)
{
	Element<T1>* cur;
	s << "\n{";
	for (cur = el.head; cur->getNext() != NULL; cur = cur->getNext())
		s << *cur << ", ";
	s << *cur;
	s << "\n}";
	return s;
}

template <class T1>
istream& operator>>(istream& s, GovStack<T1>& el)
{
	cout << "\nList size is: " << el.count << ". Enter " << el.count << " values: ";
	Element<T1>* p = el.head;
	T1 v;
	for (int i = 0; i < el.count; i++)
	{
		s >> v;
		p->setInfo(v);
		p = p->getNext();
	}
	return s;
}




class Government
{
public:
	string name, capital, language;
	int square, population;

	Government(string Name = "unknown", string Capital = "unknown",
		string Language = "unknown", int Square = 0, int Population = 0)
	{
		name = Name;
		capital = Capital;
		language = Language;
		square = Square;
		population = Population;
	}

	~Government() {}

	bool operator==(Government g) {
		return name == g.name && capital == g.capital && language == g.language && population == g.population && square == g.square;
	}

	bool operator !=(Government g) {
		return name != g.name || capital != g.capital || language != g.language || population != g.population || square != g.square;
	}

	bool operator>(Government g) {
		return square > g.square;
	}

	bool operator<(Government g) {
		return square < g.square;
	}

	friend ostream& operator<<(ostream& s, Government& v);
	friend istream& operator>>(istream& s, Government& v);
};

ostream& operator<<(ostream& s, Government& v) {
	if (typeid(s) == typeid(ifstream))
	{
		s << v.name << " " << v.capital << " " << v.language << " " << v.square << " "
			<< v.population << '\n';
	}
	else
	{
		s << "( " << v.name << ", " << v.capital << ", " << v.language << ", " << v.square << ", "
			<< v.population << " )" << '\n';
	}
	return s;
}

istream& operator>>(istream& s, Government& v) {
	if (typeid(s) == typeid(ifstream)) {
		s >> v.name >> v.capital >> v.language >> v.square >> v.population;
	}
	else {
		cout << "\nName (string): ";
		s >> v.name;
		cout << "\nCapital (string): ";
		s >> v.capital;
		cout << "\nLanguage (string): ";
		s >> v.language;
		cout << "\nSquare (int): ";
		s >> v.square;
		cout << "\nPopulation (double); ";
		s >> v.population;
	}
	return s;
}

bool f(int s) { return s > 4; };
bool gf(Government c) { return c.square > 9500000; }
