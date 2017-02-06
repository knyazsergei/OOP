#pragma once
#include <stdexcept>
#include <boost/utility/string_ref.hpp>

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string & msg);
};
