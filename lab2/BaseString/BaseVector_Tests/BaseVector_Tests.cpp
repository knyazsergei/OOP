// BaseString_Tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../BaseVector/ProcessVector.h"


BOOST_AUTO_TEST_SUITE(ProcessVectorTest)

BOOST_AUTO_TEST_CASE(emptyVec)
{
	std::vector<double> vec = {};
	ProcessVector(vec);
	std::vector<double> realVec = {};
	BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(),
		realVec.begin(), realVec.end());
};

BOOST_AUTO_TEST_CASE(withOneNumber)
{
	std::vector<double> vec = {5};
	ProcessVector(vec);
	std::vector<double> realVec = {25};
	BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(),
		realVec.begin(), realVec.end());
};

BOOST_AUTO_TEST_CASE(withZero)
{
	std::vector<double> vec = {1, 0};
	ProcessVector(vec);
	std::vector<double> realVec = {0, 0};
	BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(),
		realVec.begin(), realVec.end());
};

BOOST_AUTO_TEST_CASE(withNegativeNumber)
{
	std::vector<double> vec = { -1, 1, 2, 3, 4 };
	ProcessVector(vec);
	std::vector<double> realVec = { 1, -1, -2, -3, -4 };
	BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(),
		realVec.begin(), realVec.end());
};


BOOST_AUTO_TEST_CASE(withMinNumIsOne)
{
	std::vector<double> vec = { 1, 2, 3, 4 };
	ProcessVector(vec);
	std::vector<double> realVec = { 1, 2, 3, 4 };
	BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(),
		realVec.begin(), realVec.end());
};

BOOST_AUTO_TEST_SUITE_END()