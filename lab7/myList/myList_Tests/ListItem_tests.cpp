#include "stdafx.h"
#include "../myList/ListItem.h"

BOOST_AUTO_TEST_SUITE(Test_list_item)

BOOST_AUTO_TEST_CASE(test_next_and_back_pointer)
{
	CListItem<int> listItem;
	BOOST_CHECK_EQUAL(listItem.GetBack(), nullptr);
	BOOST_CHECK_EQUAL(listItem.GetNext(), nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
