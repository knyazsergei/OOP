#include "stdafx.h"
#include "Calculator.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <utility>


CCalculator::CCalculator()
{
}


CCalculator::~CCalculator()
{
}

bool CCalculator::Let(const std::string & nameFirstVar, const std::string & nameSecondVar)
{
	if (!CheckIdentificator(nameFirstVar))
	{
		return false;
	}
	else if (!m_listOfVar.count(nameFirstVar))
	{
		m_listOfVar[nameFirstVar] = NAN;
	}
	
	if (isNumber(nameSecondVar))
	{
		m_listOfVar[nameFirstVar] = std::stod(nameSecondVar);
		return true;
	}
	return false;
}

bool CCalculator::SetFn(const std::string & fnName,
	const std::string & firstId,
	OperatorType operatorType,
	const std::string & secondId)
{
	if (!CheckIdentificator(fnName))
	{
		return false;
	}

	std::shared_ptr<CCalculator>calc(this);
	if (secondId == "")
	{
		m_listOfFn[fnName] = std::make_shared<CFunc>(calc, fnName, firstId);
	}
	else
	{
		m_listOfFn[fnName] = std::make_shared<CFunc>(calc, fnName, firstId, operatorType, secondId);
	}
	return true;
}

bool CCalculator::CheckIdentificator(const std::string & str)const
{
	if (str.size() == 0 || !(isalpha(str[0]) || str[0] == '_'))
	{
		return false;
	}

	for (const auto & ch : str)
	{
		if (!isalpha(ch) && !isdigit(ch) && (ch != '_'))
		{
			return false;
		}
	}

	return true;
}

double CCalculator::GetVar(const std::string & varName)const
{
	return m_listOfVar.at(varName);
}

double CCalculator::CalculateFn(const std::string & fnName)
{
	return m_listOfFn[fnName]->Run();
}

double CCalculator::operator[](const std::string & id)
{
	if (m_listOfVar.count(id))
	{
		return GetVar(id);
	}

	if (m_listOfFn.count(id))
	{
		return CalculateFn(id);
	}

	if(isNumber(id))
	{
		return std::stod(id);
	}
	return NAN;
}

bool CCalculator::Print(const std::string & id)
{
	if (CheckIdentificator(id))
	{
		if (m_listOfFn.count(id))
		{
			m_cashFnList.clear();
			m_cashDependenceBuffer.clear();
			m_cashDependence.clear();
			m_cashDependenceBuffer.push_back(id);
			while(m_cashDependenceBuffer.size() > 0)
			{
				std::string word = m_cashDependenceBuffer[m_cashDependenceBuffer.size() - 1];
				m_cashDependenceBuffer.pop_back();
				m_cashDependence.push_back(word);
				m_listOfFn[word]->getDepency();
			}
			std::reverse(m_cashDependence.begin(), m_cashDependence.end());
			for (auto it : m_cashDependence)
			{
				CalculateFn(it);
			}
			std::cout << "result:" << CalculateFn(id) << std::endl;
		}
		else if(m_listOfVar.count(id))
		{
			std::cout << GetVar(id) << std::endl;
		}
		return true;
	}
	std::cout << id << std::endl;
	return true;
}

namespace std{
	std::ostream &operator<<(std::ostream &stream, const std::pair<std::string, double>& pairElement)
	{
		return stream << pairElement.first << " " << pairElement.second << std::endl;
	}
	std::ostream &operator<<(std::ostream &os, std::pair<std::string, std::shared_ptr<CFunc> > const &t) 
	{
		return os << t.first << " " << t.second->m_result << std::endl;
	}
}

bool CCalculator::PrintVars()const
{
	std::copy(m_listOfVar.begin(), m_listOfVar.end(), std::ostream_iterator< std::pair<std::string, double>>(std::cout, ""));
	return true;
}

bool CCalculator::PrintFns()
{
	std::copy(m_listOfFn.begin(), m_listOfFn.end(), std::ostream_iterator< std::pair<std::string, std::shared_ptr<CFunc> > >(std::cout, ""));
	return true;
}

bool isNumber(const std::string& s)
{
	return(strspn(s.c_str(), "-.0123456789") == s.size());
}