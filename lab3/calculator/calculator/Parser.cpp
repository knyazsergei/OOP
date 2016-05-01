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

boost::container::small_vector<std::string, 10> CParser::getArgs(const std::string & srm)
{
	boost::container::small_vector<std::string, 10> result;
	std::string value;
	std::string sch;
	for (auto ch : srm)
	{
		sch = std::string(1, ch);
		if (m_equalOperatorType.count(sch) || isspace(ch))
		{
			result.push_back(value);
			if (!isspace(ch)) {
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
	boost::container::small_vector<std::string, 10> args = getArgs(str);
	if (args.size() == 0)
	{
		return false;
	}
	/*{
		std::stringstream srm(str);
		std::string word;

		while (srm >> word)
		{
			args.push_back(word);
			std::cout << word << std::endl;
		}
	}*/
	/*std::cout << args.size() << ": ";
	std::copy(args.begin(), args.end(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;
*/
	if (args[0] == "fn")
	{
		return ProcessFnLine(args, 1);
	}
	else if (args[0] == "printfns")
	{
		m_calc->PrintFns();
		return true;
	}
	else if (args[0] == "printvars")
	{
		m_calc->PrintVars();
		return true;
	}
	else if (args[0] == "let")
	{
		return ProcessLetLine(args, 1);
	}
	else if (args[0] == "print")
	{
		return m_calc->Print(args[1]);
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
	return m_calc->Print(str);
}

bool CParser::ProcessFnLine(const boost::container::small_vector<std::string, 10> & args, size_t shift)
{
	return m_calc->SetFn(args[shift + 0], args[shift + 2], m_equalOperatorType[args[shift + 3]], args[shift + 4]);
}

bool CParser::ProcessLetLine(const boost::container::small_vector<std::string, 10> & args, size_t shift)
{
	std::cout << args[shift] << " " << args[shift + 2] << std::endl;
	return m_calc->Let(args[shift], args[shift + 2]);
}