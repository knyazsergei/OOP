#include "stdafx.h"
#include "Func.h"
#include "Calculator.h"

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

double CFunc::Run(CCalculator & calculator, const std::string & fnName, std::map<std::string, double> & cashFnList)
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