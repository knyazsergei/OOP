#include "stdafx.h"
#include "Parser.h"

CParser::CParser()
{
	m_equalOperatorType = {
		{ "=", OperatorType::equally },
		{ "+", OperatorType::plus },
		{ "-", OperatorType::minus },
		{ "*", OperatorType::multiplication },
		{ "/",OperatorType::division },
		{ "^", OperatorType::degree }
	};
}


CParser::~CParser()
{
}

void CParser::ProcessCode(const std::string & code, std::shared_ptr<CCalculator> calc)
{
	m_calc = calc;
	std::string line;
	std::stringstream sCode(code);
	while (getline(sCode, line))
	{
		if (!ProcessLine(line))
		{
			std::cout << "Error\n";
		}
	}
}

bool CParser::ProcessLine(std::string str)
{
	
	std::stringstream streamArgs(str);
	std::string firstArg;
	std::string secondArg;
	streamArgs >> firstArg;
	boost::container::small_vector<std::string, 10> args;
	std::string word;
	while (streamArgs >> word)
	{
		args.push_back(word);
	}

	if (firstArg == "fn")
	{
		return ProcessFnLine(secondArg);
	}
	else if (firstArg == "printfns")
	{
		m_calc->PrintFns();
		return true;
	}
	else if (firstArg == "printvars")
	{
		m_calc->PrintVars();
		return true;
	}
	else if (firstArg  == "let")
	{
		return ProcessLetLine(str);
	}
	else if (firstArg == "print")
	{
		return m_calc->Print(secondArg);
	}
	else if (str.find('=') != std::string::npos && ProcessFnLine(str))
	{
			return true;	
	}
	return m_calc->Print(str);
}

bool CParser::ProcessFnLine(const std::string & str)
{
	size_t i = 0;

	bool id = false;
	bool first = false;
	std::string idStr;
	std::string firstStr;
	std::string secondStr;
	std::string operatorStr;
	
	for(auto ch:str)
	{

		if (!id)
		{
			if (ch == '=')
			{
				id = true;
			}
			else
			{
				idStr += ch;
			}
		}
		else if (!first)
		{
			if(m_equalOperatorType.count(std::to_string(str[i])))
			{
				operatorStr = ch;
				first = true;
			}
			else
			{
				firstStr += ch;
			}

		}
		else
		{
			secondStr += ch;
		}
	}
	if (firstStr == "")
	{
		return false;
	}

	bool isNum = true;
	for (auto ch : firstStr)
	{
		if (!isdigit(ch))
		{
			isNum = false;
			break;
		}
	}

	if (isNum & secondStr == "")
	{
		return ProcessLetLine(str);
	}

	m_calc->SetFn(idStr, firstStr, m_equalOperatorType[operatorStr], secondStr);
	return true;
}

bool CParser::ProcessLetLine(const std::string & str)
{
	size_t i = 0;
	bool left = true;
	std::string leftStr;
	std::string rightStr;
	
	for(auto ch:str)
	{
		if (ch == '=')
		{
			left = false;
		}
		else if(left)
		{
			leftStr += ch;
		}
		else
		{
			rightStr += ch;
		}
	}
	std::cout << "hi" << left << std::endl;
	if (left)
	{
		return false;
	}
	return m_calc->Let(leftStr, rightStr);
}