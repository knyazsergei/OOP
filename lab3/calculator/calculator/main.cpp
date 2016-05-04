// calculator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Calculator.h"
#include "Parser.h"
#include <iomanip>

int main()
{
	std::cout << std::fixed << std::setprecision(2);
	std::string str;

	std::shared_ptr<CCalculator> calc = std::make_shared<CCalculator>();
	CParser parser(calc);

	while (getline(std::cin, str) && !str.empty())
	{
		parser.ProcessCode(str);
	}
	return EXIT_SUCCESS;
}

