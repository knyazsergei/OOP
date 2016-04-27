#pragma once
#include <map>
class CCalculator;

enum class OperatorType
{
	equally,
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
	double m_result = NAN;
	CFunc();
	CFunc(const std::string & firstId,
		OperatorType & operatorType,
		const std::string & secondId);
	CFunc(const std::string & firstId);

	double Run(CCalculator & calculator, const std::string & fnName, std::map<std::string, double> & cashFnList);
private:
	bool m_complex = false;
	

	std::string m_firstId;
	OperatorType m_operatorType;
	std::string m_secondId;
};