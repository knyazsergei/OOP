#include "stdafx.h"
#include "Func.h"
#include "Calculator.h"
#include <algorithm>

CFunc::CFunc(
	const std::string & fnName,
	const std::string & firstId,
	OperatorType & operatorType,
	const std::string & secondId)
{
	m_fnName = fnName;
	m_firstId = firstId;
	m_operatorType = operatorType;
	m_secondId = secondId;
	m_complex = true;
}

CFunc::CFunc(const std::string & fnName, const std::string & firstId)
{
	m_fnName = fnName;
	m_firstId = firstId;
	m_complex = false;
}

boost::optional<double> CFunc::Run(CCalculator & calc)
{
	boost::optional<double> result;
	if (calc.m_cashFnList.count(m_fnName) && !isnan(calc.m_cashFnList[m_fnName]))
	{
		result = calc.m_cashFnList[m_fnName];
		return result;
	}
	if (m_secondId.size() == 0)
	{
		result = calc[m_firstId];
		return result;
	}

	boost::optional<double> firstValue = calc[m_firstId];
	boost::optional<double> secondValue = calc[m_secondId];
	switch (m_operatorType)
	{
	case OperatorType::plus:
		m_result = firstValue.get() + secondValue.get();
		break;
	case OperatorType::minus:
		m_result = firstValue.get() - secondValue.get();
		break;
	case OperatorType::multiplication:
		m_result = firstValue.get() * secondValue.get();
		break;
	case OperatorType::division:
		m_result = firstValue.get() / secondValue.get();
		break;
	}

	calc.m_cashFnList[m_fnName] = m_result;
	result = m_result;
	return result;
}

void CFunc::GetDepency(CCalculator & calc)const
{
	if (
		calc.m_listOfFn.count(m_firstId) &&
		!std::count(calc.m_cashDependence.begin(), calc.m_cashDependence.end(), m_firstId) &&
		!std::count(calc.m_cashDependenceBuffer.begin(), calc.m_cashDependenceBuffer.end(), m_firstId)
	)
	{
		calc.m_cashDependenceBuffer.push_back(m_firstId);
	}

	if (
		calc.m_listOfFn.count(m_secondId) &&
		!std::count(calc.m_cashDependence.begin(), calc.m_cashDependence.end(), m_secondId) &&
		!std::count(calc.m_cashDependenceBuffer.begin(), calc.m_cashDependenceBuffer.end(), m_secondId)
		)
	{
		calc.m_cashDependenceBuffer.push_back(m_secondId);
	}
}
