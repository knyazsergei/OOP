#include "stdafx.h"
#include "../calculator/Calculator.h"

BOOST_AUTO_TEST_SUITE(Test_calc)

CCalculator calc;

BOOST_AUTO_TEST_CASE(Check_set_variable)
{
	//Check ID
	BOOST_CHECK_EQUAL(calc.SetVar("a"), true);
	BOOST_CHECK_EQUAL(calc.SetVar("_a"), true);
	BOOST_CHECK_EQUAL(calc.SetVar("8var"), false);
	BOOST_CHECK_EQUAL(calc.SetVar("sad_a"), true);
	BOOST_CHECK_EQUAL(calc.SetVar("snext_devision99"),true);
	BOOST_CHECK_EQUAL(calc.SetVar("snext+devision99"), false);
	BOOST_CHECK_EQUAL(calc.SetVar("!snextdevision99"), false);

	//check for repeat
	BOOST_CHECK_EQUAL(calc.SetVar("a"), false);
	BOOST_CHECK_EQUAL(calc.SetVar("!snextdevision99"), false);
}
	
BOOST_AUTO_TEST_CASE(Check_equating_variable)
{
	BOOST_CHECK_EQUAL(calc.Let("a", "4"), true);
	BOOST_CHECK_EQUAL(calc.Let("a", "a"), true);
	BOOST_CHECK_EQUAL(calc.Let("sad_a", "a"), true);
	BOOST_CHECK_EQUAL(calc.Let("sad_a", "snext_devision99"), true);
	BOOST_CHECK_EQUAL(calc.Let("sad_a", "23"), true);
	BOOST_CHECK_EQUAL(calc.Let("sad_a", " "), false);
}

BOOST_AUTO_TEST_CASE(Check_creat_functions)
{
	BOOST_CHECK_EQUAL(calc.SetFn("fn1", "4", "+", "2"), true);
	calc.SetVar("a");
	BOOST_CHECK_EQUAL(calc.SetFn("fn2", "a", "+", "2"), true);
	calc.SetVar("b");
	BOOST_CHECK_EQUAL(calc.SetFn("fn3", "a", "+", "b"), true);
	calc.Let("a", "1");
	calc.Let("b", "2");
	BOOST_CHECK_EQUAL(calc.SetFn("fn4", "a", "+", "b"), true);
	BOOST_CHECK_EQUAL(calc.GetFn("fn4"), 3);
}

BOOST_AUTO_TEST_SUITE_END()