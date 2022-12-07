#include <iostream>

using namespace std;

template <class K, class V>
class Node
{
protected:
	K key;
	V data;

	Node *left;
	Node *right;
	Node *parent;

	int height;

public:
	virtual void setKey(K key) { this->key = key; }

	virtual K getKey() { return key; }

	virtual void setData(V d) { data = d; }

	virtual V getData() { return data; }

	int getHeight() { return height; }

	virtual Node *getLeft() { return left; }

	virtual Node *getRight() { return right; }

	virtual Node *getParent() { return parent; }

	virtual void setLeft(Node *N) { left = N; }

	virtual void setRight(Node *N) { right = N; }

	virtual void setParent(Node *N) { parent = N; }

	Node<K, V>(K key, V data)
	{
		this->key = key;
		this->data = data;
		left = right = parent = nullptr;
		height = 1;
	}

	Node<K, V>()
	{
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		height = 1;
	}

	virtual void print()
	{
		cout << "\n"
			 << key << " -> " << data;
	}

	virtual void setHeight(int h)
	{
		height = h;
	}

	template <class K1, class V1>
	friend ostream &operator<<(ostream &stream, Node<K1, V1> &N);
};

template <class K, class V>
ostream &operator<<(ostream &stream, Node<K, V> &N)
{
	stream << "\nNode: " << N.key << " -> " << N.data << ", height: " << N.height;
	return stream;
}

template <class K, class V>
void print(Node<K, V> *N)
{
	auto temp = N->getData();
	cout << "\nNode: " << N->getKey() << " -> " << temp << ", height: " << N->getHeight();
}

// -------------------------------------------- Tree --------------------------------------------

template <class K, class V>
class Tree
{
protected:
	Node<K, V> *root;

	virtual Node<K, V> *push_R(Node<K, V> *N, Node<K, V> *Current)
	{
		if (N == nullptr)
			return nullptr;
		if (root == nullptr)
		{
			root = N;
			return N;
		}

		if (Current->getKey() > N->getKey())
		{
			//идем влево
			if (Current->getLeft() != nullptr)
				Current->setLeft(push_R(N, Current->getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getKey() < N->getKey())
		{
			//идем вправо
			if (Current->getRight() != nullptr)
				Current->setRight(push_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getKey() == N->getKey())
			//нашли совпадение
			;
		//для несбалансированного дерева поиска
		return Current;
	}

	virtual Node<K, V> *Find_R(K key, Node<K, V> *Current)
	{
		if (Current == nullptr)
			return nullptr;

		if (Current->getKey() == key)
			return Current;

		if (Current->getKey() > key)
			return Find_R(key, Current->getLeft());

		return Find_R(key, Current->getRight());
	}

	virtual Node<K, V> *Remove_R(K key, Node<K, V> *N)
	{
		Node<K, V> *temp;
		if (N == nullptr)
			return nullptr;
		if (key < N->getKey())
			N->setLeft(Remove_R(key, N->getLeft()));
		else if (key > N->getKey())
			N->setRight(Remove_R(key, N->getRight()));
		else if (N->getLeft() && N->getRight())
		{
			temp = Tree<K, V>::Min(N->getRight());
			N->setRight(Remove_R(temp->getKey(), N->getRight()));
			temp->setLeft(N->getLeft());
			temp->setRight(N->getRight());
			if (N->getLeft() != nullptr)
			{
				N->getLeft()->setParent(temp);
				N->setLeft(nullptr);
			}
			if (N->getRight() != nullptr)
			{
				N->getRight()->setParent(temp);
				N->setRight(nullptr);
			}
			if (N == Tree<K, V>::root)
				Tree<K, V>::root = temp;
		}
		else
		{
			temp = N;
			if (N->getLeft() == nullptr)
			{
				N = N->getRight();
				if (N != nullptr)
					N->setParent(temp->getParent());
				temp->setRight(nullptr);
				temp->setParent(nullptr);
			}
			else if (N->getRight() == nullptr)
			{
				N = N->getLeft();
				if (N != nullptr)
					N->setParent(temp->getParent());
				temp->setLeft(nullptr);
				temp->setParent(nullptr);
			}
			if (temp == Tree<K, V>::root)
				Tree<K, V>::root = N;
			temp->setParent(nullptr);
		}

		return N;
	}

public:
	virtual Node<K, V> *getRoot() { return root; }

	Tree<K, V>() { root = nullptr; }

	virtual Node<K, V> *push(Node<K, V> *N)
	{
		return push_R(N, Tree<K, V>::root);
	}

	virtual Node<K, V> *push(K key, V data)
	{
		auto *N = new Node<K, V>;
		N->setKey(key);
		N->setData(data);
		return push_R(N, Tree<K, V>::root);
	}

	virtual Node<K, V> *Find(K key)
	{
		return Find_R(key, root);
	}

	virtual Node<K, V> *Remove(K key)
	{
		Node<K, V> *result = Find(key);
		Remove_R(key, root);
		return result;
	}

	virtual Node<K, V> *Min(Node<K, V> *Current = nullptr)
	{
		if (root == nullptr)
			return nullptr;

		if (Current == nullptr)
			Current = root;
		while (Current->getLeft() != nullptr)
			Current = Current->getLeft();

		return Current;
	}

	virtual Node<K, V> *Max(Node<K, V> *Current = nullptr)
	{
		if (root == nullptr)
			return nullptr;

		if (Current == nullptr)
			Current = root;
		while (Current->getRight() != nullptr)
			Current = Current->getRight();

		return Current;
	}

	virtual void PreOrder(Node<K, V> *N, void (*f)(Node<K, V> *))
	{
		if (N != nullptr)
			f(N);
		if (N != nullptr && N->getLeft() != nullptr)
			PreOrder(N->getLeft(), f);
		if (N != nullptr && N->getRight() != nullptr)
			PreOrder(N->getRight(), f);
	}

	virtual void InOrder(Node<K, V> *N, void (*f)(Node<K, V> *))
	{
		if (N != nullptr && N->getLeft() != nullptr)
			InOrder(N->getLeft(), f);
		if (N != nullptr)
			f(N);
		if (N != nullptr && N->getRight() != nullptr)
			InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<K, V> *N, void (*f)(Node<K, V> *))
	{
		if (N != nullptr && N->getLeft() != nullptr)
			PostOrder(N->getLeft(), f);
		if (N != nullptr && N->getRight() != nullptr)
			PostOrder(N->getRight(), f);
		if (N != nullptr)
			f(N);
	}
};

// -------------------------------------------- IteratedTree --------------------------------------------

template <class K, class V>
class IteratedTree : public Tree<K, V>
{
public:
	IteratedTree<K, V>() : Tree<K, V>() {}

	class iterator : public std::iterator<std::input_iterator_tag, V>
	{
	public:
		iterator() { ptr = nullptr; }

		iterator(Node<K, V> *p) { ptr = p; }

		iterator(const iterator &it) { ptr = it.ptr; }

		iterator &operator=(const iterator &it)
		{
			ptr = it.ptr;
			return *this;
		}

		iterator &operator=(Node<K, V> *p)
		{
			ptr = p;
			return *this;
		}

		bool operator!=(iterator const &other) const
		{
			return other.ptr != ptr;
		}

		bool operator==(iterator const &other) const
		{
			return other.ptr == ptr;
		}

		Node<K, V> &operator*()
		{
			if (ptr == nullptr)
				throw invalid_argument("nullptr pointer!");
			return *ptr;
		}

		virtual Node<K, V> *Min(Node<K, V> *Current = nullptr)
		{
			if (Current == nullptr)
				return nullptr;
			while (Current->getLeft() != nullptr)
				Current = Current->getLeft();

			return Current;
		}

		virtual Node<K, V> *Max(Node<K, V> *Current = nullptr)
		{
			if (Current == nullptr)
				return nullptr;
			while (Current->getRight() != nullptr)
				Current = Current->getRight();

			return Current;
		}

		iterator &operator++()
		{
			if (ptr == nullptr)
			{
				throw invalid_argument("nullptr pointer!");
			}
			if (ptr->getRight() != nullptr)
			{
				ptr = Min(ptr->getRight());
			}
			else
			{
				if (ptr->getParent() == nullptr)
					return *this;

				Node<K, V> *p = ptr->getParent();
				while (p->getKey() < ptr->getKey() && p->getParent() != nullptr)
					p = p->getParent();

				if (p->getKey() > ptr->getKey())
					ptr = p;
			}
			return *this;
		}

		iterator &operator++(int v)
		{
			return operator++();
		}

		iterator &operator--()
		{
			if (ptr == nullptr)
			{
				throw invalid_argument("null pointer!");
			}

			if (ptr->getLeft() != nullptr)
			{
				ptr = Max(ptr->getLeft());
			}
			else
			{
				if (ptr->getParent() == nullptr)
					return *this;

				Node<K, V> *p = ptr->getParent();
				while (p->getKey() > ptr->getKey() && p->getParent() != nullptr)
					p = p->getParent();

				if (p->getKey() < ptr->getKey())
					ptr = p;
			}
			return *this;
		}

		iterator &operator--(int v)
		{
			return operator--();
		}

	private:
		Node<K, V> *ptr;
	};

	iterator begin()
	{
		iterator b = Tree<K, V>::Min();
		return b;
	}

	iterator end()
	{
		iterator e = Tree<K, V>::Max();
		return e;
	}
};

// -------------------------------------------- AVL_Tree --------------------------------------------

template <class K, class V>
class AVL_Tree : public IteratedTree<K, V>
{
protected:
	int bfactor(Node<K, V> *p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != nullptr)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != nullptr)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	void fixHeight(Node<K, V> *p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != nullptr)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != nullptr)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	Node<K, V> *RotateRight(Node<K, V> *p)
	{
		Node<K, V> *q = p->getLeft();

		p->setLeft(q->getRight());
		q->setRight(p);

		if (p != Tree<K, V>::root)
		{
			if (p->getParent()->getLeft() == p)
				p->getParent()->setLeft(q);
			else
				p->getParent()->setRight(q);
		}
		else
			Tree<K, V>::root = q;

		q->setParent(p->getParent());
		p->setParent(q);
		if (p->getLeft() != nullptr)
			p->getLeft()->setParent(p);

		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<K, V> *RotateLeft(Node<K, V> *q)
	{
		Node<K, V> *p = q->getRight();

		q->setRight(p->getLeft());
		p->setLeft(q);

		if (q != Tree<K, V>::root)
		{
			if (q->getParent()->getLeft() == q)
				q->getParent()->setLeft(p);
			else
				q->getParent()->setRight(p);
		}
		else
			Tree<K, V>::root = p;

		p->setParent(q->getParent());
		q->setParent(p);
		if (q->getRight() != nullptr)
			q->getRight()->setParent(q);

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	Node<K, V> *Balance(Node<K, V> *p)
	{
		if (p == nullptr)
			return nullptr;
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->getRight()) < 0)
				RotateRight(p->getRight());
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->getLeft()) > 0)
				RotateLeft(p->getLeft());
			return RotateRight(p);
		}

		return p;
	}

	virtual Node<K, V> *push_R(Node<K, V> *N, Node<K, V> *Current)
	{
		Node<K, V> *pushedNode = Tree<K, V>::push_R(N, Current);
		if (pushedNode != nullptr)
			return Balance(pushedNode);
		return pushedNode;
	}

	virtual Node<K, V> *Remove_R(K key, Node<K, V> *N)
	{
		Node<K, V> *temp;
		if (N == nullptr)
			return nullptr;
		if (key < N->getKey())
			N->setLeft(Remove_R(key, N->getLeft()));
		else if (key > N->getKey())
			N->setRight(Remove_R(key, N->getRight()));
		else if (N->getLeft() && N->getRight())
		{
			temp = Tree<K, V>::Min(N->getRight());
			N->setRight(Remove_R(temp->getKey(), N->getRight()));
			temp->setHeight(N->getHeight());
			temp->setLeft(N->getLeft());
			temp->setRight(N->getRight());
			if (N->getLeft() != nullptr)
			{
				N->getLeft()->setParent(temp);
				N->setLeft(nullptr);
			}
			if (N->getRight() != nullptr)
			{
				N->getRight()->setParent(temp);
				N->setRight(nullptr);
			}
			if (N == Tree<K, V>::root)
				Tree<K, V>::root = temp;
		}
		else
		{
			temp = N;
			if (N->getLeft() == nullptr)
			{
				N = N->getRight();
				if (N != nullptr)
					N->setParent(temp->getParent());
				temp->setRight(nullptr);
				temp->setParent(nullptr);
			}
			else if (N->getRight() == nullptr)
			{
				N = N->getLeft();
				if (N != nullptr)
					N->setParent(temp->getParent());
				temp->setLeft(nullptr);
				temp->setParent(nullptr);
			}
			if (temp == Tree<K, V>::root)
				Tree<K, V>::root = N;
			temp->setParent(nullptr);
		}

		return Balance(N);
	}

public:
	AVL_Tree<K, V>() : IteratedTree<K, V>() {}

	virtual Node<K, V> *push(Node<K, V> *N)
	{
		return push_R(N, Tree<K, V>::root);
	}

	virtual Node<K, V> *push(K key, V data)
	{
		auto *N = new Node<K, V>;
		N->setKey(key);
		N->setData(data);
		return push_R(N, Tree<K, V>::root);
	}

	virtual Node<K, V> *Remove(K key)
	{
		Node<K, V> *result = Tree<K, V>::Find(key);
		Remove_R(key, Tree<K, V>::root);
		return result;
	}

	virtual void InOrder(Node<K, V> *N, void (*f)(Node<K, V> *))
	{
		if (N == nullptr)
			return;
		typename IteratedTree<K, V>::iterator start = IteratedTree<K, V>::Min();
		typename IteratedTree<K, V>::iterator end = IteratedTree<K, V>::Max();
		while (true)
		{
			auto tem = (*end).getData();
			cout << "\nNode: " << (*start).getKey() << " -> " << tem << ", height: " << (*start).getHeight();
			if (start == end)
				break;
			++start;
		}
	}

	virtual void PostOrder(Node<K, V> *N, void (*f)(Node<K, V> *))
	{
		if (N == nullptr)
			return;
		typename IteratedTree<K, V>::iterator start = IteratedTree<K, V>::Min();
		typename IteratedTree<K, V>::iterator end = IteratedTree<K, V>::Max();
		while (true)
		{
			auto tem = (*end).getData();
			cout << "\nNode: " << (*end).getKey() << " -> " << tem << ", height: " << (*end).getHeight();
			if (start == end)
				break;
			--end;
		}
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
	std::string book_name;
	std::string surname;
	std::string name;
	int year_of_present;
	std::string publisher;
	unsigned int num_of_pages;
	Type type;
	int count;

	Book(std::string book_name_ = "Unknown", std::string surname_ = "Unknown", std::string name_ = "Unknown",
		 int year_of_present_ = 0, std::string publisher_ = "Unknown",
		 unsigned int num_of_pages_ = 0, Type type_ = none, int count_ = 0)
	{
		book_name = book_name_;
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
		book_name = book.book_name;
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
	s << "\nBook name: " << b.book_name << "\nSurname: " << b.surname << "\nName: " << b.name << "\nYear of present: " << b.year_of_present << "\nNum of pages: " << b.num_of_pages << "\nPublication type: " << b.type << "\nCirculation: " << b.count << "\n";
}

int main()
{

	Book b1("one", "o", "o", 1, "o", 1, book, 1);
	Book b2("two", "t", "t", 2, "t", 2, book, 2);
	Book b3("three", "th", "th", 3, "th", 3, book, 3);
	Book b4("four", "f", "f", 4, "f", 4, book, 4);
	Book b5("five", "fi", "fi", 5, "fi", 5, book, 5);
	Book b6("six", "s", "s", 6, "s", 6, book, 6);

	AVL_Tree<string, Book> book_container;
	book_container.push(b1.book_name, b1);
	book_container.push(b2.book_name, b2);
	book_container.push(b3.book_name, b3);
	book_container.push(b4.book_name, b4);
	book_container.push(b5.book_name, b5);
	book_container.push(b6.book_name, b6);

	book_container.InOrder(book_container.getRoot(), print);
	return 0;
}
