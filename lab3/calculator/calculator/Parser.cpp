#include "stdafx.h"
#include "Parser.h"
#include <iostream>

CParser::CParser(std::shared_ptr<CCalculator> calc)
{
	m_calc = calc;
	m_equalOperatorType = {
		{ "==", OperatorType::equally },
		{ "=", OperatorType::equals },
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

void CParser::ProcessCode(const std::string & code)
{
	if (!ProcessLine(code))
	{
		std::cout << "Error\n";
	}
}

boost::container::small_vector<std::string, 10> CParser::GetArgs(const std::string & srm)
{
	boost::container::small_vector<std::string, 10> result;
	std::string value;
	std::string sch;
	
	for (auto ch : srm)
	{
		sch = std::string(1, ch);
		
		if (m_equalOperatorType.count(sch) || isspace(ch))
		{
			if (!value.empty())
			{
				result.push_back(value);
			}

			if (!isspace(ch)) 
			{
				result.push_back(sch);
			}
			value = "";
		}
		else if (!isspace(ch))
		{
			value += ch;
		}
	}

	if (value.length() > 0)
	{
		result.push_back(value);
	}
	
	return result;
}

bool CParser::ProcessLine(std::string str)
{
	boost::container::small_vector<std::string, 10> args = GetArgs(str);
	if (args.size() == 0)
	{
		return false;
	}

	if (args[0] == "fn")
	{
		return ProcessFnLine(args, 1);
	}
	else if (args[0] == "printfns")
	{
		return m_calc->GetFns();
	}
	else if (args[0] == "printvars")
	{
		return m_calc->GetVars();
	}
	else if (args[0] == "printvar")
	{
		if (m_calc->GetVar(args[1]).is_initialized())
		{
			std::cout << m_calc->GetVar(args[1]).get() << std::endl;
		}
	}
	else if (args[0] == "let")
	{
		return ProcessLetLine(args, 1);
	}
	else if (args[0] == "print" && args.size() == 2 && m_calc->GetValue(args[1]).is_initialized())
	{
		std::cout << m_calc->GetValue(args[1]).get();
		return m_calc->GetValue(args[1]).is_initialized();
	}
	else if (str.find('=') != std::string::npos)
	{
		if (args.size() == 3)
		{
			return ProcessLetLine(args, 0);
		}
		else if (args.size() > 4)
		{
			return ProcessFnLine(args, 0);
		}
	}
	else if (m_calc->GetValue(str).is_initialized())
	{
		std::cout << m_calc->GetValue(str).get() << std::endl;
		return true;
	}	
	return false;
}

bool CParser::ProcessFnLine(const boost::container::small_vector<std::string, 10> & args, size_t shift)
{
	if (args.size() == 4)
	{
		
		return m_calc->SetFn(args[shift + 0], args[shift + 2], m_equalOperatorType["="], "");
	}
	return m_calc->SetFn(args[shift + 0], args[shift + 2], m_equalOperatorType[args[shift + 3]], args[shift + 4]);
}

bool CParser::ProcessLetLine(const boost::container::small_vector<std::string, 10> & args, size_t shift)
{
	return m_calc->Let(args[shift], args[shift + 2]);
}