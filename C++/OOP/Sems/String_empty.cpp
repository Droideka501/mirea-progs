

#include <iostream>

using namespace std;

class BaseString
{
protected:
	char* p;
	int len;
	int capacity;
public:
	BaseString(char* ptr)
	{
		cout<<"\nBase Constructor 1\n";
	}

	BaseString(int Capacity = 256)
	{
		cout<<"\nBase Constructor 0\n";
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
	}

	~BaseString()
	{
		cout<<"\nBase Destructor\n";
		if(p!=NULL)
			delete[] p;
		len = 0;
	}

	int Length() {return len;}
	int Capacity() { return capacity; }
	//char* get() {return p;}
	char& operator[](int i) {return p[i];}


	BaseString& operator=(BaseString& s)
	{
		cout<<"\nBase Operator = \n";
		
		return *this;
	}

	BaseString(BaseString& s)
	{
		cout<<"\nBase Copy Constructor\n";
		
	}

	virtual void print()
	{
		int i=0;
		while(p[i]!='\0')
		{
			cout<<p[i];
			i++;
		}
	}
};

int main()
{
	if (true)
	{
		String s("test");
		s.print();
		String s1 = s;
		s1.print();
		String s2;
		s2 = s;
		s2 = s + s1;
		s2.print();
		s1 = s2 + s;
		s1.print();
	}
	char c; cin>>c;
	return 0;
}

