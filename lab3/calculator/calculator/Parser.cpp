#include "stdafx.h"
#include "Parser.h"

CParser::CParser()
{
}


CParser::~CParser()
{
}

void CParser::parse(const std::string & code, std::shared_ptr<CCalculator> calc)
{
	m_calc = calc;
	std::string line;
	std::stringstream sCode(code);
	while (getline(sCode, line))
	{
		if (!processLine(line))
		{
			std::cout << "Error\n";
		}
	}
}

bool CParser::processLine(std::string str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());

	if (str.substr(0, 2) == "fn")
	{
		str = str.substr(2, std::string::npos);
		str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
		return processFnLine(str);
	}
	else if (str.substr(0, 8) == "printfns")
	{
		m_calc->PrintFns();
		return true;
	}
	else if (str.substr(0, 9) == "printvars")
	{
		m_calc->PrintVars();
		return true;
	}
	else if (str.substr(0, 3) == "let")
	{
		return processLetLine(str.substr(3, std::string::npos));
	}
	else if (str.substr(0, 5) == "print")
	{
		return m_calc->Print(str.substr(5, std::string::npos));
	}
	else if (str.find('=') != std::string::npos)
	{
		if (((str.find('+') != std::string::npos ||
			str.find('-') != std::string::npos ||
			str.find('*') != std::string::npos ||
			str.find('/') != std::string::npos)||
			str.find('^') != std::string::npos) &&
			processFnLine(str))
		{
			return true;	
		}
		else if (processLetLine(str))
		{
			return true;	
		}
	}
	return m_calc->Print(str);
}

bool CParser::processFnLine(const std::string & str)
{
	size_t i = 0;

	bool id = false;
	bool first = false;
	std::string idStr;
	std::string firstStr;
	std::string secondStr;
	std::string operatorStr;
	while (i != str.size())
	{

		if (!id)
		{
			if (str[i] == '=')
			{
				id = true;
			}
			else
			{
				idStr += str[i];
			}
		}
		else if (!first)
		{
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^')
			{
				operatorStr = str[i];
				first = true;
			}
			else
			{
				firstStr += str[i];
			}

		}
		else
		{
			secondStr += str[i];
		}
		++i;
	}
	if (firstStr == "")
	{
		return false;
	}

	OperatorType operotrType = OperatorType::none;

	if (operatorStr == "+")
	{
		operotrType = OperatorType::plus;
	}
	else if (operatorStr == "-")
	{
		operotrType = OperatorType::minus;
	}
	else if (operatorStr == "*")
	{
		operotrType = OperatorType::multiplication;
	}
	else if (operatorStr == "/")
	{
		operotrType = OperatorType::division;
	}
	else if (operatorStr == "^")
	{
		operotrType = OperatorType::degree;
	}
	m_calc->SetFn(idStr, firstStr, operotrType, secondStr);
	return true;
}

bool CParser::processLetLine(const std::string & str)
{
	size_t i = 0;
	bool left = true;
	std::string leftStr;
	std::string rightStr;
	while (i < str.size())
	{
		if (str[i] == '=')
		{
			left = false;
		}
		else if(left)
		{
			leftStr += str[i];
		}
		else
		{
			rightStr += str[i];
		}
		++i;
	}

	if (left)
	{
		return false;
	}
	return m_calc->Let(leftStr, rightStr);
}