#pragma once
#include <string>
#include <boost/utility/string_ref.hpp>
#include <ctype.h>
#include <cctype>
#include "UrlParsingError.h"
#include <boost/lexical_cast.hpp>


enum Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CHttpUrl
{
public:
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
	��� �������������� ������� ���������� ����������� ����������
	std::invalid_argument
	���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � URL �� ������ ����������
	std::string GetURL()const;

	// ���������� �������� ���
	std::string GetDomain()const;

	/*
	���������� ��� ���������. �������:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument()const;

	// ���������� ��� ���������
	Protocol GetProtocol()const;

	// ���������� ����� �����
	unsigned short GetPort()const;



private:
	bool ValidateDocument(const boost::string_ref & document);
	bool CHttpUrl::ValidateDomainName(const boost::string_ref & domain);
	bool ValidatePort(const unsigned port);

	Protocol ParseProtocol(boost::string_ref & str)const;
	boost::string_ref ParseDomain(boost::string_ref & str)const;
	unsigned short ParsePort(boost::string_ref & str)const;
	std::string ParseDocument(const boost::string_ref & str)const;

	std::string ToStringProtocol()const;
	Protocol ToProtocolString(const boost::string_ref & str)const;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
