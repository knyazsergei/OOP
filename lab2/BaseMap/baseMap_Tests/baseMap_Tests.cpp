// baseMap_Tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "../baseMap/Calculate.h"
// baseSet_Tests.cpp: определяет точку входа для консольного приложения.
//
using namespace std;

bool isEqualMap( map<string, int> & firstMap, map<string, int> & secondMap)
{
	for (auto it : firstMap)
	{
		try
		{
			if (secondMap[it.first] != it.second)
			{
				return false;
			}
		}
		catch(int i)
		{
			std::cout << "Error: " << i << std::endl;
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(ProcessVectorTest)

BOOST_AUTO_TEST_CASE(BoostTestReady)
{
	BOOST_CHECK_EQUAL(2 * 2, 4);
}

BOOST_AUTO_TEST_CASE(oneWord)
{
	std::vector<std::string> words = { "hello"};
	std::map< std::string, int > vec = CalculateCountOfWords(words);
	std::map< std::string, int > realVec = { std::pair<std::string, int>({ "hello", 1 }) };

	BOOST_CHECK(isEqualMap(vec, realVec));
};


BOOST_AUTO_TEST_CASE(someWords)
{
	std::vector<std::string> words = { "hello", "world" };
	std::map< std::string, int > vec = CalculateCountOfWords(words);
	std::map< std::string, int > realVec = { std::pair<std::string, int>({ "hello", 1 }), std::pair<std::string, int>({ "world", 1 }) };
	bool isEqual = isEqualMap(vec, realVec);
	BOOST_CHECK_EQUAL(isEqual, true);
};

BOOST_AUTO_TEST_CASE(wordRepetition)
{
	std::vector<std::string> words = { "hello", "world", "hello" };
	std::map< std::string, int > vec = CalculateCountOfWords(words);
	std::map< std::string, int > realVec = { std::pair<std::string, int>({ "hello", 2 }), std::pair<std::string, int>({ "world", 1 }) };
	bool isEqual = isEqualMap(vec, realVec);
	BOOST_CHECK_EQUAL(isEqual, true);
};

BOOST_AUTO_TEST_CASE(wordRepetitionOneMore)
{
	std::vector<std::string> words = { "hello", "world", "world", "hello" };
	std::map< std::string, int > vec = CalculateCountOfWords(words);
	std::map< std::string, int > realVec = { std::pair<std::string, int>({ "hello", 2 }), std::pair<std::string, int>({ "world", 2 }) };
	bool isEqual = isEqualMap(vec, realVec);
	BOOST_CHECK_EQUAL(isEqual, true);
};

BOOST_AUTO_TEST_SUITE_END()