#pragma once
#include "stdafx.h"
#include <limits>
#include <map>
#include <string>
#include <math.h> 
#include "Func.h"
#include <ctype.h>
#include "Tree.h"

class CCalculator
{
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

	double GetVar(std::string varName)const;
	double CalculateFn(std::string fnName);
private:
	bool isNumber(const std::string& s);
	bool CheckIdentificator(const std::string & str)const;
	std::map<std::string, double> m_listOfVar;
	std::map<std::string, CFunc> m_listOfFn;
	//cash
	std::map<std::string, double> cashFnList;
	//call
	CTree m_tree;
};

