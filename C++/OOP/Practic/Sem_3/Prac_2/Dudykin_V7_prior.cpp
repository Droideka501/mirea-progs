#include <iostream>
#include <queue>

using namespace std;

template <typename T>
void print_queue(T &q)
{
    while (!q.empty())
    {
        cout << q.top();
        q.pop();
    }
    std::cout << '\n';
}

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

	bool operator<(const Book &b) const
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
    priority_queue<Book> pq;

    Book b1("one", "o", "o", 1, "o", 1, book, 1);
	Book b2("two", "t", "t", 2, "t", 2, book, 2);
	Book b3("three", "th", "th", 3, "th", 3, book, 3);
	Book b4("four", "f", "f", 4, "f", 4, book, 4);
	Book b5("five", "fi", "fi", 5, "fi", 5, book, 5);
	Book b6("six", "s", "s", 6, "s", 6, book, 6);

    pq.push(b1);
    pq.push(b2);
    pq.push(b3);
    pq.push(b4);
    pq.push(b5);
    pq.push(b6);

    print_queue(pq);
}