// parseUrl_Tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

BOOST_AUTO_TEST_SUITE(Test_RECT)

BOOST_AUTO_TEST_CASE(exampleFromDocument)
{

	parsedUrl realResult;
	realResult.host = "www.mysite.com";
	realResult.port = 80;
	realResult.document = "/docs/document1.html?page=30&lang=en#title1";
	std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title1";
	parsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithHTTPS)
{
	parsedUrl realResult;
	realResult.host = "www.mysite.com";
	realResult.port = 443;
	realResult.document = "/docs/document1.html?page=30&lang=en#title1";
	std::string url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title1";
	parsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithFTP)
{
	parsedUrl realResult;
	realResult.host = "www.mysite.com";
	realResult.port = 21;
	realResult.document = "/docs/document1.html?page=30&lang=en#title1";
	std::string url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title1";
	parsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithDifferentHost)
{
	parsedUrl realResult;
	realResult.host = "mysite.com";
	realResult.port = 443;
	realResult.document = "/docs/document1.html?page=30&lang=en#title1";
	std::string url = "https://mysite.com/docs/document1.html?page=30&lang=en#title1";
	parsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_CASE(exampleFromDocumentWithDifferentDocument)
{
	parsedUrl realResult;
	realResult.host = "mysite.com";
	realResult.port = 443;
	realResult.document = "/docs/./document1.html?page=30&lang=en#title1";
	std::string url = "https://mysite.com/docs/./document1.html?page=30&lang=en#title1";
	parsedUrl result = ParseURL(url);
	BOOST_CHECK_EQUAL(result.document, realResult.document);
	BOOST_CHECK_EQUAL(result.host, realResult.host);
	BOOST_CHECK_EQUAL(result.port, realResult.port);
}

BOOST_AUTO_TEST_SUITE_END()