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

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};

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
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(after_copy_construction)
BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
{
	for (auto i = 0; i < 6; ++i)
	{
		arr.PushBack(i);
	}
	auto copy(arr);
	BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(after_moving_constructor)
BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
{
	for (auto i = 0; i < 6; ++i)
	{
		arr.PushBack(i);
	}
	auto arr1 = arr;
	BOOST_CHECK_EQUAL(arr1.GetSize(), arr.GetSize());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(initialization_lists)
{
	CMyArray<int> arr1({ 0, 1, 2, 3, 4, 5 });
	BOOST_CHECK_EQUAL(arr1.GetSize(), 6);
	BOOST_CHECK_EQUAL(arr1.GetBack(), 5);
	arr1.PushBack(6);
	BOOST_CHECK_EQUAL(arr1.GetSize(), 7);
	BOOST_CHECK_EQUAL(arr1.GetBack(), 6);
}

BOOST_AUTO_TEST_CASE(moving_constructor)
{
	CMyArray<int> arr1(CMyArray<int>({ 0, 1, 2 }));
	bool result = true;
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (!arr1[i] == i)
		{
			result = !result;
		}
	}
	BOOST_CHECK(result);
}


BOOST_AUTO_TEST_CASE(the_initial_value_of_constructor)
{
	CMyArray<int> arr1(10, 5);
	bool result = true;
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (!(arr1[i] == 5))
		{
			result = !result;
		}
	}
	BOOST_CHECK(result);
}

BOOST_AUTO_TEST_CASE(resize)
{
	arr.Resize(10);
	BOOST_CHECK_EQUAL(arr.GetSize(), 10u);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 0);
	arr.Resize(2);
	arr.PushBack(3);
	BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
	BOOST_CHECK_EQUAL(arr.GetBack().value, 3);
}


BOOST_AUTO_TEST_CASE(brackets)
{
	CMyArray<int> arr1({ 0, 1, 2, 3 });
	bool result = true;
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (!arr1[i] == i)
		{
			result = !result;
		}
	}
	BOOST_CHECK(result);
	arr1[3] = 10;
	BOOST_CHECK_EQUAL(arr1[3], 10);
}

BOOST_AUTO_TEST_CASE(Iterator)
{
	CMyArray<int> arr1({ 0, 1, 2, 3 });
	int i = 0;
	bool result = true;
	for (auto it : arr1)
	{
		if (!it == i)
		{
			result = !result;
		}
		++i;
	}
	BOOST_CHECK(result);


	//TODO: make copy
	//CMyArray<int> arr2;
	//std::copy(arr1.begin(), arr1.end(), arr2.begin());
}
BOOST_AUTO_TEST_SUITE_END()

struct MyStruct
{
	CMyArray<int> arr;
};

BOOST_FIXTURE_TEST_SUITE(Array_tests, MyStruct)

BOOST_AUTO_TEST_CASE(push_item_widthout_exception)
{
	BOOST_CHECK_THROW(arr.GetBack(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(get_size_tests)
{
	BOOST_CHECK_EQUAL(arr.GetSize(), 0);
	arr.PushBack(0);
	BOOST_CHECK_EQUAL(arr.GetSize(), 1);
	arr.PushBack(0);
	BOOST_CHECK_EQUAL(arr.GetSize(), 2);
	arr.PushBack(0);
	BOOST_CHECK_EQUAL(arr.GetSize(), 3);
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
	CMyArray<ArrayItem> arr1;
	arr1.Resize(10);
	BOOST_CHECK_EQUAL(arr1.GetSize(), 10);
	BOOST_CHECK_EQUAL(arr1[0].value, 0);
	BOOST_CHECK_EQUAL(arr1[9].value, 0);
	arr1.Resize(2);
	BOOST_CHECK_EQUAL(arr1.GetSize(), 2);
	BOOST_CHECK_EQUAL(arr1[1].value, 0);
}

BOOST_AUTO_TEST_CASE(clear_array)
{
	CMyArray<ArrayItem> arr1;
	arr1.Resize(10);
	arr1.Clear();
	BOOST_CHECK_EQUAL(arr1.GetSize(), 0);
	BOOST_CHECK_THROW(arr1[0].value, std::out_of_range);
}

BOOST_AUTO_TEST_CASE(initializer_list)
{
	CMyArray<int> arr1 = { 0, 1, 2 };
	BOOST_CHECK_EQUAL(arr1.GetSize(), 3);
	BOOST_CHECK_EQUAL(arr1[2], 2);
}
BOOST_AUTO_TEST_SUITE_END()


class CMockItem
{
public:
	CMockItem()
	{
		ms_registry[this] = true;
	}

	CMockItem(const CMockItem &other)
	{
		ms_registry[this] = ms_registry.at(std::addressof(other));
	}

	CMockItem &operator =(const CMockItem &other)
	{
		ms_registry[this] = ms_registry.at(std::addressof(other));
		return *this;
	}

	~CMockItem()
	{
		ms_registry.erase(this);
	}

	bool IsRegistered()
	{
		return ms_registry.at(this);;
	}

private:
	static std::map<const CMockItem*, bool> ms_registry;
};

struct MyCopyStruct
{
	int value;
	//CMyArray<CMockItem> arr;
};

BOOST_FIXTURE_TEST_SUITE(ConstructTests, MyCopyStruct)

BOOST_AUTO_TEST_CASE(copy_constructor)
{
	//arr.PushBack(CMockItem());
	//CMyArray<CMockItem> arr3(arr);

	//BOOST_CHECK_EQUAL(arr3.GetSize(), arr.GetSize());
	//BOOST_CHECK_EQUAL(arr3.GetBack().IsRegistered(), arr.GetBack().IsRegistered());

}

BOOST_AUTO_TEST_CASE(move_constructor)
{
	CMyArray<int> arr1(CMyArray<int>({0, 1, 2, 3}));
	BOOST_CHECK_EQUAL(arr1.GetSize(), 4);

	CMyArray<int> arr2(CMyArray<int>(5, 123));
	BOOST_CHECK_EQUAL(arr2.GetSize(), 5);
	BOOST_CHECK_EQUAL(arr2[0], 123);
	BOOST_CHECK_EQUAL(arr2[4], 123);
}

BOOST_AUTO_TEST_CASE(iterator_tests)
{
	CMyArray<int> arr1 = CMyArray<int>({ 0, 1, 2, 3 });

	size_t i = 0;
	for (auto it : arr1)
	{
		BOOST_CHECK_EQUAL(it, i);
		++i;
	}

}
BOOST_AUTO_TEST_SUITE_END()