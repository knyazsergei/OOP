#pragma once
#include <map>
#include <boost/container/small_vector.hpp>
#include <boost/optional/optional.hpp>

class CCalculator;

enum class OperatorType
{
	equals,
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
	CFunc(
		const std::string & fnName,
		const std::string & firstId,
		OperatorType & operatorType,
		const std::string & secondId);
	CFunc(const std::string & fnName, const std::string & firstId);

	boost::optional<double> Run(CCalculator & calc);
	void GetDepency(CCalculator & calc)const;
private:
	bool m_complex = false;
	std::string m_fnName;

	std::string m_firstId;
	OperatorType m_operatorType;
	std::string m_secondId;
};