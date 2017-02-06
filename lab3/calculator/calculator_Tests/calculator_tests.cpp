#include "stdafx.h"
#include "../calculator/Calculator.h"

BOOST_AUTO_TEST_SUITE(Test_calc)

CCalculator calc;

BOOST_AUTO_TEST_CASE(Check_set_correct_variable)
{
	BOOST_CHECK_EQUAL(calc.Let("a", "0"), true);
	BOOST_CHECK_EQUAL(calc.Let("_a", "0"), true);
	BOOST_CHECK_EQUAL(calc.Let("sad_a", "0"), true);
	BOOST_CHECK_EQUAL(calc.Let("sNEXT_devision99", "0"), true);
}
BOOST_AUTO_TEST_CASE(Check_incorrect_variable)
{
	BOOST_CHECK_EQUAL(calc.Let("", "0"), false);
	BOOST_CHECK_EQUAL(calc.Let("8var", "0"), false);
	BOOST_CHECK_EQUAL(calc.Let("snext+devision99", "0"), false);
	BOOST_CHECK_EQUAL(calc.Let("!snextdevision99", "0"), false);
}
BOOST_AUTO_TEST_CASE(Check_set_incorrect_value)
{
	std::string emptyStr = "";
	BOOST_CHECK_EQUAL(calc.Let("b", "asd"), false);
	BOOST_CHECK_EQUAL(calc.Let("d", "\t"), false);
	BOOST_CHECK_EQUAL(calc.Let("e", "@#$%"), false);
}

BOOST_AUTO_TEST_CASE(Change_variable)
{
	BOOST_CHECK_EQUAL(calc.Let("a", "100"), true);
	BOOST_CHECK_EQUAL(calc.GetVar("a").get() == 100, true);
}

BOOST_AUTO_TEST_CASE(Check_creat_wrong_function)
{
	BOOST_CHECK_EQUAL(calc.SetFn("a", "4", OperatorType::plus, "2"), false);
	BOOST_CHECK_EQUAL(calc.SetFn("23", "a", OperatorType::plus, "2"), false);
	BOOST_CHECK_EQUAL(calc.SetFn("fn3", "not_specified_variable", OperatorType::plus, "b"), false);
}

BOOST_AUTO_TEST_CASE(Check_creat_correct_function)
{
	BOOST_CHECK_EQUAL(calc.SetFn("fn1", "4", OperatorType::plus, "2"), true);
	BOOST_CHECK_EQUAL(calc.SetFn("fn2", "a", OperatorType::plus, "2"), true);
	BOOST_CHECK_EQUAL(calc.SetFn("fn3", "a", OperatorType::plus, "b"), true);
}

BOOST_AUTO_TEST_SUITE_END()