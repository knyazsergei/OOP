#pragma once
#include <map>
#include <boost/container/small_vector.hpp>
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
	CFunc(std::shared_ptr<CCalculator> calc,
		const std::string & fnName,
		const std::string & firstId,
		OperatorType & operatorType,
		const std::string & secondId);
	CFunc(std::shared_ptr<CCalculator> calc, const std::string & fnName, const std::string & firstId);

	double Run();
	void getDepency();
private:
	bool m_complex = false;
	std::shared_ptr<CCalculator> m_calc;
	std::string m_fnName;

	std::string m_firstId;
	OperatorType m_operatorType;
	std::string m_secondId;
};