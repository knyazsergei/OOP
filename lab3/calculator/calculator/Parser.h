#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include "Calculator.h"
#include "stdafx.h"

class CParser
{
public:
	CParser();
	~CParser();
	void parse(const std::string & code, std::shared_ptr<CCalculator> calc);
private:
	bool processLine(std::string str);
	bool processFnLine(const std::string & str);
	bool processLetLine(const std::string & str);
	bool processSetLine(const std::string & str);
	std::shared_ptr<CCalculator> m_calc;
};

