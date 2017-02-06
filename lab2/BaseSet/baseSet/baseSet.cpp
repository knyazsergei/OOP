// baseSet.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <set>
#include "GeneratePrimeNumbers.h"
#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char * argv[])
{
	int number;
	if(argc != 2) {
		cout << "Wrong arguments, use: baseVector.exe <input file name>";
		return EXIT_FAILURE;
	}
	number = atoi(argv[1]);

	if (number < 0)
	{
		return EXIT_FAILURE;
	}

	auto result = GeneratePrimeNumbersSet(number);
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	return EXIT_SUCCESS;
}

