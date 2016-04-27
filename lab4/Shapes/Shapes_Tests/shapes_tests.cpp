#include "stdafx.h"

#include "../Shapes/Dot.h"
#include <iostream>

struct DotFixture
{
	CDot dot;
	DotFixture()
		: dot(10, 10)
	{};
};

BOOST_FIXTURE_TEST_SUITE(point_test, DotFixture)

BOOST_AUTO_TEST_CASE(point_has_predetermined_position)
{
	BOOST_CHECK_EQUAL(dot.m_position.x, 10);
	BOOST_CHECK_EQUAL(dot.m_position.y, 10);
}

BOOST_AUTO_TEST_CASE(a_point_is_black_by_default)
{
	sf::Color blackColor(0, 0, 0);
	BOOST_CHECK_EQUAL(dot.GetBorderColor().r, blackColor.r);
	BOOST_CHECK_EQUAL(dot.GetBorderColor().g, blackColor.g);
	BOOST_CHECK_EQUAL(dot.GetBorderColor().b, blackColor.b);
}

BOOST_AUTO_TEST_CASE(a_point_has_zero_area)
{
	BOOST_CHECK_EQUAL(dot.GetSquare(), 0);
}

BOOST_AUTO_TEST_CASE(a_point_has_zero_perimeter)
{
	BOOST_CHECK_EQUAL(dot.GetPerimeter(), 0);
}

BOOST_AUTO_TEST_CASE(point_has_a_string_representation)
{
	auto str = "Point: Pos <15.00,30.00>; P = 0.00; S = 0.00";
	std::cout << dot.GetStringRepresentation() << std::endl;
	BOOST_CHECK_EQUAL(dot.GetStringRepresentation(), str);
}


BOOST_AUTO_TEST_SUITE_END()
