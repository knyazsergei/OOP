#include "stdafx.h"
#include "../FindMaxEx/findMax.h"
#include <iostream>
#include <climits>

BOOST_AUTO_TEST_SUITE(Find_max_test)

template<typename T>
bool CompareCouples(const std::pair<T,T> & first, const std::pair<T, T> & second)
{
#if (0):
	std::cout << first.first << " " << first.second << "  " << second.first << " " << second.second << std::endl;
#endif
	return (first.first == second.first) && (first.second == second.second);
}

BOOST_AUTO_TEST_CASE(zeros_comparison)
{
	std::pair<int, int> first = { 0,0 };
	std::pair<int, int> second = { 0,0 };
	Sort2<int>(first.first, second.second);
	BOOST_CHECK(CompareCouples<int>(first, second));
}

BOOST_AUTO_TEST_CASE(small_numbers_comparison)
{
	std::pair<int, int> first = { 1,0 };
	std::pair<int, int> second = { 0,1 };
	Sort2<int>(first.first, first.second);
	BOOST_CHECK(CompareCouples<int>(first, second));

	first = { 0, 1 };
	Sort2<int>(first.first, first.second);
	BOOST_CHECK(CompareCouples<int>(first, second));

	first = { -500, -1000 };
	second = { -1000, -500 };
	Sort2<int>(first.first, first.second);
	BOOST_CHECK(CompareCouples<int>(first, second));
}
//
//BOOST_AUTO_TEST_CASE(char_comparison)
//{
//	std::pair<char*, char*> first = { "b","a" };
//	std::pair<char*, char*> second = { "a","b" };
//	Sort2<char*>(first.first, first.second);
//	BOOST_CHECK(CompareCouples<char*>(first, second));
//
//	first = { "ab", "ba" };
//	second = { "ab", "ba" };
//	Sort2<char*>(first.first, first.second);
//	BOOST_CHECK(CompareCouples<char*>(first, second));
//
//	first = { "ba", "ab" };
//	Sort2<char*>(first.first, first.second);
//	BOOST_CHECK(CompareCouples<char*>(first, second));
//}


bool comparator(int a, int b)
{
	return a < b;
}

BOOST_AUTO_TEST_CASE(find_max_element)
{
		std::vector<int> a = { 0, 1, 2, 3, 4 };
		auto max_value = INT_MIN;
		BOOST_CHECK(FindMax<int>(a, max_value, comparator));
		BOOST_CHECK_EQUAL(4, max_value);
}

BOOST_AUTO_TEST_CASE(find_max_element_in_min)
{
	std::vector<int> a = { INT_MIN, INT_MIN, INT_MIN };
	auto max_value = INT_MIN;
	BOOST_CHECK(!FindMax<int>(a, max_value, comparator));
}

BOOST_AUTO_TEST_CASE(find_max_element_in_min_max)
{
	std::vector<int> a = { INT_MIN, INT_MIN, INT_MIN };
	auto max_value = INT_MAX;
	BOOST_CHECK(!FindMax<int>(a, max_value, comparator));
}

BOOST_AUTO_TEST_SUITE_END()