#pragma once
#include <map>
#include <boost/container/small_vector.hpp>
#include <boost/optional/optional.hpp>
#include <vector>

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
	CFunc(
		const std::string & fnName,
		const std::string & firstId,
		OperatorType & operatorType,
		const std::string & secondId);
	CFunc(const std::string & fnName, const std::string & firstId);

	boost::optional<double> Run(CCalculator & calc, std::map<std::string, double> & m_cashFnList);
	void GetDepency(std::vector<std::string> & m_cashDependence, std::vector<std::string> & m_cashDependenceBuffer, std::map<std::string, std::shared_ptr<CFunc>> & m_listOfFn);
	boost::optional<double> GetLastResult();
private:
	double m_result;
	bool m_complex = false;
	std::string m_fnName;

	std::string m_firstId;
	OperatorType m_operatorType;
	std::string m_secondId;
};