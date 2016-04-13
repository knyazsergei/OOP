#include "stdafx.h"
#include "Calculator.h"
#include <cmath>
#include <iostream>


CFunc::CFunc()
{

}

CFunc::CFunc(const std::string & firstId,
	const std::string & strOperator,
	const std::string & secondId)
{
	m_firstId = firstId;
	m_strOperator = strOperator;
	m_secondId = secondId;
	m_complex = true;
}

CFunc::CFunc(const std::string & firstId)
{
	m_firstId = firstId;
	m_complex = false;
}

double CFunc::run(CCalculator & calculator)
{	
	if (!isnan(m_result))
	{
		return m_result;
	}

	if (!m_complex)
	{
		return calculator[m_firstId];
	}

	if (m_strOperator == "+")
	{
		m_result = calculator[m_firstId] + calculator[m_secondId];
	}
	else if (m_strOperator == "-")
	{
		m_result = calculator[m_firstId] - calculator[m_secondId];
	}
	else if (m_strOperator == "*")
	{
		m_result = calculator[m_firstId] * calculator[m_secondId];
	}
	else if (m_strOperator == "/")
	{
		m_result = calculator[m_firstId] / calculator[m_secondId];
	}
	return m_result;
}

CCalculator::CCalculator()
{
}


CCalculator::~CCalculator()
{
}

bool CCalculator::SetVar(const std::string & nameVar)
{
	if (m_listOfVar.count(nameVar) || !isID(nameVar))
	{
		return false;
	}
	m_listOfVar[nameVar] = NAN;
	return true;
}

bool CCalculator::Let(const std::string & nameFirstVar, const std::string & nameSecondVar)
{
	if (!isID(nameFirstVar))
	{
		return false;
	}
	else if (!m_listOfVar.count(nameFirstVar))
	{
		if (!SetVar(nameFirstVar))
		{
			return false;
		}
	}
	//check is it number?
	bool isNum = true;
	for (auto it : nameSecondVar)
	{
		if (!isdigit(it))
		{
			isNum = false;
			break;
		}
	}

	if (isNum)
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
	const std::string & strOperator,
	const std::string & secondId)
{
	std::string hash = fnName;// +firstId + strOperator + secondId;
	if (m_listOfFn.count(hash) != 0 || !isID(fnName))
	{
		return false;
	}
	if (secondId == "")
	{
		m_listOfFn[hash] = CFunc(firstId);
	}
	else
	{
		m_listOfFn[hash] = CFunc(firstId, strOperator, secondId);
	}
	
	return true;
}

bool CCalculator::Print(const std::string & id)
{
	if (isID(id) && m_listOfFn.count(id))
	{
		std::cout << m_listOfFn[id].run(*this) << std::endl;
	}
	else if (isID(id) && m_listOfVar.count(id))
	{
		std::cout << m_listOfVar[id] << std::endl;
	}
	else
	{
		std::cout << id << std::endl;
	}
	return true;
}

bool CCalculator::PrintVars()
{
	for (const auto & it : m_listOfVar)
	{
		std::cout << it.first << ":" << m_listOfVar[it.first] << std::endl;
	}
	return true;
}

bool CCalculator::PrintFns()
{
	for (const auto & it : m_listOfFn)
	{
		std::cout << it.first << ":" << m_listOfFn[it.first].m_firstId << m_listOfFn[it.first].m_strOperator << m_listOfFn[it.first].m_secondId << std::endl;
	}
	return true;
}

bool CCalculator::isID(const std::string & str)
{
	if (str.length() == 0 || !(isalpha(str[0]) || str[0] == '_'))
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

double CCalculator::operator[](std::string & id)
{
	if (m_listOfVar.count(id))
	{
		return m_listOfVar[id];
	}

	if (m_listOfFn.count(id))
	{
		return m_listOfFn[id].run(*this);
	}

	bool isNum = true;
	for (auto it : id)
	{
		if (!isdigit(it))
		{
			isNum = false;
			break;
		}
	}

	if (isNum)
	{
		return std::stod(id);
	}
	return NAN;
}

double CCalculator::GetVar(std::string varName)
{
	return m_listOfVar[varName];
}

double CCalculator::GetFn(std::string fnName)
{
	return m_listOfFn[fnName].run(*this);
}
