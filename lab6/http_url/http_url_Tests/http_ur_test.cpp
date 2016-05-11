#include "stdafx.h"
#include "../http_url/UrlParsingError.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(url_parser)

BOOST_AUTO_TEST_SUITE(url_string_representation)
BOOST_AUTO_TEST_CASE(no_throw_with_yandex_no_port_and_document)
{
	BOOST_REQUIRE_NO_THROW(CHttpUrl url("http://yandex.ru"));
}
BOOST_AUTO_TEST_CASE(throw_with_yandex_incorrect_url_with_space)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("http://yandex.ru k"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(throw_with_yandex_incorrect_protocol)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("ftp://yandex.ru"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(throw_with_yandex_extra_slash)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("http:///yandex.ru"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(throw_with_yandex_lack_of_slash)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("http:/yandex.ru"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(throw_with_no_domain)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("http://"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(no_throw_with_min_domain)
{
	BOOST_REQUIRE_NO_THROW(CHttpUrl url("http://y"));
}
BOOST_AUTO_TEST_CASE(throw_with_incorrect_domain)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("http://y an/post"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(throw_with_yandex_incorrect_port)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("http://yandex.ru:s"), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(no_throw_with_yandex_correct_port)
{
	BOOST_REQUIRE_NO_THROW(CHttpUrl url("http://yandex.ru:36"));
}
BOOST_AUTO_TEST_CASE(parse_habra_OK)
{
	CHttpUrl url("https://habrahabr.ru/post/64226/");

	BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTPS);
	auto domain = url.GetDomain();
	std::cout << domain << std::endl;
	BOOST_CHECK_EQUAL(url.GetDomain(), "habrahabr.ru");
	BOOST_CHECK_EQUAL(url.GetPort(), 443);
	BOOST_CHECK_EQUAL(url.GetDocument(), "/post/64226/");
	BOOST_CHECK_EQUAL(url.GetURL(), "https://habrahabr.ru/post/64226/");
}

BOOST_AUTO_TEST_CASE(without_doc)
{
	CHttpUrl url("http://yandex.ru");

	BOOST_CHECK_EQUAL(url.GetDocument(), "/");
	BOOST_CHECK_EQUAL(url.GetURL(), "http://yandex.ru/");
}


BOOST_AUTO_TEST_CASE(check_incorrect_port)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("http://yandex.ru:999999999"), CUrlParsingError);
	BOOST_REQUIRE_THROW(CHttpUrl url("http://localhost:/index.php"), CUrlParsingError);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(url_parse_with_arguments)
BOOST_AUTO_TEST_CASE(no_throw_with_yandex_arguments)
{
	BOOST_REQUIRE_NO_THROW(CHttpUrl url("yandex.ru", "/pogoda", Protocol::HTTP, 78));
}
BOOST_AUTO_TEST_CASE(throw_with_yandex_domain_and_space)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("yande x.ru", "/pogoda", Protocol::HTTP, 78), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(throw_with_yandex_document_and_space)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("yandex.ru", "/po goda", Protocol::HTTP, 78), CUrlParsingError);
	BOOST_REQUIRE_THROW(CHttpUrl url("yandex.ru", "/po goda/okay", Protocol::HTTP, 78), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(throw_with_yandex_empty_domain)
{
	BOOST_REQUIRE_THROW(CHttpUrl url("", "/pogoda", Protocol::HTTP, 78), CUrlParsingError);
	BOOST_REQUIRE_THROW(CHttpUrl url("  \t", "/pogoda", Protocol::HTTP, 78), CUrlParsingError);
}
BOOST_AUTO_TEST_CASE(no_throw_with_yandex_empty_document)
{
	BOOST_REQUIRE_NO_THROW(CHttpUrl url("yandex.ru", "", Protocol::HTTP, 78));
}
BOOST_AUTO_TEST_CASE(output_url_habra_post)
{
	CHttpUrl url("habrahabr.ru", "/post/252533/", Protocol::HTTPS, 80);
	BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTPS);
	BOOST_CHECK_EQUAL(url.GetDomain(), "habrahabr.ru");
	BOOST_CHECK_EQUAL(url.GetPort(), 443);
	BOOST_CHECK_EQUAL(url.GetDocument(), "/post/252533/");
	BOOST_CHECK_EQUAL(url.GetURL(), "https://habrahabr.ru/post/252533/");
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()