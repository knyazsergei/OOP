// Shapes_Tests.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"

#include "stdafx.h"
#include "../Shapes/LineSegment.h"
#include "../Shapes//Triangle.h"

//can create a point

struct PointFixture
{
	CDot point;
	PointFixture()
		: point({ 15, 30 })
	{};
};

BOOST_FIXTURE_TEST_SUITE(point_test, PointFixture)

BOOST_AUTO_TEST_CASE(point_has_predetermined_position)
{
	BOOST_CHECK_EQUAL(point.m_position.x, 15);
	BOOST_CHECK_EQUAL(point.m_position.y, 30);
}

BOOST_AUTO_TEST_CASE(a_point_is_black_by_default)
{
	sf::Color blackColor(0, 0, 0);
	BOOST_CHECK_EQUAL(point.GetBorderColor().r, blackColor.r);
	BOOST_CHECK_EQUAL(point.GetBorderColor().g, blackColor.g);
	BOOST_CHECK_EQUAL(point.GetBorderColor().b, blackColor.b);
}

BOOST_AUTO_TEST_CASE(a_point_has_zero_area)
{
	BOOST_CHECK_EQUAL(point.GetSquare(), 0);
}

BOOST_AUTO_TEST_CASE(a_point_has_zero_perimeter)
{
	BOOST_CHECK_EQUAL(point.GetPerimeter(), 0);
}

BOOST_AUTO_TEST_CASE(point_has_a_string_representation)
{
	auto str = "Point: Pos <15.00,30.00>; P = 0.00; S = 0.00";
	BOOST_CHECK_EQUAL(point.GetStringRepresentation(), str);
}

BOOST_AUTO_TEST_SUITE_END()

//can create a line segment
//
//struct LineFixture
//{
//	CLineSegment line;
//	LineFixture()
//		: line({ 10, 10 }, { 20, 20 }, sf::Color(138, 138, 138))
//	{};
//};
//
//BOOST_FIXTURE_TEST_SUITE(line_tests, LineFixture)
//
//BOOST_AUTO_TEST_CASE(first_point_of_line_has_predetermined_position)
//{
//	BOOST_CHECK_EQUAL(line.GetPosOfFirstPoint().x, 10);
//	BOOST_CHECK_EQUAL(line.GetPosOfFirstPoint().y, 10);
//}
//
//BOOST_AUTO_TEST_CASE(second_point_of_line_has_predetermined_position)
//{
//	BOOST_CHECK_EQUAL(line.GetPosOfSecondPoint().x, 20);
//	BOOST_CHECK_EQUAL(line.GetPosOfSecondPoint().y, 20);
//}
//
//BOOST_AUTO_TEST_CASE(line_has_color_set_in_the_constructor)
//{
//	Color color(138, 138, 138);
//	BOOST_CHECK_EQUAL(line.GetLineColor().r, color.r);
//	BOOST_CHECK_EQUAL(line.GetLineColor().g, color.g);
//	BOOST_CHECK_EQUAL(line.GetLineColor().b, color.b);
//}
//
//BOOST_AUTO_TEST_CASE(line_has_zero_area)
//{
//	BOOST_CHECK_EQUAL(line.GetShapesSquare(), 0);
//}
//
//BOOST_AUTO_TEST_CASE(perimeter_is_equal_length_of_segment)
//{
//	Vector2f firstPoint = line.GetPosOfFirstPoint();
//	Vector2f secondPoint = line.GetPosOfSecondPoint();
//	float length = sqrtf(pow((firstPoint.x - secondPoint.x), 2) + pow((firstPoint.y - secondPoint.y), 2));
//
//	BOOST_CHECK_EQUAL(line.GetShapesPerimeter(), length);
//}
//
//BOOST_AUTO_TEST_CASE(line_has_string_representation)
//{
//	auto str = "LineSegment: First point pos <10.00,10.00>, Second point pos <20.00,20.00>; P = 14.14; S = 0.00";
//	BOOST_CHECK_EQUAL(line.ToString(), str);
//}
//
//BOOST_AUTO_TEST_SUITE_END()
//
////can create a circle
//
//struct CircleFixture
//{
//	CCircle circle;
//	CircleFixture()
//		: circle({ 20, 20 }, 10, Color(135, 135, 135), Color(204, 204, 204))
//	{};
//};
//
//BOOST_FIXTURE_TEST_SUITE(circle_tests, CircleFixture)
//
//BOOST_AUTO_TEST_CASE(circle_has_a_position)
//{
//	BOOST_CHECK_EQUAL(circle.GetPosition().x, 20);
//	BOOST_CHECK_EQUAL(circle.GetPosition().y, 20);
//}
//
//BOOST_AUTO_TEST_CASE(circle_has_a_radius)
//{
//	BOOST_CHECK_EQUAL(circle.GetRadius(), 10);
//}
//
//BOOST_AUTO_TEST_CASE(circle_has_a_line_color)
//{
//	BOOST_CHECK_EQUAL(circle.GetLineColor().r, 135);
//	BOOST_CHECK_EQUAL(circle.GetLineColor().g, 135);
//	BOOST_CHECK_EQUAL(circle.GetLineColor().b, 135);
//}
//
//BOOST_AUTO_TEST_CASE(circle_has_a_fill_color)
//{
//	BOOST_CHECK_EQUAL(circle.GetFillColor().r, 204);
//	BOOST_CHECK_EQUAL(circle.GetFillColor().g, 204);
//	BOOST_CHECK_EQUAL(circle.GetFillColor().b, 204);
//}
//
//BOOST_AUTO_TEST_CASE(can_find_area)
//{
//	BOOST_CHECK_EQUAL(int(circle.GetShapesSquare()), 314);
//}
//
//BOOST_AUTO_TEST_CASE(can_find_perimeter)
//{
//	BOOST_CHECK_EQUAL(int(circle.GetShapesPerimeter()), 62);
//}
//
//BOOST_AUTO_TEST_SUITE_END()
//
////can create a rectangle
//
//struct RectangleFixture
//{
//	CRectangle rect;
//	RectangleFixture()
//		: rect({ 60, 60 }, { 100, 30 }, Color(175, 125, 115), Color(214, 224, 234))
//	{};
//};
//
//
//BOOST_FIXTURE_TEST_SUITE(rectangle_tests, RectangleFixture)
//
//BOOST_AUTO_TEST_CASE(rect_has_a_position)
//{
//	BOOST_CHECK_EQUAL(rect.GetPosition().x, 60);
//	BOOST_CHECK_EQUAL(rect.GetPosition().y, 60);
//}
//
//BOOST_AUTO_TEST_CASE(rect_has_a_proportion)
//{
//	BOOST_CHECK_EQUAL(rect.GetProportions().x, 100);
//	BOOST_CHECK_EQUAL(rect.GetProportions().y, 30);
//}
//
//BOOST_AUTO_TEST_CASE(rect_has_a_line_color)
//{
//	BOOST_CHECK_EQUAL(rect.GetLineColor().r, 175);
//	BOOST_CHECK_EQUAL(rect.GetLineColor().g, 125);
//	BOOST_CHECK_EQUAL(rect.GetLineColor().b, 115);
//}
//
//BOOST_AUTO_TEST_CASE(circle_has_a_fill_color)
//{
//	BOOST_CHECK_EQUAL(rect.GetFillColor().r, 214);
//	BOOST_CHECK_EQUAL(rect.GetFillColor().g, 224);
//	BOOST_CHECK_EQUAL(rect.GetFillColor().b, 234);
//}
//
//BOOST_AUTO_TEST_CASE(can_find_area)
//{
//	BOOST_CHECK_EQUAL(int(rect.GetShapesSquare()), 3000);
//}
//
//BOOST_AUTO_TEST_CASE(can_find_perimeter)
//{
//	BOOST_CHECK_EQUAL(int(rect.GetShapesPerimeter()), 260);
//}
//
//BOOST_AUTO_TEST_SUITE_END()
//
////can create a triangle
//
//struct TriangleFixture
//{
//	CTriangle triangle;
//	TriangleFixture()
//		: triangle({ 20, 0 }, { 0, 20 }, { 20, 20 }, Color(123, 125, 255), Color(12, 4, 234))
//	{};
//};
//
//
//BOOST_FIXTURE_TEST_SUITE(triangle_tests, TriangleFixture)
//
//BOOST_AUTO_TEST_CASE(top_vertex_of_triangle_has_a_position)
//{
//	BOOST_CHECK_EQUAL(triangle.GetTopVertexPos().x, 20);
//	BOOST_CHECK_EQUAL(triangle.GetTopVertexPos().y, 0);
//}
//
//BOOST_AUTO_TEST_CASE(left_vertex_of_triangle_has_a_position)
//{
//	BOOST_CHECK_EQUAL(triangle.GetLeftVertexPos().x, 0);
//	BOOST_CHECK_EQUAL(triangle.GetLeftVertexPos().y, 20);
//}
//
//BOOST_AUTO_TEST_CASE(right_vertex_of_triangle_has_a_position)
//{
//	BOOST_CHECK_EQUAL(triangle.GetRightVertexPos().x, 20);
//	BOOST_CHECK_EQUAL(triangle.GetRightVertexPos().y, 20);
//}
//
//BOOST_AUTO_TEST_CASE(triangle_has_a_line_color)
//{
//	BOOST_CHECK_EQUAL(triangle.GetLineColor().r, 123);
//	BOOST_CHECK_EQUAL(triangle.GetLineColor().g, 125);
//	BOOST_CHECK_EQUAL(triangle.GetLineColor().b, 255);
//}
//
//BOOST_AUTO_TEST_CASE(triangle_has_a_fill_color)
//{
//	BOOST_CHECK_EQUAL(triangle.GetFillColor().r, 12);
//	BOOST_CHECK_EQUAL(triangle.GetFillColor().g, 4);
//	BOOST_CHECK_EQUAL(triangle.GetFillColor().b, 234);
//}
//
//BOOST_AUTO_TEST_CASE(can_find_area)
//{
//	BOOST_CHECK_EQUAL(int(triangle.GetShapesSquare()), 200);
//}
//
//BOOST_AUTO_TEST_CASE(can_find_perimeter)
//{
//	BOOST_CHECK_EQUAL(int(triangle.GetShapesPerimeter()), 68);
//}
//
//BOOST_AUTO_TEST_SUITE_END()


//#include <boost/test/output/compiler_log_formatter.hpp>
//
//
//class SpecLogFormatter :
//	public boost::unit_test::output::compiler_log_formatter
//{
//public:
//	SpecLogFormatter() : m_indent(0) {}
//private:
//	void test_unit_start(std::ostream &os,
//		boost::unit_test::test_unit const& tu)
//	{
//		os << std::string(m_indent, ' ') <<
//			boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
//		m_indent += 2;
//	}
//	void test_unit_finish(std::ostream &os,
//		boost::unit_test::test_unit const& tu, unsigned long elapsed)
//	{
//		elapsed;
//		tu;
//		os;
//		m_indent -= 2;
//	}
//	int m_indent;
//};
//
//
//boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
//{
//	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
//	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
//	return 0;
//}
//
//
//int main(int argc, char* argv[])
//{
//	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
//}