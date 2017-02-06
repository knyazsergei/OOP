#pragma once
#include <string>
#include <map>
#include <boost/regex.hpp>
#include <iostream>

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21
};

struct ParsedUrl
{
	unsigned port;
	std::string host;
	std::string document;
	std::string error = "";
};

ParsedUrl ParseURL(std::string  & url);