// EncodeHtml_Tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\EncodeHtml\EncodeHtml.h"


BOOST_AUTO_TEST_SUITE(EncodeStringElementsToHtmlEntities)

BOOST_AUTO_TEST_CASE(BoostTestReady)
{
	BOOST_CHECK_EQUAL(2 * 2, 4);
}

BOOST_AUTO_TEST_CASE(EncodeEmptyString)
{
	std::string str = "";
	BOOST_CHECK_EQUAL(EncodeHtml(str), "");
};

BOOST_AUTO_TEST_CASE(EncodeNotEmptyString)
{
	std::string testString = "&lt;hello&gt;world&lt;endHello&gt;Doyou&quot;&apos;&amp;";
	BOOST_CHECK_EQUAL(EncodeHtml(testString), "<hello>world<endHello>Doyou\"'&");
};

BOOST_AUTO_TEST_CASE(EncodeNotEmptyStringWithCollision)
{
	std::string testString = "&amp;lt;";
	BOOST_CHECK_EQUAL(EncodeHtml(testString), "&lt;");
};

BOOST_AUTO_TEST_SUITE_END()
