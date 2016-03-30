#include "stdafx.h"
#include "GeneratePrimeNumbers.h"

std::set<int> GeneratePrimeNumbersSet(const unsigned & upperBound)
{
	std::vector<bool> sieve = std::vector<bool>(upperBound + 1, true);
	unsigned i = 2;
	unsigned j = 2;
	std::set<int> result;
	while (j <= upperBound)
	{
		if (sieve[j])
		{
			result.insert(j);
			i = j;
			for (unsigned k = i; k * i < upperBound + 1; ++k)
			{
				sieve[k * i] = false;
			}
		}
		++j;
	}

	return result;
}
