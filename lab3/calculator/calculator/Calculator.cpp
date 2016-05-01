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

bool CCalculator::isNumber(const std::string& s)
{
	return(strspn(s.c_str(), "-.0123456789") == s.size());
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
	else if(!m_listOfVar.count(nameSecondVar))
	{
		return false;
	}

	m_listOfVar[nameFirstVar] = m_listOfVar[nameSecondVar];
	return true;
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

	if (secondId == "")
	{
		m_listOfFn[fnName] = CFunc(firstId);
	}
	else
	{
		m_listOfFn[fnName] = CFunc(firstId, operatorType, secondId);
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

double CCalculator::GetVar(std::string varName)const
{
	return m_listOfVar.at(varName);
}

double CCalculator::CalculateFn(std::string fnName)
{
	return m_listOfFn[fnName].Run(*this, fnName, cashFnList);
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
	if (CheckIdentificator(id) && ( m_listOfFn.count(id) || m_listOfVar.count(id)))
	{
		std::cout << (*this)[id] << std::endl;
	}
	else
	{
		std::cout << id << std::endl;
	}
	return true;
}
namespace std{
std::ostream &operator<<(std::ostream &stream, const std::pair<std::string, double>& pairElement)
{
	return stream << pairElement.first << " " << pairElement.second << std::endl;
}
}

bool CCalculator::PrintVars()const
{
	//std::copy(m_listOfVar.begin(), m_listOfVar.end(), std::ostream_iterator< std::pair<std::string, double>>(std::cout, ""));
	/*
	for (const auto & it : m_listOfVar)
	{
		std::cout << it.first << ":" << m_listOfVar.at(it.first) << std::endl;
	}
	*/
	return true;
}

namespace std {
	std::ostream &operator<<(std::ostream &os, std::pair<std::string, CFunc > const &t) {
		return os << t.first << " " << t.second.m_result;
	}
}

bool CCalculator::PrintFns()
{
	//std::copy(m_listOfVar.begin(), m_listOfVar.end(), std::ostream_iterator< std::pair<std::string, CFunc > >(std::cout, ""));

	/*
	for (const auto & it : m_listOfFn)
	{
		std::cout << it.first << ":" << m_listOfFn[it.first].m_firstId << m_listOfFn[it.first].m_operatorType << m_listOfFn[it.first].m_secondId << std::endl;
	}
	*/
	return true;
}