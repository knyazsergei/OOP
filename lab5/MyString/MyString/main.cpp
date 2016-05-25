#include "stdafx.h"
#include <iostream>
#include "MyString.h"

using namespace std;

int main()
{
	std::cout << (CMyString("Test String") == CMyString("Test String", 11u)) << std::endl;
	auto srt = CMyString("Test");
	auto first = "CHAR*" + CMyString(" string");
	std::cout << first << std::endl;
 	return EXIT_SUCCESS;
}

