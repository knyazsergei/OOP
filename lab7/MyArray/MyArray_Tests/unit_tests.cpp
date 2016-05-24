#include "stdafx.h"
#include "../MyArray/MyArray.h"
#include <stdexcept>

struct MyStruct
{
	CMyArray<int> arr;
};

BOOST_FIXTURE_TEST_SUITE(Array_tests, MyStruct)

BOOST_AUTO_TEST_CASE(push_item_widthout_exception)
{
	BOOST_CHECK_NO_THROW(arr.PushBack(0));
}

BOOST_AUTO_TEST_CASE(get_size_tests)
{
	BOOST_CHECK_EQUAL(arr.Size(), 0);
	arr.PushBack(0);
	BOOST_CHECK_EQUAL(arr.Size(), 1);
	arr.PushBack(0);
	BOOST_CHECK_EQUAL(arr.Size(), 2);
	arr.PushBack(0);
	BOOST_CHECK_EQUAL(arr.Size(), 3);
}

BOOST_AUTO_TEST_CASE(get_item_by_index)
{
	arr.PushBack(213);
	arr.PushBack(312);
	arr.PushBack(123);
	BOOST_CHECK_EQUAL(arr[0], 213);
	BOOST_CHECK_EQUAL(arr[1], 312);
	BOOST_CHECK_EQUAL(arr[2], 123);
	BOOST_CHECK_THROW(arr[3], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(resize_array_width_start_item)
{
	arr.Resize(10, 5);
	BOOST_CHECK_EQUAL(arr.Size(), 10);
	BOOST_CHECK_EQUAL(arr[0], 5);
	BOOST_CHECK_EQUAL(arr[9], 5);
	arr.Resize(2, 5);
	BOOST_CHECK_EQUAL(arr.Size(), 2);
	BOOST_CHECK_EQUAL(arr[1], 5);
}

BOOST_AUTO_TEST_CASE(clear_array)
{
	arr.Resize(10, 0);
	arr.Clear();
	BOOST_CHECK_EQUAL(arr.Size(), 0);
	BOOST_CHECK_THROW(arr[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(initializer_list)
{
	CMyArray<int> arr1 = { 0, 1, 2 };
	BOOST_CHECK_EQUAL(arr1.Size(), 3);
	BOOST_CHECK_EQUAL(arr1[2], 2);
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
	CMyArray<int> arr1 = { 0, 1, 2 };
	CMyArray<int> arr2(arr1);
	BOOST_CHECK_EQUAL(arr1.Size(), arr2.Size());
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
	CMyArray<int> arr1(CMyArray<int>({0, 1, 2, 3}));
	BOOST_CHECK_EQUAL(arr1.Size(), 4);

	CMyArray<int> arr2(CMyArray<int>(5, 123));
	BOOST_CHECK_EQUAL(arr2.Size(), 5);
	BOOST_CHECK_EQUAL(arr2[0], 123);
	BOOST_CHECK_EQUAL(arr2[4], 123);
}

BOOST_AUTO_TEST_CASE(iterator_tests)
{
	BOOST_CHECK(true);
	CMyArray<int> arr = CMyArray<int>({ 0, 1, 2, 3 });
	size_t i= 0;
	/*
	for (auto it : arr)
	{
		it == 0;
		++i;
	}*/
}

BOOST_AUTO_TEST_SUITE_END()