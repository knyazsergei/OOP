#include "stdafx.h"
#include "../MyString/MyString.h"
#include <string>

struct my_string_can_be_declared_by_default_
{
	CMyString myString;
};

BOOST_FIXTURE_TEST_SUITE(before_declared_string, my_string_can_be_declared_by_default_)

BOOST_AUTO_TEST_CASE(default_pointer_to_an_array_of_char_strings_is_nullptr)
{
	BOOST_CHECK(myString.GetStringData()[0] == '\0');
}

BOOST_AUTO_TEST_CASE(default_length_of_the_string_is_equal_to_zero)
{
	BOOST_CHECK_EQUAL(myString.GetLength(), 0u);
}

BOOST_AUTO_TEST_CASE(my_str_have_a_null_char_on_end)
{
	BOOST_CHECK_EQUAL(myString.GetStringData()[myString.GetLength()], '\0');
}

BOOST_AUTO_TEST_CASE(attempt_to_take_substring_returns_nullptr_and_zero_length)
{
	auto substr = myString.SubString(0u, 30u);
	BOOST_CHECK_EQUAL(substr.GetLength(), 0u);
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

/*
void ExpectStringDataImpl(CMyString & s, const char *data, size_t size)
{
	BOOST_REQUIRE_EQUAL(s.GetLength(), size - 1);
	BOOST_REQUIRE_EQUAL(s.GetStringData(), data);
	BOOST_REQUIRE_EQUAL(memcmp(s.GetStringData(), data, size), 0);
}
template <size_t N>
void ExpectStringData(CMyString & s, const char(&data)[N])
{
	ExpectStringDataImpl(s, data, N);
}

BOOST_AUTO_TEST_CASE(SelfConcatenationAfterClearing)
{
	CMyString s("hello");
	s.Clear();
	s += s;
	ExpectStringData(s, "");
}

BOOST_AUTO_TEST_CASE(my_string_without_null_char_in_center_str_will_not_be_cut_off)
{
	CMyString myStr("Test\0 String", 12u);
	ExpectStringData(myStr, "Test\0 String");
	BOOST_CHECK_EQUAL(myStr.GetStringData(), "Test\0 String");
	BOOST_CHECK_EQUAL(myStr.GetLength(), 12u);
}


struct my_string_can_be_copied_existing_my_str_
{
	my_string_can_be_copied_existing_my_str_()
		: myString("Test String", 11u)
		, copiedMyStr(myString)
	{
	};

	CMyString myString;
	CMyString copiedMyStr;
};
/*
BOOST_FIXTURE_TEST_SUITE(before_copied_my_str, my_string_can_be_copied_existing_my_str_)

BOOST_AUTO_TEST_CASE(character_string_of_existing_string_is_equal_copied_string)
{
	BOOST_CHECK_EQUAL(myString.GetStringData(), copiedMyStr.GetStringData());
}

BOOST_AUTO_TEST_CASE(existing_strings_length_is_equal_copied_strings_length)
{
	BOOST_CHECK_EQUAL(myString.GetLength(), copiedMyStr.GetLength());
}

BOOST_AUTO_TEST_SUITE_END()


struct my_string_can_be_moved_from_rvalue_my_str_
{
	my_string_can_be_moved_from_rvalue_my_str_()
		: myString(CMyString("Test String", 11u))
	{
	};

	CMyString myString;
};

BOOST_FIXTURE_TEST_SUITE(before_moved_to_my_str, my_string_can_be_moved_from_rvalue_my_str_)

BOOST_AUTO_TEST_CASE(character_string_of_existing_string_is_equal_to_moved_string)
{
	BOOST_CHECK_EQUAL(myString.GetStringData(), "Test String");
}

BOOST_AUTO_TEST_CASE(existing_strings_length_is_equal_copied_strings_length)
{
	BOOST_CHECK_EQUAL(myString.GetLength(), 11u);
}

BOOST_AUTO_TEST_SUITE_END()


struct my_string_can_be_copied_from_stl_string_
{
	my_string_can_be_copied_from_stl_string_()
		: stlString("Test String")
		, myString(stlString)
	{
	};

	std::string stlString;
	CMyString myString;
};

BOOST_FIXTURE_TEST_SUITE(before_copied_from_stl_string, my_string_can_be_copied_from_stl_string_)

BOOST_AUTO_TEST_CASE(character_string_of_existing_string_is_equal_to_stl_string)
{
	BOOST_CHECK_EQUAL(myString.GetStringData(), "Test String");
}

BOOST_AUTO_TEST_CASE(existing_strings_length_is_equal_copied_stl_strings_length)
{
	BOOST_CHECK_EQUAL(myString.GetLength(), 11u);
}

BOOST_AUTO_TEST_SUITE_END()

*/