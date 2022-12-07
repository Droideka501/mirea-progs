#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>

char* trim(const char *str)
{
	char* res = new char[strlen(str)];
	int size = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] != ' ')
		{
			res[size] = str[i];
			size++;
		}
	}
	return res;
}

int main()
{
	std::cout << trim(" asd a a asd    asdajhd");
}