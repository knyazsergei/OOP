// calculator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Calculator.h"
#include "Parser.h"
#include <iomanip>
#include <fstream>

int main()
{
	std::cout << std::fixed << std::setprecision(2);
	std::string str;

	std::shared_ptr<CCalculator> calc = std::make_shared<CCalculator>();
	CParser parser(calc);
	
	std::ifstream iFile("code.txt");
	if (iFile.is_open())
	{
		while (getline(iFile, str) && !str.empty())
		{
			std::cout << str << std::endl;
			parser.ProcessCode(str);
		}

	}
	while (getline(std::cin, str) && !str.empty())
	{
		parser.ProcessCode(str);
	}
	
	return EXIT_SUCCESS;
}

