// EncodeHtml.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "encodeHtml.h"


int main()
{

	std::string base;
	std::string line;

	while (getline(std::cin, line) && line != "")
	{
		base.append(line);
	}

	EncodeHtml(base);
	std::cout << base;
	return EXIT_SUCCESS;
}