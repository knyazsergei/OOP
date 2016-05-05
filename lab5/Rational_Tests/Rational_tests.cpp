// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../lab5.0/Rational.h"
BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}



/*
Рациональное число:
равно нулю по умолчанию (0/1)
может быть созданно из целого в формате (n / 1)
может быть задано с указанием числителя и знаменателя
хранится в нормализованном виде
*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
BOOST_AUTO_TEST_CASE(is_zero_by_default)
{
	VerifyRational(CRational(), 0, 1);
}
BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
{
	VerifyRational(CRational(10), 10, 1);
	VerifyRational(CRational(-10), -10, 1);
	VerifyRational(CRational(0), 0, 1);
}
BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
{
	VerifyRational(CRational(5, 2), 5, 2);
	VerifyRational(CRational(-5, 2), -5, 2);
	VerifyRational(CRational(5, -2), -5, 2);
	VerifyRational(CRational(-5, -2), 5, 2);
}
BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
{
	VerifyRational(CRational(6, 8), 3, 4);
	VerifyRational(CRational(6, -8), -3, 4);
	VerifyRational(CRational(-6, 8), -3, 4);
	VerifyRational(CRational(-6, -8), 3, 4);
	VerifyRational(CRational(-10, 20), -1, 2);
}
BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
{
	BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
}




//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE(test_case_for_ToDouble_method)
BOOST_AUTO_TEST_CASE(a_simple_rational_fraction_into_a_decimal)
{
	BOOST_CHECK_EQUAL(CRational(3, 5).ToDouble(), 0.6);
}
BOOST_AUTO_TEST_CASE(negative_simple_rational_fraction_into_a_decimal)
{
	BOOST_CHECK_EQUAL(CRational(-4, 5).ToDouble(), -0.8);
}
BOOST_AUTO_TEST_CASE(zero_numerator_into_a_decimal)
{
	BOOST_CHECK_EQUAL(CRational(0, 3).ToDouble(), 0);
}
BOOST_AUTO_TEST_CASE(the_third_part_into_a_decimal)
{
	BOOST_CHECK_EQUAL(round(CRational(1, 3).ToDouble() * 10) / 10, 0.3);
}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число без знака
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////

struct unaryOperationFixture
{
	CRational rational1;
	unaryOperationFixture()
		: rational1(3, 5)
	{}
};

BOOST_FIXTURE_TEST_SUITE(unary_operation, unaryOperationFixture)
BOOST_AUTO_TEST_CASE(unary_plus)
{
	auto r2 = +rational1;
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 3);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(unary_minus)
{
	auto r3 = -rational1;
	BOOST_CHECK_EQUAL(r3.GetNumerator(), -3);
	BOOST_CHECK_EQUAL(r3.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(unary_plus_with_unary_minus)
{
	auto r2 = -rational1;
	auto r3 = +r2;
	BOOST_CHECK_EQUAL(r3.GetNumerator(), -3);
	BOOST_CHECK_EQUAL(r3.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(unary_minus_with_unary_minus)
{
	auto r2 = -rational1;
	auto r3 = -r2;
	BOOST_CHECK_EQUAL(r3.GetNumerator(), 3);
	BOOST_CHECK_EQUAL(r3.GetDenominator(), 5);
}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
// Возвращает результат сложения двух рациональных чисел, 
//	рационального числа с целым, целого числа с рациональным.
//	(1/2) + (1/6) = (2/3)
//	(1/2) + 1     = (3/2)
//	1 + (1/2)     = (3/2)
//////////////////////////////////////////////////////////////////////////

struct binaryOperationFixture
{
	CRational rational1;
	binaryOperationFixture()
		: rational1(1, 2)
	{}
};

BOOST_FIXTURE_TEST_SUITE(binary_plus_operator, binaryOperationFixture)
BOOST_AUTO_TEST_CASE(binary_plus_with_sixth_part)
{
	auto r2 = rational1 + CRational(1, 6);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 2);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 3);
}
BOOST_AUTO_TEST_CASE(binary_plus_with_unit)
{
	auto r2 = rational1 + CRational(1);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 3);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 2);
}
BOOST_AUTO_TEST_CASE(binary_plus_with_unit_conversely)
{
	auto r2 = CRational(1) + rational1;
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 3);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 2);
}
BOOST_AUTO_TEST_CASE(binary_plus_with_negative_unit_conversely)
{
	auto r2 = CRational(-1) + rational1;
	BOOST_CHECK_EQUAL(r2.GetNumerator(), -1);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 2);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(binary_minus_with_sixth_part)
{
	auto r2 = rational1 - CRational(1, 6);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 1);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 3);
}
BOOST_AUTO_TEST_CASE(binary_minus_with_unit)
{
	auto r2 = rational1 - CRational(1);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), -1);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 2);
}
BOOST_AUTO_TEST_CASE(binary_minus_with_unit_conversely)
{
	auto r2 = CRational(1) - rational1;
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 1);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 2);
}
BOOST_AUTO_TEST_CASE(binary_minus_with_negative_unit_conversely)
{
	auto r2 = CRational(-1) - rational1;
	BOOST_CHECK_EQUAL(r2.GetNumerator(), -3);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 2);
}
BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////


struct ConcatenationOperatorFixture
{
	CRational rational1;
	ConcatenationOperatorFixture()
		: rational1(3, 2)
	{}
};

BOOST_FIXTURE_TEST_SUITE(concatenation_operator, ConcatenationOperatorFixture)
BOOST_AUTO_TEST_CASE(concatenation_operator_with_sixth_part)
{
	rational1 += CRational(1, 6);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 5);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 3);
}
BOOST_AUTO_TEST_CASE(concatenation_operator_with_unit)
{
	rational1 += CRational(1);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 5);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 2);
}
BOOST_AUTO_TEST_CASE(concatenation_operator_with_negative_sixth_part)
{
	rational1 += CRational(-1, 6);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 4);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 3);
}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////

struct SubstractionOperatorFixture
{
	CRational rational1;
	SubstractionOperatorFixture()
		: rational1(4, 3)
	{}
};

BOOST_FIXTURE_TEST_SUITE(substraction_operator, SubstractionOperatorFixture)
BOOST_AUTO_TEST_CASE(substraction_operator_with_sixth_part)
{
	rational1 -= CRational(1, 6);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 7);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 6);
}
BOOST_AUTO_TEST_CASE(substraction_operator_with_unit)
{
	rational1 -= CRational(1, 6);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 7);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 6);
}
BOOST_AUTO_TEST_CASE(substraction_operator_with_negative_unit)
{
	rational1 -= CRational(-1);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 7);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 3);
}
BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	(7*2) / 3     = (14/3)
//////////////////////////////////////////////////////////////////////////

struct MultiplyOperatorFixture
{
	CRational rational1;
	MultiplyOperatorFixture()
		: rational1(5, 6)
	{}
};

BOOST_FIXTURE_TEST_SUITE(multiply_operator, MultiplyOperatorFixture)
BOOST_AUTO_TEST_CASE(multiply_operator_with_sixth_part)
{
	auto r2 = rational1 * CRational(1, 6);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 5);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 36);
}
BOOST_AUTO_TEST_CASE(multiply_operator_with_unit)
{
	auto r2 = rational1 * CRational(1);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 5);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 6);
}
BOOST_AUTO_TEST_CASE(multiply_operator_with_negative_sixth_part)
{
	auto r2 = rational1 * CRational(-1, 6);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), -5);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 36);
}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////

struct DivisionOperatorFixture
{
	CRational rational1;
	DivisionOperatorFixture()
		: rational1(6, 5)
	{}
};

BOOST_FIXTURE_TEST_SUITE(division_operator, DivisionOperatorFixture)
BOOST_AUTO_TEST_CASE(division_operator_with_sixth_part)
{
	auto r2 = rational1 / CRational(-1, 6);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), -36);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(division_operator_with_unit)
{
	auto r2 = rational1 / CRational(1);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 6);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(division_operator_with_negative_sixth_part)
{
	auto r2 = rational1 / CRational(-1, 6);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), -36);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(division_operator_with_five)
{
	auto r2 = rational1 / CRational(5);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 6);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 25);
}
BOOST_AUTO_TEST_CASE(division_operator_with_two_thirds)
{
	auto r2 = rational1 / CRational(2, 3);
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 9);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 5);
}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////


struct MultipliedOperatorFixture
{
	CRational rational1;
	MultipliedOperatorFixture()
		: rational1(7, 8)
	{}
};

BOOST_FIXTURE_TEST_SUITE(multiplied_operator, MultipliedOperatorFixture)
BOOST_AUTO_TEST_CASE(multiplied_operator_with_two_third)
{
	rational1 *= CRational(2, 3);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 7);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 12);
}
BOOST_AUTO_TEST_CASE(multiplied_operator_with_third)
{
	rational1 *= CRational(3);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 21);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 8);
}
BOOST_AUTO_TEST_CASE(multiplied_operator_with_negative_sixth_part)
{
	rational1 *= CRational(-1, 6);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), -7);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 48);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_CASE(divisied_operator_with_two_third)
{
	rational1 /= CRational(2, 3);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 21);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 16);
}
BOOST_AUTO_TEST_CASE(divisied_operator_with_third)
{
	rational1 /= CRational(3);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 7);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), 24);
}
BOOST_AUTO_TEST_CASE(divisied_operator_with_negative_sixth_part)
{
	rational1 /= CRational(-1, 6);
	BOOST_CHECK_EQUAL(rational1.GetNumerator(), 21);
	BOOST_CHECK_EQUAL(rational1.GetDenominator(), -4);
}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
// Проверяют равенство (и неравенство) двух рациональных чисел, 
//	целого и рационального, рационального и целого:
//	(1/2) == (1/2) → true
//	(4/1) == 4     → true
//	3 == (3/1)     → true
//	(1/2) != (2/3) → true
//	(1/2) != 7     → true
//	3 != (2/3)     → true
//////////////////////////////////////////////////////////////////////////


struct ComparisonOperatorFixture
{
	CRational rational1;
	ComparisonOperatorFixture()
		: rational1(9, 5)
	{}
};

BOOST_FIXTURE_TEST_SUITE(compare_operator, ComparisonOperatorFixture)
BOOST_AUTO_TEST_CASE(comparison_operator_with_third_fourth)
{
	BOOST_CHECK(!(rational1 == CRational(3, 4)));
}
BOOST_AUTO_TEST_CASE(comparison_operator_with_nine_fifth)
{
	BOOST_CHECK(rational1 == CRational(9, 5));

}
BOOST_AUTO_TEST_CASE(not_equal_operator_with_nine_fifth)
{
	BOOST_CHECK(!(rational1 != CRational(9, 5)));

}
BOOST_AUTO_TEST_CASE(not_equal_operator_with_unit)
{
	BOOST_CHECK(rational1 != CRational(1));

}

//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////
struct ComparisonOperatorFixture
{
	CRational rational1;
	ComparisonOperatorFixture()
		: rational1(9, 5)
	{}
};

BOOST_AUTO_TEST_CASE(more_operator_with_unit)
{
	BOOST_CHECK(rational1 > CRational(1));
}
BOOST_AUTO_TEST_CASE(more_operator_with_more_number)
{
	BOOST_CHECK(!(rational1 > CRational(2)));
}
BOOST_AUTO_TEST_CASE(more_operator_with_number)
{
	BOOST_CHECK(!(rational1 > CRational(9, 5)));
}
BOOST_AUTO_TEST_CASE(less_operator_with_unit)
{
	BOOST_CHECK(!(rational1 < CRational(1)));
}
BOOST_AUTO_TEST_CASE(less_operator_with_number)
{
	BOOST_CHECK(!(rational1 < CRational(9, 5)));
}
BOOST_AUTO_TEST_CASE(less_operator_with_more_number)
{
	BOOST_CHECK(rational1 < CRational(2));
}

BOOST_AUTO_TEST_CASE(more_or_equal_operator_with_more_number)
{
	BOOST_CHECK(!(rational1 >= CRational(2)));
}
BOOST_AUTO_TEST_CASE(more_or_equal_operator_with_number)
{
	BOOST_CHECK(rational1 >= CRational(9, 5));
}
BOOST_AUTO_TEST_CASE(more_or_equal_operator_with_less_number)
{
	BOOST_CHECK(rational1 >= CRational(1));
}

BOOST_AUTO_TEST_CASE(less_or_equal_operator_with_more_number)
{
	BOOST_CHECK(rational1 <= CRational(2));
}
BOOST_AUTO_TEST_CASE(less_or_equal_operator_with_number)
{
	BOOST_CHECK(rational1 <= CRational(9, 5));
}
BOOST_AUTO_TEST_CASE(mless_or_equal_operator_with_less_number)
{
	BOOST_CHECK(!(rational1 <= CRational(1)));
}

BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////

struct ostreamOperatorFixture
{
	CRational rational = CRational(7, 15);
};

BOOST_FIXTURE_TEST_SUITE(ostream_operator, ostreamOperatorFixture)

BOOST_AUTO_TEST_CASE(rational_integer_to_ostream)
{
	std::ostringstream strm;
	strm << rational;
	BOOST_CHECK_EQUAL(strm.str(), "7/15");
}

BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////


struct istreamOperatorFixture
{
	CRational rational;
};

BOOST_FIXTURE_TEST_SUITE(istream_operator, istreamOperatorFixture)

BOOST_AUTO_TEST_CASE(rational_integer_in_istream)
{
	std::istringstream strm("1/2");
	strm >> rational;
	VerifyRational(rational, 1, 2);
}

BOOST_AUTO_TEST_CASE(negative_rational_integer_in_istream)
{
	std::istringstream strm("-1/2");
	strm >> rational;
	VerifyRational(rational, -1, 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()