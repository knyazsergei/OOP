#include "stdafx.h"
#include "../MyString/MyString.h"
#include <string>

// operator =
struct my_string_allows_you_assign_meaning_other_strings_
{
	my_string_allows_you_assign_meaning_other_strings_()
		: assignedMyStr("SomeString")
	{
		myString = assignedMyStr;
	}
	CMyString myString;
	CMyString assignedMyStr;
};

BOOST_FIXTURE_TEST_SUITE(before_assignment_other_string_to_my_string, my_string_allows_you_assign_meaning_other_strings_)

	BOOST_AUTO_TEST_CASE(character_string_of_my_string_is_equal_assignment_string)
	{
		BOOST_CHECK_EQUAL(myString.GetStringData(), "SomeString");
	}

	BOOST_AUTO_TEST_CASE(existing_strings_length_is_equal_assignment_strings_length)
	{
		BOOST_CHECK_EQUAL(myString.GetLength(), 10u);
	}

	BOOST_AUTO_TEST_CASE(can_be_assign_itself)
	{
		BOOST_CHECK_NO_THROW(myString = myString);
		
		BOOST_CHECK_EQUAL(myString.GetStringData(), "SomeString");
	}

BOOST_AUTO_TEST_SUITE_END()


// operator + for CMyString, std::string, const char*
struct my_string_have_the_addition_operator_
{
	my_string_have_the_addition_operator_()
	{
		stlAddStr = std::string("STL") + CMyString(" string");
		charArrAddStr = "CHAR*" + CMyString(" string");
		myAddStr = CMyString("MY") + CMyString(" string");
	}
	CMyString stlAddStr;
	CMyString charArrAddStr;
	CMyString myAddStr;
};

BOOST_FIXTURE_TEST_SUITE(before_addition_strings, my_string_have_the_addition_operator_)

	BOOST_AUTO_TEST_CASE(characters_string_of_my_string_is_equal_assignment_strings)
	{
		BOOST_CHECK_EQUAL(stlAddStr.GetStringData(), "STL\0 string");

		BOOST_CHECK_EQUAL(charArrAddStr.GetStringData(), "CHAR*\0 string");

		BOOST_CHECK_EQUAL(myAddStr.GetStringData(), "MY\0 string");
	}

	BOOST_AUTO_TEST_CASE(existing_strings_length_is_equal_assignment_strings_length)
	{
		BOOST_CHECK_EQUAL(stlAddStr.GetLength(), 12u);

		BOOST_CHECK_EQUAL(charArrAddStr.GetLength(), 14u);

		BOOST_CHECK_EQUAL(myAddStr.GetLength(), 12u);
	}

	BOOST_AUTO_TEST_CASE(can_be_assign_addition_of_itself)
	{
		BOOST_CHECK_NO_THROW(myAddStr = myAddStr + myAddStr);

		BOOST_CHECK_EQUAL(myAddStr.GetStringData(), "MY\0 stringMY string");
	}

BOOST_AUTO_TEST_SUITE_END()

//operator ==
BOOST_AUTO_TEST_SUITE(comparison_operator)

BOOST_AUTO_TEST_CASE(strings_are_equal)
{
	BOOST_CHECK(CMyString("Test String") == CMyString("Test String", 11u));
}

BOOST_AUTO_TEST_CASE(strings_are_not_equal)
{
	BOOST_CHECK(!(CMyString("Test String1") == CMyString("Test String", 11u)));
}

BOOST_AUTO_TEST_CASE(null_character_will_not_be_ignored)
{
	BOOST_CHECK(!(CMyString("Test") == CMyString("Test\0 String", 12u)));
}

BOOST_AUTO_TEST_SUITE_END()

//operator !=
BOOST_AUTO_TEST_SUITE(inequality_operator)

BOOST_AUTO_TEST_CASE(strings_are_equal)
{
	BOOST_CHECK(!(CMyString("Test String") != CMyString("Test String", 11u)));
}

BOOST_AUTO_TEST_CASE(strings_are_not_equal)
{
	BOOST_CHECK(CMyString("Test String1") != CMyString("Test String", 11u));
}

BOOST_AUTO_TEST_CASE(null_character_will_not_be_ignored)
{
	BOOST_CHECK(CMyString("Test") != CMyString("Test\0 String", 12u));
}


BOOST_AUTO_TEST_SUITE_END()

//operator <
	BOOST_AUTO_TEST_SUITE(less_operator)

	BOOST_AUTO_TEST_CASE(can_find_out_which_of_rows_preceded_by_another_in_alphabetical_order)
{
	BOOST_CHECK((CMyString("ab") < CMyString("abc", 3)));
}

BOOST_AUTO_TEST_CASE(left_str_is_not_less_by_right_str)
{
	BOOST_CHECK(!(CMyString("abz") < CMyString("abcd", 3)));
}

BOOST_AUTO_TEST_CASE(if_strings_is_equal_operator_less_return_false)
{
	BOOST_CHECK(!(CMyString("Test", 4u) < CMyString("Test")));
}

BOOST_AUTO_TEST_SUITE_END()
