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

	bool Print(const std::string & id);
	bool PrintVars()const;
	bool PrintFns();

	double operator[](const std::string & id);

	double GetVar(const std::string & varName)const;
	double CalculateFn(const std::string & fnName);
private:
	
	bool CheckIdentificator(const std::string & str)const;

	std::map<std::string, double> m_listOfVar;
	std::map<std::string, std::shared_ptr<CFunc>> m_listOfFn;
	//cash
	std::map<std::string, double> m_cashFnList;
	//
	std::vector<std::string> m_cashDependenceBuffer;
	std::vector<std::string> m_cashDependence;
};

bool isNumber(const std::string& s);