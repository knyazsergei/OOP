#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>

//#include "Interpreter.h"

char NumberRepresentation(size_t num)
{
	static std::vector<char> m_out = { '0','1','2','3','4','5','6','7','8','9',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X','Y','Z' };
	if (m_out.size() < num) 
	{
		return -1;
	}
	else
	{
		return m_out[num];
	}
}

std::string ConvertFromTenBaseToOtherSystem(int num, int base)
{
	std::string result = "";
	if (num < base)
	{
		result = NumberRepresentation(num);
		return result;
	}
	result += ConvertFromTenBaseToOtherSystem(num / base, base);
	result += NumberRepresentation(num % base);
	return result;
}

std::pair<int, bool> ConvertNumBaseSystem_s(std::string number, const int & from, const int & to)
{
	bool error = false;
	if (from <= 0 || to  <= 0)
	{
		bool error = true;
	}
	
	bool isNegative = false;
	if (number[0] == '-') {
		isNegative = true;
		number = number.substr(1);
	}
	
	char * m_pEnd;
	int basicSystem = strtol(number.c_str(), &m_pEnd, from);
	
	if (isNegative)
	{
		return{ -1 * atoi(ConvertFromTenBaseToOtherSystem(basicSystem, to).c_str()), !error };
	}
	else
	{
		return{ atoi(ConvertFromTenBaseToOtherSystem(basicSystem, to).c_str()), !error };
	}

}

int main(int argc, char* argv[]) 
{
	setlocale(LC_ALL, "Russian");
	
	if (argc != 4)
	{
		std::cout << "invalid arguments, use params like:\n lab1.2.exe <source notation> <destination notation> <value>\n";
		return EXIT_FAILURE;
	}

	std::string data = argv[3];
	int from = atoi(argv[1]);
	int to = atoi(argv[2]);

	if (from < 2 || from > 36 || to < 2 || to > 36) {
		std::cout << "invalid notation, you can use [2-36] value\n";
		return EXIT_FAILURE;
	}
	
	auto result = ConvertNumBaseSystem_s(data, from, to);
	if (result.second) {
		std::cout << ConvertNumBaseSystem_s(data, from, to).first << std::endl;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}