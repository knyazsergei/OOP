#pragma once
#include "stdafx.h"
#include <limits>
#include <map>
#include <string>
#include <math.h> 

class CCalculator;

struct CFunc
{
	std::string m_firstId;
	std::string m_strOperator;
	std::string m_secondId;
	bool m_complex = false;
	double m_result = NAN;
	CFunc();
	CFunc(const std::string & firstId,
		const std::string & strOperator,
		const std::string & secondId);

	CFunc(const std::string & firstId);
	
	double run(CCalculator & calculator);
};

class CCalculator
{
public:
	CCalculator();
	~CCalculator();

	bool SetVar(const std::string & nameVar);
	bool Let(const std::string & nameFirstVar, const std::string & nameSecondVar);
	bool SetFn(const std::string & fnName,
		const std::string & firstId,
		const std::string & strOperator,
		const std::string & secondId);

	bool Print(const std::string & id);
	bool PrintVars();
	bool PrintFns();

	double CCalculator::operator[](std::string & id);

	double GetVar(std::string varName);
	double GetFn(std::string fnName);
private:
	bool isID(const std::string & str);
	std::map<std::string, double> m_listOfVar;
	std::map<std::string, CFunc> m_listOfFn;
};

