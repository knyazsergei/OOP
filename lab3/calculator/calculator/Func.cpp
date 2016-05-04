#include "stdafx.h"
#include "Func.h"
#include "Calculator.h"
#include <algorithm>

CFunc::CFunc(
	std::shared_ptr<CCalculator> calc, 
	const std::string & fnName,
	const std::string & firstId,
	OperatorType & operatorType,
	const std::string & secondId)
{
	m_fnName = fnName;
	m_calc = calc;
	m_firstId = firstId;
	m_operatorType = operatorType;
	m_secondId = secondId;
	m_complex = true;
}

CFunc::CFunc(std::shared_ptr<CCalculator> calc, const std::string & fnName, const std::string & firstId)
{
	m_fnName = fnName;
	m_calc = calc;
	m_firstId = firstId;
	m_complex = false;
}

double CFunc::Run()
{
	if (m_calc->m_cashFnList.count(m_fnName) && !isnan(m_calc->m_cashFnList[m_fnName]))
	{
		return m_calc->m_cashFnList[m_fnName];
	}
	if (m_secondId.size() == 0)
	{
		return (*m_calc)[m_firstId];
	}

	double firstValue = (*m_calc)[m_firstId];
	double secondValue = (*m_calc)[m_secondId];

	if (m_operatorType == OperatorType::plus)
	{
		m_result = firstValue + secondValue;
	}
	else if (m_operatorType == OperatorType::minus)
	{
		m_result = firstValue - secondValue;
	}
	else if (m_operatorType == OperatorType::multiplication)
	{
		m_result = firstValue * secondValue;
	}
	else if (m_operatorType == OperatorType::division)
	{
		m_result = firstValue / secondValue;
	}
	else if (m_operatorType == OperatorType::degree)
	{
		m_result = pow(firstValue, secondValue);
	}
	else if (m_operatorType == OperatorType::equally)
	{
		m_result = double(firstValue == secondValue);
	}
	m_calc->m_cashFnList[m_fnName] = m_result;
	return m_result;
}

void CFunc::getDepency()
{
	if (
		m_calc->m_listOfFn.count(m_firstId) &&
		!std::count(m_calc->m_cashDependence.begin(), m_calc->m_cashDependence.end(), m_firstId) &&
		!std::count(m_calc->m_cashDependenceBuffer.begin(), m_calc->m_cashDependenceBuffer.end(), m_firstId)
	)
	{
		m_calc->m_cashDependenceBuffer.push_back(m_firstId);
	}

	if (
		m_calc->m_listOfFn.count(m_secondId) &&
		!std::count(m_calc->m_cashDependence.begin(), m_calc->m_cashDependence.end(), m_secondId) &&
		!std::count(m_calc->m_cashDependenceBuffer.begin(), m_calc->m_cashDependenceBuffer.end(), m_secondId)
		)
	{
		m_calc->m_cashDependenceBuffer.push_back(m_secondId);
	}
}
