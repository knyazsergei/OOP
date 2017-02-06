#include "stdafx.h"
#include "UrlParsingError.h"
#include <string>
#include <iostream>




CUrlParsingError::CUrlParsingError(const std::string & msg) : std::invalid_argument(msg)
{
	std::cout << msg << std::endl;
}
