#include "stdafx.h"
#include "UrlParsingError.h"
#include <string>
#include <iostream>
#include <cctype>



CUrlParsingError::CUrlParsingError(const std::string & msg): std::invalid_argument(msg)
{
	std::cout << msg << std::endl;
}

CHttpUrl::CHttpUrl(const std::string & url)
{
		auto m_url = boost::string_ref(url);
		//protocol
		m_protocol = ParseProtocol(m_url);
		//domain
		boost::string_ref domain = ParseDomain(m_url);
		if (!ValidationDomainName(domain))
		{
			throw CUrlParsingError("Invalid domain");
		}
		m_domain = domain.to_string();
		//port
		unsigned short port = ParsePort(m_url);
		if (!ValidationPort(port))
		{
			throw CUrlParsingError("Invalid port");
		}
		m_port = port;
		//doc
		auto document = ParseDocument(m_url);
		if (!ValidationDocument(document))
		{
			throw CUrlParsingError("Invalid document");
		}
		m_document = document;
		/*
		m_protocol = ParseProtocol(url);
		m_domain = ParseDomain(url);
		try
		{
			m_port = ParsePort(url);
		}
		catch (...)
		{
			m_port = m_protocol;
		}
		
		m_document = ParseDocument(url);
		*/
	
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port) 
{
	if (!ValidationDomainName(domain))
	{
		throw CUrlParsingError("Invalid domain");
	}
	if (!ValidationDocument(document))
	{
		throw CUrlParsingError("Invald document");
	}
	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
	if (port == 80 && m_protocol == Protocol::HTTPS)
	{
		m_port = 443;
	}
	
}

std::string CHttpUrl::GetURL() const
{
	return ToStringProtocol() + "://" 
		+ m_domain
		+ ((m_port == 80 || m_port == 443) ? "" : ":" + std::to_string(m_port))
		+ m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

Protocol CHttpUrl::ParseProtocol(const std::string & str)const
{
	auto schemePos = str.find("://");

	if (schemePos == std::string::npos)
	{
		throw CUrlParsingError("Protocol parsing error.");
	}
	
	return ToProtocolString(str.substr(0, schemePos));
}

Protocol CHttpUrl::ParseProtocol(boost::string_ref & str)const
{
	const std::string schemeDelimiter = "://";
	auto schemePos = str.find(schemeDelimiter);
	if (schemePos == boost::string_ref::npos)
	{
		throw CUrlParsingError("Protocol parsing error.");
	}
	auto protocol = str;
	protocol.remove_suffix(str.size() - schemePos);
	str.remove_prefix(schemePos + 3);
	return ToProtocolString(protocol);

}

std::string CHttpUrl::ParseDomain(const std::string & str) const
{
	size_t domainStart = str.find("://");

	if (domainStart == std::string::npos)
	{
		domainStart = 0;
	}
	else
	{
		domainStart += 3;
	}
	size_t domainEnd = str.find(':', domainStart);

	if (domainEnd == std::string::npos)
	{
		domainEnd = str.find("/", domainStart);
		if (domainEnd == std::string::npos)
		{
			domainEnd = str.length();
		}
	}
	return str.substr(domainStart, domainEnd - domainStart);
}

boost::string_ref CHttpUrl::ParseDomain(boost::string_ref & str) const
{
	size_t domainEnd = str.find(':');

	if (domainEnd == boost::string_ref::npos)
	{
		domainEnd = str.find("/");
		if (domainEnd == boost::string_ref::npos)
		{
			domainEnd = str.length();
		}
	}
	auto domain = str;
	domain.remove_suffix(str.size() - domainEnd);
	str.remove_prefix(domainEnd);
	return domain;
}

bool IsNumber(const std::string& s)
{	
	for (auto it : s)
	{
		if (!std::isdigit(it))
		{
			return false;
		}
	}
	return true;
}

unsigned short CHttpUrl::ParsePort(const std::string & str)const
{
	auto domainStart = str.find("://");
	if (domainStart == std::string::npos)
	{
		domainStart = 0;
	}
	else
	{
		domainStart += 3;
	}
	auto domainAndPortEnd = str.find('/', domainStart);
	if (domainAndPortEnd == std::string::npos)
	{
		domainAndPortEnd = str.length();
	}
	auto domainAndPort = str.substr(domainStart, domainAndPortEnd - domainStart);
	auto portStart = domainAndPort.find(':');
	if (portStart == std::string::npos)
	{
		return ParseProtocol(str);
	}
	++portStart;
	std::string port = domainAndPort.substr(portStart).c_str();

	if (!IsNumber(port))
	{
		throw CUrlParsingError("Port parsing error.");
	}
	return atoi(port.c_str());
}

unsigned short CHttpUrl::ParsePort(boost::string_ref & str) const
{
	auto port = str;
	if (str[0] == ':')
	{
		port.remove_prefix(1);
		auto portEnd = str.find('/');
		if (portEnd != boost::string_ref::npos)
		{
			port.remove_suffix(port.size() - portEnd + 1);
		}
		str.remove_prefix(portEnd);
		auto portStr = port.to_string();
		if (!IsNumber(portStr) || portStr.empty())
		{
			throw CUrlParsingError("Port parsing error.");
		}
		return atoi(port.to_string().c_str());
	}
	else
	{
		return static_cast<int>(m_protocol);
	}
	throw CUrlParsingError("Port parsing error.");
}

std::string CHttpUrl::ParseDocument(const std::string & str) const
{
	auto domainStart = str.find("://");
	if (domainStart == std::string::npos)
	{
		domainStart = 0;
	}
	else
	{
		domainStart += 3;
	}
	auto documentStart = str.find('/', domainStart);
	if (documentStart == std::string::npos)
	{
		return "";
	}
	return  str.substr(documentStart);
}

std::string CHttpUrl::ParseDocument(const boost::string_ref & str) const
{
	auto result = str.to_string();
	if (result.empty())
	{
		return "/";
	}
	return result;
}

std::string CHttpUrl::ToStringProtocol() const
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	};
	return "";
}

Protocol CHttpUrl::ToProtocolString(const std::string & str) const
{
	if (str == "http")
	{
		return Protocol::HTTP;
	}
	else if (str == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Invalid protocol  string representation " + str + " .");
}

Protocol CHttpUrl::ToProtocolString(const boost::string_ref & str) const
{
	return ToProtocolString(str.to_string());
}

bool CHttpUrl::ValidationDomainName(const std::string & domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Domain name is empty.");
	}
	
	if (std::find_if(domain.begin(), domain.end(), [&](char ch)
		{
			return (isspace(ch) || (ch == '/') || (ch == '\'')); 
		})
		!= domain.end())
	{
		throw CUrlParsingError("Domain name must not contains any spaces, tabulations or slashes.");
	}

	return true;
}

bool CHttpUrl::ValidationDocument(const boost::string_ref & document)
{
	
	if (std::find_if(document.begin(), document.end(), [&](char ch) {
		return (isspace(ch));
	}) != document.end())
	{
		throw CUrlParsingError("Document must not contain any spaces or tabulation.");
	}

	return true;
}

bool CHttpUrl::ValidationDomainName(const boost::string_ref & domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Domain name is empty.");
	}
	else if (std::find_if(domain.begin(), domain.end(), [&](char ch)
	{
		return (isspace(ch) || (ch == '/') || (ch == '\''));
	})
		!= domain.end())
	{
		throw CUrlParsingError("Domain name must not contains any spaces, tabulations or slashes.");
	}

	return true;
}


bool CHttpUrl::ValidationDocument(const std::string & document)
{
	if (find_if(document.begin(), document.end(), [&](char ch) {
		return (isspace(ch));
	}) != document.end())
	{
		throw CUrlParsingError("Document must not contain any spaces or tabulation.");
	}

	return true;
}

bool CHttpUrl::ValidationPort(const unsigned port)
{
	if (port > 0 && port < 49151)
	{
		return true;
	}
	return false;
}
