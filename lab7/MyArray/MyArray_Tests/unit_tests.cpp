#include "stdafx.h"
#include "../MyArray/MyArray.h"
#include <stdexcept>
#include <map>
#include <memory>
#include <type_traits>
#include <xstddef>


struct ArrayItem
{
	ArrayItem(int value = 0) : value(value)
	{}
	int value;
};

bool operator !=(const ArrayItem & first, const ArrayItem & second)
{
	return !(first.value == second.value);
}

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};

template <typename T>
auto CheckCorrectArr(CMyArray<T> & arr1)
{
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (arr1[i] != i)
		{
			return false;
		}
	}
	return true;
}

template <typename T>
auto CheckEqualArr(const CMyArray<T> & arr1, const CMyArray<T> & arr2)
{
	if (arr1.GetSize() != arr2.GetSize())
	{
		return false;
	}

	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if ((arr1[i]) != (arr2[i]))
		{
			return false;
		}
	}
	return true;
}

BOOST_FIXTURE_TEST_SUITE(MyArray, EmptyStringArray)
BOOST_AUTO_TEST_SUITE(by_default)

BOOST_AUTO_TEST_CASE(create_an_array)
{
	BOOST_CHECK_NO_THROW(CMyArray<ArrayItem>);
}

BOOST_AUTO_TEST_CASE(is_empty)
{
	BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(after_appending_an_item)
BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
{
	arr.PushBack(ArrayItem());
	BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
	
	arr.PushBack(ArrayItem());
	BOOST_CHECK_EQUAL(arr.GetSize(), 2u);

	arr.PushBack(ArrayItem());
	BOOST_CHECK_EQUAL(arr.GetSize(), 3u);

	arr.PushBack(ArrayItem());
	BOOST_CHECK_EQUAL(arr.GetSize(), 4u);

	arr.PushBack(ArrayItem());
	BOOST_CHECK_EQUAL(arr.GetSize(), 5u);

	arr.PushBack(ArrayItem());
	BOOST_CHECK_EQUAL(arr.GetSize(), 6u);
}

BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
{
	arr.PushBack(1);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 1);
	arr.PushBack(2);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 2);
	arr.PushBack(3);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 3);
	arr.PushBack(4);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 4);
	arr.PushBack(5);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 5);
	arr.PushBack(6);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 6);
}

BOOST_AUTO_TEST_CASE(initialization_lists)
{
	CMyArray<int> arr1;
	for (auto i = 0; i < 6; ++i)
	{
		arr1.PushBack(i);
	}
	CMyArray<int> arr2({ 0, 1, 2, 3, 4, 5 });
	BOOST_CHECK(CheckEqualArr(arr1, arr2));
}

BOOST_AUTO_TEST_CASE(brackets)
{
	CMyArray<int> arr1({ 0, 1, 2, 3 });
	BOOST_CHECK(CheckCorrectArr(arr1));
	arr1[3] = 10;
	BOOST_CHECK_EQUAL(arr1[3], 10);
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
	for (auto i = 0; i < 6; ++i)
	{
		arr.PushBack(i);
	}
	auto copy(arr);
	BOOST_CHECK(CheckEqualArr(arr, copy));
}

BOOST_AUTO_TEST_CASE(move_construcor)
{
	for (auto i = 0; i < 6; ++i)
	{
		arr.PushBack(i);
	}
	auto move = arr;
	BOOST_CHECK(CheckEqualArr(arr, move));
}

BOOST_AUTO_TEST_CASE(moving_constructor)
{
	CMyArray<int> arr1(CMyArray<int>({ 0, 1, 2 }));
	BOOST_CHECK(CheckCorrectArr(arr1));
}

BOOST_AUTO_TEST_CASE(the_initial_value_of_constructor)
{
	CMyArray<int> arr1(10, 5);
	bool result = true;
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (arr1[i] != 5)
		{
			result = false;
		}
	}
	BOOST_CHECK(result);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(work_with_an_array)

BOOST_AUTO_TEST_CASE(clear_array)
{
	CMyArray<ArrayItem> arr1;
	arr1.Resize(10);
	arr1.Clear();
	BOOST_CHECK_EQUAL(arr1.GetSize(), 0);
	BOOST_CHECK(CheckEqualArr(arr1, {}));
}

BOOST_AUTO_TEST_CASE(resize_array)
{
	arr.Resize(10);
	BOOST_CHECK_EQUAL(arr.GetSize(), 10u);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 0);
	arr.Resize(2);
	arr.PushBack(3);
	BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 3);
}

BOOST_AUTO_TEST_CASE(resize_array_width_start_item)
{
	CMyArray<ArrayItem> arr1;
	arr1.Resize(10);
	BOOST_CHECK_EQUAL(arr1.GetSize(), 10);
	BOOST_CHECK_EQUAL(arr1[0].value, 0);
	BOOST_CHECK_EQUAL(arr1[9].value, 0);
	arr1.Resize(2);
	BOOST_CHECK_EQUAL(arr1.GetSize(), 2);
	BOOST_CHECK_EQUAL(arr1[1].value, 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(check_iterator)
BOOST_AUTO_TEST_CASE(Iterator_range_based_for)
{
	CMyArray<int> arr1({ 0, 1, 2, 3 });
	int i = 0;
	bool result = true;
	for (auto it : arr1)
	{
		if (it != i)
		{
			result = false;
		}
		++i;
	}
	BOOST_CHECK(result);
}

BOOST_AUTO_TEST_CASE(iterator_copy)
{
	CMyArray<int> arr1({ 0, 1, 2, 3 });

	//TODO: make copy
	//CMyArray<int> arr2;
	//std::copy(arr1.begin(), arr1.end(), arr2.begin());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(type_casting)

BOOST_AUTO_TEST_CASE(constructor_casting)
{
	CMyArray<float> arr1({ 1.0f, 2.0f, 3.0f });
	CMyArray<int> arr2(arr1);
	bool result = true;
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (arr1[i] != arr2[i])
		{
			result = false;
		}
	}
	BOOST_CHECK(result);
}

BOOST_AUTO_TEST_CASE(static_casting)
{
	CMyArray<int> arr1({ 1, 2, 3 });
	auto arr2 = static_cast<CMyArray<float>>(arr1);
	bool result = true;
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (arr1[i] != arr2[i])
		{
			result = false;
		}
	}
	BOOST_CHECK(result);
}

BOOST_AUTO_TEST_CASE(equating_casing)
{
	CMyArray<int> arr1({ 1, 2, 3 });
	CMyArray<float> arr2 = arr1;
	bool result = true;
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (arr1[i] != arr2[i])
		{
			result = false;
		}
	}
	BOOST_CHECK(result);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()