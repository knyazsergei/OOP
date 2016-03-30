// parseUrl_Tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../parseUrl/parseUrl.h"

BOOST_AUTO_TEST_SUITE(Test_parse_url)

BOOST_AUTO_TEST_CASE(exampleFromDocument)
{
	
	ParsedUrl realResult;
	realResult.host = "www.mysite.com";
	realResult.port = 80;
	realResult.document = "/docs/document1.html?page=30&lang=en#title1";
	std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithHTTPS)
{
	ParsedUrl realResult;
	realResult.host = "www.mysite.com";
	realResult.port = 443;
	realResult.document = "/docs/document1.html?page=30&lang=en#title1";
	std::string url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithFTP)
{
	ParsedUrl realResult;
	realResult.host = "www.mysite.com";
	realResult.port = 21;
	realResult.document = "/docs/document1.html?page=30&lang=en#title1";
	std::string url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithDifferentHost)
{
	ParsedUrl realResult;
	realResult.host = "mysite.com";
	realResult.port = 443;
	realResult.document = "/docs/document1.html?page=30&lang=en#title1";
	std::string url = "https://mysite.com/docs/document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithDifferentDocument)
{
	ParsedUrl realResult;
	realResult.host = "mysite.com";
	realResult.port = 443;
	realResult.document = "/docs/./document1.html?page=30&lang=en#title1";
	std::string url = "https://mysite.com/docs/./document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithOutProtocol)
{
	std::string url = "://mysite.com/docs/./document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK(!result.error.empty());
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithBitPort)
{
	std::string url = "https://mysite.com:99999/docs/./document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK(result.error != "");
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithDifferentHttp)
{
	std::string url = "HTTP://mysite.com:99999/docs/./document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK(result.error != "");
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithDifferentHttpLo)
{
	std::string url = "HTTP://mysite.com:99999/docs/./document1.html?page=30&lang=en#title1";
	ParsedUrl result = ParseURL(url);
	BOOST_CHECK(result.error != "");
}

BOOST_AUTO_TEST_SUITE_END()