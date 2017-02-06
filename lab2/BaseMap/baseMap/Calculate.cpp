#include "stdafx.h"
#include "Calculate.h"

std::map<std::string, size_t> CalculateCountOfWords(const std::vector<std::string> & words)
{
	std::map<std::string, size_t> result;
	
	for (auto word : words)
	{
		++result[word];
	}
	return result;
}