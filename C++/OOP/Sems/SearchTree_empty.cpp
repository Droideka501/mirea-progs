#include <iostream>
#include <cmath>

using namespace std;

template <class T>
class Node
{
protected:
	T data;

	Node *left;
	Node *right;
	Node *parent;

	int height;

public:
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }

	virtual Node *getLeft() { return left; }
	virtual Node *getRight() { return right; }
	virtual Node *getParent() { return parent; }

	virtual void setLeft(Node *N) { left = N; }
	virtual void setRight(Node *N) { right = N; }
	virtual void setParent(Node *N) { parent = N; }

	Node<T>(T n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}

	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		data = 0;
		height = 1;
	}

	virtual void print()
	{
		cout << "\n"
			 << data;
	}

	virtual void setHeight(int h)
	{
		height = h;
	}

	template <class T>
	friend ostream &operator<<(ostream &stream, Node<T> &N);
};

template <class T>
ostream &operator<<(ostream &stream, Node<T> &N)
{
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}
template <class T>
void print(Node<T> *N) { cout << "\n"
							  << N->getData(); }

template <class T>
class Tree
{
protected:
	Node<T> *root;

	virtual Node<T> *insertRoot(Node<T> *N, Node<T> *Current)
	{

		if (N == NULL)
			return NULL;

		if (root == NULL)
		{
			root = N;
			return root;
		}

		if (Current->getData() > N->getData())
		{
			if (Current->getLeft() != NULL)
			{
				return insertRoot(N, Current->getLeft());
			}
			else
			{
				Current->setLeft(N);
				N->setParent(Current);
			}
		}
		if (Current->getData() < N->getData())
		{
			if (Current->getRight() != NULL)
			{
				return insertRoot(N, Current->getRight());
			}
			else
			{
				Current->setRight(N);
				N->setParent(Current);
			}
		}
		// if (Current->getData() == N->getData())

		return N;
	}

	virtual Node<T> *Find_R(T data, Node<T> *Current)
	{
	}

public:
	virtual Node<T> *getRoot() { return root; }

	Tree<T>() { root = NULL; }

	virtual Node<T> *insert(Node<T> *N)
	{
		return insertRoot(N, root);
	}

	virtual Node<T> *insert(T n)
	{
		Node<T> *N = new Node<T>(n);
		return insertRoot(N);
	}

	virtual void Remove(Node<T> *N)
	{
	}

	virtual Node<T> *Min(Node<T> *Current = NULL)
	{
	}

	virtual Node<T> *Max(Node<T> *Current = NULL)
	{
	}

	virtual Node<T> *Find(T data)
	{
		if (root == NULL)
			return NULL;
		return Find_R(data, root);
	}

	virtual void PreOrder(Node<T> *N, void (*f)(Node<T> *))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	virtual void InOrder(Node<T> *N, void (*f)(Node<T> *))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<T> *N, void (*f)(Node<T> *))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}
};

template <typename ValueType>
class TreeIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
	Node<ValueType> *ptr;

public:
	TreeIterator() { ptr = NULL; }
	TreeIterator(Tree<ValueType> *t, Node<ValueType> *p) {}
	TreeIterator(const TreeIterator &it) {}

	TreeIterator &operator=(const TreeIterator &it) {}
	TreeIterator &operator=(Node<ValueType> *p) {}

	bool operator!=(TreeIterator const &other) const {}
	bool operator==(TreeIterator const &other) const {}
	Node<ValueType> &operator*() {}
	TreeIterator &operator++()
	{
	}
	TreeIterator &operator++(int v)
	{
	}
};

template <class T>
class IteratedTree : public Tree<T>
{
public:
	IteratedTree<T>() : Tree<T>() {}

	TreeIterator<T> iterator;

	TreeIterator<T> begin() {}
	TreeIterator<T> end() {}
};

int main()
{
	Tree<double> T;
	int arr[15];
	int i = 0;
	for (i = 0; i < 15; i++)
		arr[i] = (int)(100 * cos(15 * double(i)));
	for (i = 0; i < 15; i++)
		T.insert(arr[i]);

	Node<double> *M = T.Min();
	// cout << "\nMin = " << M->getData() << "\tFind " << arr[3] << ": " << T.Find(arr[3], T.getRoot());

	void (*f_ptr)(Node<double> *);
	f_ptr = print;
	/*cout << "\n-----\nPreorder:";
	T.PreOrder(T.getRoot(), f_ptr);*/
	cout << "\n-----\nInorder:";
	T.InOrder(T.getRoot(), f_ptr);
	/*cout << "\n-----\nPostorder:";
	T.PostOrder(T.getRoot(), f_ptr);*/
	/*cout << "\nIterators:\n";
	T.iterator = T.begin();
	while (T.iterator != T.end())
	{
		cout << *T.iterator << " ";
		T.iterator++;
	}
	cout << *T.iterator << " ";*/

	char c;
	cin >> c;
	return 0;
}
