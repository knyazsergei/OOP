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

boost::optional<double> CFunc::Run(CCalculator & calc, std::map<std::string, double> & m_cashFnList)
{
	boost::optional<double> result;
	if (m_cashFnList.count(m_fnName) && !isnan(m_cashFnList.at(m_fnName)))
	{
		result = m_cashFnList[m_fnName];
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

	m_cashFnList[m_fnName] = m_result;
	result = m_result;
	return result;
}

void CFunc::GetDepency(std::vector<std::string> & m_cashDependence, std::vector<std::string> & m_cashDependenceBuffer, std::map<std::string, std::shared_ptr<CFunc>> & m_listOfFn)
{
	if (
		m_listOfFn.count(m_firstId) &&
		!std::count(m_cashDependence.begin(), m_cashDependence.end(), m_firstId) &&
		!std::count(m_cashDependenceBuffer.begin(), m_cashDependenceBuffer.end(), m_firstId)
	)
	{
		m_cashDependenceBuffer.push_back(m_firstId);
	}

	if (
		m_listOfFn.count(m_secondId) &&
		!std::count(m_cashDependence.begin(), m_cashDependence.end(), m_secondId) &&
		!std::count(m_cashDependenceBuffer.begin(), m_cashDependenceBuffer.end(), m_secondId)
		)
	{
		m_cashDependenceBuffer.push_back(m_secondId);
	}
}

boost::optional<double> CFunc::GetLastResult()
{
	return m_result;
}
