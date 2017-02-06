#include "stdafx.h"
#include "HttpUrl.h"
#include <clocale>
#include <iostream>

CHttpUrl::CHttpUrl(const std::string & url)
{
	auto urlRef = boost::string_ref(url);
	//protocol
	m_protocol = ParseProtocol(urlRef);
	//domain
	boost::string_ref domain = ParseDomain(urlRef);
	if (!ValidateDomainName(domain))
	{
		throw CUrlParsingError("Invalid domain");
	}
	m_domain = domain.to_string();
	//port
	unsigned short port = ParsePort(urlRef);
	if (!ValidatePort(port))
	{
		throw CUrlParsingError("Invalid port");
	}
	m_port = port;
	//doc
	auto document = ParseDocument(urlRef);
	if (!ValidateDocument(document))
	{
		throw CUrlParsingError("Invalid document");
	}
	m_document = document;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	if (!ValidateDomainName(domain))
	{
		throw CUrlParsingError("Invalid domain");
	}
	if (!ValidateDocument(document))
	{
		throw CUrlParsingError("Invalid document");
	}
	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
	if (ValidatePort(port))
	{
		m_port = port;
	}
	else
	{
		throw CUrlParsingError("Invalid port");
	}
}

std::string CHttpUrl::GetURL() const
{
	std::string port = ":" + std::to_string(m_port);
	if ((m_port == 80 && m_protocol == Protocol::HTTP) || (m_port == 443 && m_protocol == Protocol::HTTPS))
	{
		port = "";
	}
	return ToStringProtocol() + "://"
		+ m_domain
		+ port
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

		short int result;
		try
		{
			result = boost::lexical_cast<short int>(port);
		}
		catch (...)
		{
			throw CUrlParsingError("Invalid port");
		}
		return result;
	}
	else
	{
		return static_cast<int>(m_protocol);
	}
	throw CUrlParsingError("Port parsing error.");
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

Protocol CHttpUrl::ToProtocolString(const boost::string_ref & str) const
{
	if (str == "http")
	{
		return Protocol::HTTP;
	}
	else if (str == "https")
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError("Invalid protocol  string representation " + str.to_string() + " .");
}

bool CHttpUrl::ValidateDocument(const boost::string_ref & document)
{

	if (std::find_if(document.begin(), document.end(), [&](char ch) {
		return (isspace(ch));
	}) != document.end())
	{
		throw CUrlParsingError("Document must not contain any spaces or tabulation.");
	}

	return true;
}

bool CHttpUrl::ValidateDomainName(const boost::string_ref & domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Domain name is empty.");
	}
	else if ((std::find_if(domain.begin(), domain.end(), [&](char ch)
			{
				return (isspace(ch) || (ch == '/') || (ch == '\''));
			})!= domain.end()) ||
			(std::find_if(domain.begin(), domain.end(), [&](char ch)
			{
				return (ch == '.');
			}) == domain.end())
		)
	{
		throw CUrlParsingError("Domain name must not contains any spaces, tabulations or slashes.");
	}
	return true;
}

bool CHttpUrl::ValidatePort(const unsigned port)
{
	if (port > 0 && port < 49151)
	{
		return true;
	}
	return false;
}
