#include "stdafx.h"
#include "Calculator.h"
#include <cmath>
#include <iostream>


CFunc::CFunc()
{

}

CFunc::CFunc(const std::string & firstId,
			 OperatorType & operatorType,
			 const std::string & secondId)
{
	m_firstId = firstId;
	m_operatorType = operatorType;
	m_secondId = secondId;
	m_complex = true;
}

CFunc::CFunc(const std::string & firstId)
{
	m_firstId = firstId;
	m_complex = false;
}

double CFunc::Run(CCalculator & calculator,const std::string & fnName, std::map<std::string, double> & cashFnList)
{	
	if (cashFnList.count(fnName) && !isnan(cashFnList[fnName]))
	{
		return cashFnList[fnName];
	}

	if (!m_complex)
	{
		return calculator[m_firstId];
	}

	if (m_operatorType == OperatorType::plus)
	{
		m_result = calculator[m_firstId] + calculator[m_secondId];
	}
	else if (m_operatorType == OperatorType::minus)
	{
		m_result = calculator[m_firstId] - calculator[m_secondId];
	}
	else if (m_operatorType == OperatorType::multiplication)
	{
		m_result = calculator[m_firstId] * calculator[m_secondId];
	}
	else if (m_operatorType == OperatorType::division)
	{
		m_result = calculator[m_firstId] / calculator[m_secondId];
	}
	else if (m_operatorType == OperatorType::degree)
	{
		m_result = pow(calculator[m_firstId], calculator[m_secondId]);
	}
	cashFnList[fnName] = m_result;
	return m_result;
}

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
	OperatorType operatorType,
	const std::string & secondId)
{
	if (m_listOfFn.count(fnName) != 0 || !CheckIdentificator(fnName))
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

bool CCalculator::CheckIdentificator(const std::string & str)
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

double CCalculator::GetVar(std::string varName)
{
	return m_listOfVar[varName];
}

double CCalculator::GetFn(std::string fnName)
{
	return m_listOfFn[fnName].Run(*this, fnName, cashFnList);
}

double CCalculator::operator[](std::string & id)
{
	if (m_listOfVar.count(id))
	{
		return m_listOfVar[id];
	}

	if (m_listOfFn.count(id))
	{
		return m_listOfFn[id].Run(*this, id, cashFnList);
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

bool CCalculator::Print(const std::string & id)
{
	if (CheckIdentificator(id) && m_listOfFn.count(id))
	{
		std::cout << m_listOfFn[id].Run(*this, id, cashFnList) << std::endl;
		cashFnList.clear();
	}
	else if (CheckIdentificator(id) && m_listOfVar.count(id))
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
	/*
	for (const auto & it : m_listOfFn)
	{
		std::cout << it.first << ":" << m_listOfFn[it.first].m_firstId << m_listOfFn[it.first].m_operatorType << m_listOfFn[it.first].m_secondId << std::endl;
	}
	*/
	return true;
}