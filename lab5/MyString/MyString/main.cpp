#include "stdafx.h"
#include <iostream>
#include "MyString.h"

using namespace std;

int main()
{
	std::cout << (CMyString("Test String") == CMyString("Test String", 11u));
	auto srt = CMyString("Test");
	for (auto it : srt)
	{
		std::cout << it << std::endl;
	}
	return EXIT_SUCCESS;
}

