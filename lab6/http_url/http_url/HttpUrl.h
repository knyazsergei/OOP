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
		Protocol protocol,
		unsigned short port);

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
