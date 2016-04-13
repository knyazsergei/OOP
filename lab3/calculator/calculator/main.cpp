// calculator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Calculator.h"
#include "Parser.h"
#include <iomanip>

int main()
{
	std::cout << std::fixed << std::setprecision(2);
	CParser parser;
	std::string str;
	std::shared_ptr<CCalculator> calc = std::make_shared<CCalculator>();
	while (getline(std::cin, str) && str != "")
	{
		parser.parse(str, calc);

	}
	return 0;
}

