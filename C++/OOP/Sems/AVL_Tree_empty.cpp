#include "stdafx.h"
#include <iostream>

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

	virtual Node<T> *push_R(Node<T> *N, Node<T> *Current)
	{
		if (N == NULL)
			return NULL;
		if (root == NULL)
		{
			root = N;
			return N;
		}

		if (Current->getData() > N->getData())
		{

			if (Current->getLeft() != NULL)
				Current->setLeft(push_R(N, Current->getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getData() < N->getData())
		{

			if (Current->getRight() != NULL)
				Current->setRight(push_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getData() == N->getData())

			;

		return N;
	}

	virtual Node<T> *Find_R(T data, Node<T> *Current)
	{

		if (Current == NULL)
			return NULL;

		if (Current->getData() == data)
			return Current;

		if (Current->getData() > data)
			return Find_R(data, Current->getLeft());

		if (Current->getData() < data)
			return Find_R(data, Current->getRight());
	}

public:
	virtual Node<T> *getRoot() { return root; }

	Tree<T>() { root = NULL; }

	virtual Node<T> *push(Node<T> *N)
	{
		return push_R(N, root);
	}

	virtual Node<T> *push(T n)
	{
		Node<T> *N = new Node<T>;
		N->setData(n);
		return push_R(N);
	}

	virtual void Remove(Node<T> *N)
	{
	}

	virtual Node<T> *Min(Node<T> *Current = NULL)
	{

		if (root == NULL)
			return NULL;

		if (Current == NULL)
			Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();

		return Current;
	}

	virtual Node<T> *Max(Node<T> *Current = NULL)
	{

		if (root == NULL)
			return NULL;

		if (Current == NULL)
			Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();

		return Current;
	}

	virtual Node<T> *Find(T data)
	{
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
public:
	TreeIterator()
	{
		ptr = NULL;
		T = NULL;
	}
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

private:
	Node<ValueType> *ptr;
	Tree<ValueType> *T;
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

template <class T>
class AVL_Tree : public IteratedTree<T>
{
protected:
	int bfactor(Node<T> *p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	void fixHeight(Node<T> *p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	Node<T> *RotateRight(Node<T> *p)
	{
		Node<T> *q = p->getLeft();

		p->setLeft(q->getRight());
		q->setRight(p);

		if (p != Tree<T>::root)
		{
			if (p->getParent()->getLeft() == p)
			{
				p->getParent()->setLeft(q);
			}
			else
			{
				p->getParent()->setRight(q);
			}
		}
		else
		{
			Tree<T>::root = q;
		}

		q->setParent(p->getParent());
		p->getParent(q);
		if (p->getLeft() != NULL)
		{
			p->getLeft()->setParent(p);
		}

		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T> *RotateLeft(Node<T> *q)
	{
		Node<T> *p = q->getRight();

		q->setRight(p->getLeft());
		p->setLeft(q);

		if (q != Tree<T>::root)
		{
			if (q->getParent()->getLeft() == q)
			{
				q->getParent()->setLeft(p);
			}
			else
			{
				q->getParent()->setRight(p);
			}
		}
		else
		{
			Tree<T>::root = p;
		}

		p->setParent(q->getParent());
		q->getParent(p);
		if (q->getRight() != NULL)
		{
			q->getRight()->setParent(q);
		}

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	Node<T> *Balance(Node<T> *p)
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if(bfactor(p->getRight()) < 0) RotateRight(p->getRight());
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if(bfactor(p->getLeft()) > 0) RotateLeft(p->getLeft());
			return RotateRight(p);
		}

		return p;
	}

	virtual Node<T> *push_R(Node<T> *N, Node<T> *Current)
	{

		Node<T> *pushedNode = Tree<T>::push_R(N, Current);
		if(Current != NULL);
			return Balance(Current);
		return pushedNode;
	}

public:
	AVL_Tree<T>() : IteratedTree<T>() {}

	virtual Node<T> *push(Node<T> *N)
	{
		return push_R(N, root);
	}

	virtual Node<T> *push(T n)
	{
		Node<T> *N = new Node<T>;
		N->setData(n);
		return push_R(N);
	}

	virtual void Remove(Node<T> *N)
	{
	}
};

int main()
{
	AVL_Tree<double> T;
	int arr[15];
	int i = 0;
	for (i = 0; i < 15; i++)
		arr[i] = (int)(100 * cos(15 * double(i)));
	for (i = 0; i < 15; i++)
		T.push(arr[i]);

	Node<double> *M = T.Min();
	cout << "\nMin = " << M->getData() << "\tFind " << arr[3] << ": " << T.Find(arr[3], T.getRoot());

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
