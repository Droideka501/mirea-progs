#include <iostream>

using namespace std;

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

	Book(const Book &b)
	{
		book_name = b.book_name;
		surname = b.surname;
		name = b.name;
		year_of_present = b.year_of_present;
		publisher = b.publisher;
		num_of_pages = b.num_of_pages;
		type = b.type;
		count = b.count;
	}

	bool operator<(Book const &b) const
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

    bool operator>(Book const &b) const
	{
		if (count == b.count)
		{
			if (year_of_present == b.year_of_present)
			{
				if (name == b.name)
					return false;
				else
					return name > b.name ? true : false;
			}
			else
				return year_of_present > b.year_of_present ? true : false;
		}
		else
			return count > b.count ? true : false;
	}

    bool operator==(Book const &b) const
    {
        if(book_name == b.book_name &&
		surname == b.surname &&
		name == b.name &&
		year_of_present == b.year_of_present &&
		publisher == b.publisher &&
		num_of_pages == b.num_of_pages &&
		type == b.type &&
		count == b.count)
        return true;
        else return false;
    }

	friend std::ostream &operator<<(std::ostream &, const Book &);
};

std::ostream &operator<<(std::ostream &s, const Book &b)
{
	s << "\nBook name: " << b.book_name << "\nSurname: " << b.surname << "\nName: " << b.name << "\nYear of present: " << b.year_of_present << "\nNum of pages: " << b.num_of_pages << "\nPublication type: " << b.type << "\nCirculation: " << b.count << "\n";
}

template <class T>
class Node
{
private:
    T value;

public:
    T getValue() { return value; }
    void setValue(T v) { value = v; }

    int operator<(Node N)
    {
        return (value < N.getValue());
    }

    int operator>(Node N)
    {
        return (value > N.getValue());
    }

    void print()
    {
        cout << value;
    }

    Node &operator=(Node &c)
    {
        value = c.value;
        return *this;
    }

    template <class T1>
    friend ostream &operator<<(ostream &ustream, Node<T1> &obj);
};

template <class T>
ostream &operator<<(ostream &ustream, Node<T> &obj)
{
    ustream << obj.value;
    return ustream;
};

template <class T>
void print(Node<T> *N)
{
    cout << N->getValue() << "\n";
}

template <class T>
class Heap
{
protected:
    Node<T> *arr;
    int len;
    int size;

    void SiftUp(int index = -1)
    {
        if (len == 0)
            return;
        if (index == -1)
            index = len - 1;

        int parent_index;

        if (index % 2 == 0)
            parent_index = index / 2 - 1;
        else
            parent_index = index / 2;

        if (parent_index < 0)
            return;

        if (arr[index] > arr[parent_index])
        {
            Swap(parent_index, index);
            SiftUp(parent_index);
        }
    }

    void Heapify(int index = 0)
    {
        if (index < 0 || index >= len)
            return;

        int left_child_index = index * 2 + 1;
        int right_child_index = index * 2 + 2;

        if (left_child_index >= len)
            return;

        int max_child_index = -1;

        if (right_child_index >= len)
            max_child_index = left_child_index;
        else
            max_child_index =
                arr[left_child_index] > arr[right_child_index] ? left_child_index : right_child_index;

        if (arr[max_child_index] > arr[index])
        {
            Swap(max_child_index, index);
            Heapify(max_child_index);
        }

        return;
    }

public:
    int getCapacity() { return size; }
    int getCount() { return len; }

    Node<T> &operator[](int index)
    {
        if (index < 0 || index >= len)
            throw invalid_argument("wrong index!");

        return arr[index];
    }

    Heap<T>(int MemorySize = 100)
    {
        arr = new Node<T>[MemorySize];
        len = 0;
        size = MemorySize;
    }

    Heap<T>(const Heap<T> &h)
    {
        arr = new Node<T>[h.size];
        len = h.len;
        size = h.size;
        for (int i = 0; i < len; i++)
            arr[i] = h.arr[i];
    }

    void Swap(int index1, int index2)
    {
        if (index1 < 0 || index1 >= len)
            throw invalid_argument("wrong index!");
        if (index2 < 0 || index2 >= len)
            throw invalid_argument("wrong index!");

        Node<T> temp;
        temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }

    void Copy(Node<T> *dest, Node<T> *source)
    {
        dest->setValue(source->getValue());
    }

    Node<T> *GetLeftChild(int index)
    {
        if (index < 0 || index * 2 >= len)
            throw invalid_argument("wrong index!");
        return &arr[index * 2 + 1];
    }

    Node<T> *GetRightChild(int index)
    {
        if (index < 0 || index * 2 >= len)
            throw invalid_argument("wrong index!");

        return &arr[index * 2 + 2];
    }

    Node<T> *GetParent(int index)
    {
        if (index <= 0 || index >= len)
            throw invalid_argument("wrong index!");

        if (index % 2 == 0)
            return &arr[index / 2 - 1];
        return &arr[index / 2];
    }

    int GetLeftChildIndex(int index)
    {
        if (index < 0 || index * 2 >= len)
            throw invalid_argument("wrong index!");
        return index * 2 + 1;
    }

    int GetRightChildIndex(int index)
    {
        if (index < 0 || index * 2 >= len)
            throw invalid_argument("wrong index!");

        return index * 2 + 2;
    }

    int GetParentIndex(int index)
    {
        if (index < 0 || index >= len)
            throw invalid_argument("wrong index!");

        if (index % 2 == 0)
            return index / 2 - 1;
        return index / 2;
    }

    void push(T v)
    {
        Node<T> *N = new Node<T>;
        N->setValue(v);
        push(N);
    }

    void push(Node<T> *N)
    {
        if (len < size)
        {
            arr[len] = *N;
            len++;
            SiftUp();
        }
    }

    Node<T> *ExtractMax()
    {

        if (len == 0)
            return NULL;

        Node<T> *res = new Node<T>;
        Copy(res, &arr[0]);
        Swap(0, len - 1);
        len--;
        Heapify();

        return res;
    }

    Node<T> *Remove_index(int index = 0)
    {

        if (index < 0 || index >= len)
            throw invalid_argument("wrong index!");

        if (len == 0)
            return NULL;

        if (index == 0)
            return ExtractMax();

        Node<T> *res = new Node<T>;
        Copy(res, &arr[index]);

        bool flag = arr[index] > arr[len - 1];

        Swap(index, len - 1);
        len--;

        if (flag)
            Heapify(index);
        else
            SiftUp(index);

        return res;
    }

    Node<T> *Remove(T val)
    {
        if (len == 0)
            return NULL;

        for (int i = 0; i < len; i++)
            if (arr[i].getValue() == val)
                return Remove_index(i);
    }

    void Straight(void (*f)(Node<T> *))
    {
        int i;
        for (i = 0; i < len; i++)
        {
            f(&arr[i]);
        }
    }

    void PreOrder(void (*f)(Node<T> *), int index = 0)
    {
        if (index >= 0 && index < len)
            f(&arr[index]);
        if (GetLeftChildIndex(index) < len)
            PreOrder(f, GetLeftChildIndex(index));
        if (GetRightChildIndex(index) < len)
            PreOrder(f, GetRightChildIndex(index));
    }

    void InOrder(void (*f)(Node<T> *), int index = 0)
    {
        if (GetLeftChildIndex(index) < len)
            PreOrder(f, GetLeftChildIndex(index));
        if (index >= 0 && index < len)
            f(&arr[index]);
        if (GetRightChildIndex(index) < len)
            PreOrder(f, GetRightChildIndex(index));
    }

    void PostOrder(void (*f)(Node<T> *), int index = 0)
    {
        if (GetLeftChildIndex(index) < len)
            PreOrder(f, GetLeftChildIndex(index));
        if (GetRightChildIndex(index) < len)
            PreOrder(f, GetRightChildIndex(index));
        if (index >= 0 && index < len)
            f(&arr[index]);
    }

    template <class T1>
    friend ostream &operator<<(ostream &ustream, Heap<T1> obj);
};

template <class T>
ostream &operator<<(ostream &ustream, Heap<T> obj)
{
    ustream << "\nLength: " << obj.len << "\n";

    for (int i = 0; i < obj.len;)
    {
        Node<int> *N = obj.ExtractMax();
        ustream << " " << *N;
        delete N;
    }

    ustream << '\n';
    return ustream;
};

int main()
{
    Heap<Book> book_heap;

    Book b1("one", "o", "o", 1, "o", 1, book, 1);
	Book b2("two", "t", "t", 2, "t", 2, book, 2);
	Book b3("three", "th", "th", 3, "th", 3, book, 3);
	Book b4("four", "f", "f", 4, "f", 4, book, 4);
	Book b5("five", "fi", "fi", 5, "fi", 5, book, 5);
	Book b6("six", "s", "s", 6, "s", 6, book, 6);

    book_heap.push(b1);
    book_heap.push(b2);
    book_heap.push(b3);
    book_heap.push(b4);
    book_heap.push(b5);
    book_heap.push(b6);

    book_heap.Remove(b1);
    book_heap.Remove(b5);

    void(*f_ptr)(Node<Book>*);
    f_ptr = print;
    book_heap.Straight(f_ptr);

    cout << " ---------------------- \n";

    cout << book_heap.ExtractMax()->getValue();
    cout << " ---------------------- \n";
    
    book_heap.Straight(f_ptr);
}