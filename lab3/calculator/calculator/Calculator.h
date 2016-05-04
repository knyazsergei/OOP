#pragma once
#include "stdafx.h"
#include <limits>
#include <map>
#include <string>
#include <math.h>
#include <ctype.h>
#include <vector>
//#include "Tree.h"
#include "Func.h"
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/optional/optional.hpp>
#include <boost/optional/optional_io.hpp>

class CCalculator
{
	friend CFunc;
public:
	CCalculator();
	~CCalculator();

	bool Let(const std::string & nameFirstVar, const std::string & nameSecondVar);
	bool SetFn(const std::string & fnName,
		const std::string & firstId,
		OperatorType operatorType,
		const std::string & secondId="");

	boost::optional<double> GetValue(const std::string & id);
	bool GetVars()const;

	std::map<std::string, double>::const_iterator BeginItForVariablesList() const;
	std::map<std::string, double>::const_iterator EndItForVariablesList() const;

	std::map<std::string, std::shared_ptr<CFunc>>::const_iterator BeginItForFunctionList() const;
	std::map<std::string, std::shared_ptr<CFunc>>::const_iterator EndItForFunctionList() const;

	bool GetFns();

	boost::optional<double> operator[](const std::string & id);

	boost::optional<double> GetVar(const std::string & varName)const;
	boost::optional<double> CalculateFn(const std::string & fnName);
private:
	bool CheckIdentifier(const std::string & str)const;

	std::map<std::string, double> m_listOfVar;
	std::map<std::string, std::shared_ptr<CFunc>> m_listOfFn;
	//cash
	std::map<std::string, double> m_cashFnList;
	//
	std::vector<std::string> m_cashDependenceBuffer;
	std::vector<std::string> m_cashDependence;
};

bool IsNumber(const std::string& s);