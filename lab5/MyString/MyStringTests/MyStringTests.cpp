#include "stdafx.h"
#include "../MyString/MyString.h"
#include <string>
#include <iostream>

struct my_string_can_be_declared_by_default_
{
	CMyString myString;
};

BOOST_FIXTURE_TEST_SUITE(before_declared_string, my_string_can_be_declared_by_default_)

BOOST_AUTO_TEST_CASE(default_pointer_to_an_array_of_char_strings_is_nullptr)
{
	BOOST_CHECK_EQUAL(myString.GetStringData()[0], '\0');

	BOOST_CHECK(CMyString("aaa\0 as").GetStringData() == std::string("aaa\0 as"));
	BOOST_CHECK(CMyString("aaa\0 as").GetLength() == 3u);
}

BOOST_AUTO_TEST_CASE(default_length_of_the_string_is_equal_to_zero)
{
	BOOST_CHECK_EQUAL(myString.GetLength(), 0u);
}

BOOST_AUTO_TEST_CASE(my_str_have_a_null_char_on_end)
{
	BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength() - 1], '\0');
}

BOOST_AUTO_TEST_CASE(attempt_to_take_substring_returns_nullptr_and_zero_length)
{
	auto substr = myString.SubString(0u, 30u);
	BOOST_CHECK_EQUAL(substr.GetLength(), 0u);
	BOOST_CHECK(substr.GetStringData()[0] == '\0');
	CMyString myString2("abcde");
	auto substr2 = myString2.SubString(10, 1);
	BOOST_CHECK_EQUAL(substr2.GetStringData(), "");
	auto substr3 = myString2.SubString(4, 4);
	BOOST_CHECK_EQUAL(substr2.GetStringData(), "");

	BOOST_CHECK(substr.GetStringData()[0] == '\0');
}

BOOST_AUTO_TEST_CASE(can_clear_empty_string)
{
	BOOST_CHECK_NO_THROW(myString.Clear());
}

BOOST_AUTO_TEST_CASE(can_create_my_string_without_null_char)
{
	CMyString myStr("\0");
	BOOST_CHECK_EQUAL(myStr.GetStringData(), "\0");
	BOOST_CHECK_EQUAL(myStr.GetLength(), 0u);
}

BOOST_AUTO_TEST_CASE(my_string_without_null_char_in_center_str_will_be_cut)
{
	CMyString myStr("Test\0 String");
	BOOST_CHECK_EQUAL(myStr.GetStringData()[myStr.GetLength()], '\0');
	BOOST_CHECK_EQUAL(myStr.GetLength(), 4u);
}
BOOST_AUTO_TEST_SUITE_END()

struct my_string_can_be_declared_by_value_
{
	my_string_can_be_declared_by_value_()
		: myString("Test String")
	{};

	CMyString myString;
};

BOOST_FIXTURE_TEST_SUITE(before_declared_string_by_value, my_string_can_be_declared_by_value_)

	BOOST_AUTO_TEST_CASE(pointer_to_an_array_of_char_strings_is_equal_to_test_str)
	{
		BOOST_CHECK_EQUAL(myString.GetStringData(), "Test String");
	}

	BOOST_AUTO_TEST_CASE(default_length_of_the_string_is_equal_to_length_test_str)
	{
		BOOST_CHECK_EQUAL(myString.GetLength(), 11u);
	}

	BOOST_AUTO_TEST_CASE(attempt_to_take_correct_substring_returns_this_substr)
	{
		auto substr = myString.SubString(0u, 4u);
		BOOST_CHECK_EQUAL(substr.GetLength(), 4u);
		BOOST_CHECK_EQUAL(substr.GetStringData(), "Test");
	}

	BOOST_AUTO_TEST_CASE(my_str_have_a_null_char_on_end)
	{
		BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
	}


	BOOST_AUTO_TEST_CASE(attempt_to_take_substring_without_incorrect_args_returns_null_str)
	{
		auto substr = myString.SubString(4u, 0u);
		BOOST_CHECK_EQUAL(substr.GetLength(), 0u);
		BOOST_CHECK_EQUAL(substr.GetStringData()[0], '\0');
	}

	BOOST_AUTO_TEST_CASE(attempt_to_take_incorrect_substring_returns_empty_str)
	{
		auto substr = myString.SubString(20u, 30u);
		BOOST_CHECK_EQUAL(substr.GetLength(), 0u);
		BOOST_CHECK(substr.GetStringData()[0] == '\0');
	}

	BOOST_AUTO_TEST_CASE(can_clear_initialized_string)
	{
		BOOST_CHECK_NO_THROW(myString.Clear());
		BOOST_CHECK_EQUAL(myString.GetLength(), 0u);
		BOOST_CHECK_EQUAL(myString.GetStringData()[0], '\0');
	}

BOOST_AUTO_TEST_SUITE_END()


struct my_string_can_be_declared_by_value_and_length_
{
	my_string_can_be_declared_by_value_and_length_()
		: myString("Test String", 11u)
	{};

	CMyString myString;
};

BOOST_FIXTURE_TEST_SUITE(before_declared_string_by_value_and_length, my_string_can_be_declared_by_value_and_length_)

	BOOST_AUTO_TEST_CASE(pointer_to_an_array_of_char_strings_is_equal_to_test_str)
	{
		BOOST_CHECK_EQUAL(myString.GetStringData(), "Test String");
	}

	BOOST_AUTO_TEST_CASE(default_length_of_the_string_is_equal_to_length_test_str)
	{
		BOOST_CHECK_EQUAL(myString.GetLength(), 11u);
	}

	BOOST_AUTO_TEST_CASE(attempt_to_take_correct_substring_returns_this_substr)
	{
		auto substr = myString.SubString(0u, 4u);
		BOOST_CHECK_EQUAL(substr.GetLength(), 4u);
		BOOST_CHECK_EQUAL(substr.GetStringData(), "Test");
	}

	BOOST_AUTO_TEST_CASE(my_str_have_a_null_char_on_end)
	{
		BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
	}

	BOOST_AUTO_TEST_CASE(attempt_to_take_substring_without_incorrect_args_returns_null_str)
	{
		auto substr = myString.SubString(4u, 0u);
		BOOST_CHECK_EQUAL(substr.GetLength(), 0u);
		BOOST_CHECK_EQUAL(substr.GetStringData()[0], '\0');
	}

	BOOST_AUTO_TEST_CASE(attempt_to_take_incorrect_substring_returns_empty_str)
	{
		auto substr = myString.SubString(20u, 30u);
		BOOST_CHECK_EQUAL(substr.GetLength(), 0u);
		BOOST_CHECK(substr.GetStringData()[0] == '\0');
	}

	BOOST_AUTO_TEST_CASE(can_clear_initialized_string)
	{
		BOOST_CHECK_NO_THROW(myString.Clear());
		BOOST_CHECK_EQUAL(myString.GetLength(), 0u);
		BOOST_CHECK_EQUAL(myString.GetStringData()[0], '\0');
	}



BOOST_AUTO_TEST_SUITE_END()
