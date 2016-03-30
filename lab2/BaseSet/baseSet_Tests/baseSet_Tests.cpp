// baseSet_Tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../baseSet/GeneratePrimeNumbers.h"

BOOST_AUTO_TEST_SUITE(ProcessmySettorTest)

BOOST_AUTO_TEST_CASE(BoostTestReady)
{
	BOOST_CHECK_EQUAL(2 * 2, 4);
}

BOOST_AUTO_TEST_CASE(clearSet)
{
	std::set<int> mySet = GeneratePrimeNumbersSet(0);	 
	std::set<int> realmySet = std::set<int>();
	BOOST_CHECK_EQUAL_COLLECTIONS(mySet.begin(), mySet.end(),
		realmySet.begin(), realmySet.end());
};

BOOST_AUTO_TEST_CASE(smallSizeSet)
{
	std::set<int> mySet = GeneratePrimeNumbersSet(20);
	std::set<int> realmySet = std::set<int>({2, 3, 5, 7, 11, 13, 17, 19});
	
	BOOST_CHECK_EQUAL_COLLECTIONS(mySet.begin(), mySet.end(),
		realmySet.begin(), realmySet.end());

};

BOOST_AUTO_TEST_CASE(NormalSizeSet)
{
	std::set<int> mySet = GeneratePrimeNumbersSet(200);
	std::set<int> realmySet = std::set<int>({ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199 });

	BOOST_CHECK_EQUAL_COLLECTIONS(mySet.begin(), mySet.end(),
		realmySet.begin(), realmySet.end());
};

BOOST_AUTO_TEST_CASE(MaxSizeSet)
{
	std::set<int> mySet = GeneratePrimeNumbersSet(42589);
	BOOST_CHECK(mySet.find(42589) != mySet.end());
};

BOOST_AUTO_TEST_SUITE_END()