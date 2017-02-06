#include "stdafx.h"
#include "../myList/MyList.h"

BOOST_AUTO_TEST_SUITE(Test_list)

BOOST_AUTO_TEST_CASE(test_size_of_vector)
{
	CMyList<int> list;
	BOOST_CHECK_EQUAL(list.size(), 0);
	list.push_pack(123);
	BOOST_CHECK_EQUAL(list.size(), 1);
}

BOOST_AUTO_TEST_CASE(test_size_of_vector)
{
	CMyList<int> list;
	list.push_pack(123);
	BOOST_CHECK_EQUAL(list.size(), 1);
}


BOOST_AUTO_TEST_SUITE_END()
