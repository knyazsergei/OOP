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
	void ProcessCode(const std::string & code, std::shared_ptr<CCalculator> calc);
private:
	bool ProcessLine(std::string str);
	bool ProcessFnLine(const std::string & str);
	bool ProcessLetLine(const std::string & str);
	std::shared_ptr<CCalculator> m_calc;
};

