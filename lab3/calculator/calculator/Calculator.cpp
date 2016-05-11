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
	if (!CheckIdentifier(nameFirstVar))
	{
		return false;
	}
	else if (!m_listOfVar.count(nameFirstVar))
	{
		m_listOfVar[nameFirstVar] = NAN;
	}
	
	if (IsNumber(nameSecondVar))
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
	if (!CheckIdentifier(fnName) || m_listOfVar.count(fnName) || 
		!((m_listOfVar.count(firstId) || m_listOfFn.count(firstId) || IsNumber(firstId)) &&
		(m_listOfVar.count(secondId) || m_listOfFn.count(secondId) || IsNumber(secondId) || secondId != ""))
		)
	{
		return false;
	}

	if (secondId == "")
	{
		m_listOfFn[fnName] = std::make_shared<CFunc>(fnName, firstId);
	}
	else
	{
		m_listOfFn[fnName] = std::make_shared<CFunc>(fnName, firstId, operatorType, secondId);
	}
	return true;
}

bool CCalculator::CheckIdentifier(const std::string & str)const
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

boost::optional<double> CCalculator::GetVar(const std::string & varName)const
{
	boost::optional<double> result;
	try
	{
		result = m_listOfVar.at(varName);
	}
	catch(int e)
	{
		std::cout << "The variable is not declared" << e << std::endl;
	}
	return result;
}

boost::optional<double> CCalculator::CalculateFn(const std::string & fnName)
{
	return m_listOfFn[fnName]->Run(*this, m_cashFnList);
}

boost::optional<double> CCalculator::operator[](const std::string & id)
{
	if (m_listOfVar.count(id))
	{
		return GetVar(id);
	}

	if (m_listOfFn.count(id))
	{
		return CalculateFn(id);
	}

	if (IsNumber(id))
	{
		return std::stod(id);
	}
	return NAN;
}

boost::optional<double> CCalculator::GetValue(const std::string & id)
{
	boost::optional<double> result;
	if (CheckIdentifier(id))
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
				m_listOfFn[word]->GetDepency(m_cashDependence, m_cashDependenceBuffer, m_listOfFn);
			}
			std::reverse(m_cashDependence.begin(), m_cashDependence.end());
			for (auto it : m_cashDependence)
			{
				CalculateFn(it);
			}
			result = CalculateFn(id);
		}
		else if(m_listOfVar.count(id))
		{
			result = GetVar(id);
		}
		return result;
	}
	return result;
}

namespace std
{
	std::ostream &operator<<(std::ostream &stream, const std::pair<std::string, double>& pairElement)
	{
		return stream << pairElement.first << " " << pairElement.second << std::endl;
	}
	std::ostream &operator<<(std::ostream &os, std::pair<std::string, std::shared_ptr<CFunc> > const &t) 
	{
		return os << t.first << " " << (t.second->GetLastResult().is_initialized() ? t.second->GetLastResult().get() : NAN) << std::endl;
	}
}

bool CCalculator::GetVars()const
{
	std::copy(m_listOfVar.begin(), m_listOfVar.end(), std::ostream_iterator< std::pair<std::string, double>>(std::cout, ""));
	return true;
}

bool CCalculator::GetFns()
{
	std::copy(m_listOfFn.begin(), m_listOfFn.end(), std::ostream_iterator< std::pair<std::string, std::shared_ptr<CFunc> > >(std::cout, ""));
	return true;
}

std::map <std::string, double>::const_iterator CCalculator::BeginItForVariablesList() const
{
	return m_listOfVar.begin();
}

std::map <std::string, double>::const_iterator CCalculator::EndItForVariablesList() const
{
	return m_listOfVar.end();
}

std::map <std::string, std::shared_ptr<CFunc>>::const_iterator CCalculator::BeginItForFunctionList() const
{
	return m_listOfFn.begin();
}

std::map <std::string, std::shared_ptr<CFunc>>::const_iterator CCalculator::EndItForFunctionList() const
{
	return m_listOfFn.end();
}

bool IsNumber(const std::string& s)
{
	return(strspn(s.c_str(), "-.0123456789") == s.size());
}