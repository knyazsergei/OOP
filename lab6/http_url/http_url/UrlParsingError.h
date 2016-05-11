#pragma once
#include <stdexcept>
#include <boost/utility/string_ref.hpp>
#include <ctype.h>

enum Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string & msg);
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
		Protocol = HTTP,
		unsigned short port = 80);

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
	bool ValidationDocument(const std::string & document);
	bool CHttpUrl::ValidationDomainName(const std::string & domain);

	bool ValidationDocument(const boost::string_ref & document);
	bool CHttpUrl::ValidationDomainName(const boost::string_ref & domain);
	
	bool ValidationPort(const unsigned port);

	Protocol ParseProtocol(const std::string & str)const;
	Protocol ParseProtocol(boost::string_ref & str)const;

	std::string ParseDomain(const std::string & str)const;
	boost::string_ref ParseDomain(boost::string_ref & str)const;

	unsigned short ParsePort(const std::string & str)const;
	unsigned short ParsePort(boost::string_ref & str)const;

	std::string ParseDocument(const std::string & str)const;
	std::string ParseDocument(const boost::string_ref & str)const;
	
	std::string ToStringProtocol()const;

	Protocol ToProtocolString(const std::string & str)const;
	Protocol ToProtocolString(const boost::string_ref & str)const;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
