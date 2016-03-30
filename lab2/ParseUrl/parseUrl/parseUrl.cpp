#include "stdafx.h"
#include "parseUrl.h"
#include <algorithm>

ParsedUrl ParseURL(std::string  & url)
{
	ParsedUrl result;
	transform(url.begin(), url.end(), url.begin(), ::tolower);
	boost::regex ex("(ftp|http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)");
	boost::cmatch what;
	if (regex_match(url.c_str(), what, ex))
	{
		result.port = atoi(std::string(what[3].first, what[3].second).c_str());
		if (result.port == 0)
		{
			Protocol protocol = Protocol::HTTP;
			std::string protocolStr = std::string(what[1].first, what[1].second);
			if (protocolStr == "")
			{
				result.error = "Invalid protocol";
				return result;
			}
			if (protocolStr == "http") {
				protocol = Protocol::HTTP;
			}
			else if (protocolStr == "https") {
				protocol = Protocol::HTTPS;
			}
			else if (protocolStr == "ftp") {
				protocol = Protocol::FTP;
			}
			result.port = static_cast<int>(protocol);
		}
		else if(result.port < 0 || result.port > 65535)
		{
			result.error = "Invalid port";
			return result;
		}
		result.host = std::string(what[2].first, what[2].second);
		result.document = std::string(what[4].first, what[6].second);
	}
	else
	{
		result.error = "Invalid document";
	}
	return result;
}