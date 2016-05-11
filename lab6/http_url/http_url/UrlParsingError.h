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
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
	ѕри недопустимости входных параметров выбрасывает исключение
	std::invalid_argument
	≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol = HTTP,
		unsigned short port = 80);

	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в URL не должен включатьс€
	std::string GetURL()const;

	// возвращает доменное им€
	std::string GetDomain()const;

	/*
	¬озвращает им€ документа. ѕримеры:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument()const;

	// возвращает тип протокола
	Protocol GetProtocol()const;

	// возвращает номер порта
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
