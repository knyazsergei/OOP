#pragma once
#include "stdafx.h"
#include <limits>
#include <map>
#include <string>
#include <math.h> 

class CCalculator;

enum class OperatorType
{
	plus,
	minus,
	multiplication,
	division,
	degree,
	none
};

class CFunc
{
public:
	bool m_complex = false;
	double m_result = NAN;

	CFunc();
	CFunc(const std::string & firstId,
		  OperatorType & operatorType,
		  const std::string & secondId);
	CFunc(const std::string & firstId);
	
	double Run(CCalculator & calculator,const std::string & fnName, std::map<std::string, double> & cashFnList);

	std::string m_firstId;
	OperatorType m_operatorType;
	std::string m_secondId;
};

class CCalculator
{
public:
	CCalculator();
	~CCalculator();

	bool Let(const std::string & nameFirstVar, const std::string & nameSecondVar);
	bool SetFn(const std::string & fnName,
		const std::string & firstId,
		OperatorType operatorType,
		const std::string & secondId);

	bool Print(const std::string & id);
	bool PrintVars();
	bool PrintFns();

	double operator[](std::string & id);

	double GetVar(std::string varName);
	double GetFn(std::string fnName);
private:
	bool CheckIdentificator(const std::string & str);
	
	std::map<std::string, double> m_listOfVar;
	std::map<std::string, CFunc> m_listOfFn;
	//cash
	std::map<std::string, double> cashFnList;
};

