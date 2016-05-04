#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <iterator>
#include "stdafx.h"
#include "Calculator.h"
#include <boost/container/small_vector.hpp>

class CParser
{
public:
	CParser(std::shared_ptr<CCalculator> calc);
	~CParser();
	void ProcessCode(const std::string & code);
private:
	boost::container::small_vector<std::string, 10> GetArgs(const std::string & srm);

	bool ProcessLine(std::string str);
	bool ProcessFnLine(const boost::container::small_vector<std::string, 10> & args, size_t shift);
	bool ProcessLetLine(const boost::container::small_vector<std::string, 10> & args, size_t shift);
	std::shared_ptr<CCalculator> m_calc;
	std::map<std::string, OperatorType> m_equalOperatorType;
};

