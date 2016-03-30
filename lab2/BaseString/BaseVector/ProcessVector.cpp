#include "stdafx.h"
#include "ProcessVector.h"

void ProcessVector(std::vector<double> & numbers)
{
	if (numbers.empty())
	{
		return;
	}
	auto minNumber = *min_element(numbers.begin(), numbers.end());
	transform(numbers.begin(), numbers.end(), numbers.begin(), [&minNumber](double current) {
		return current * minNumber;
	});
}