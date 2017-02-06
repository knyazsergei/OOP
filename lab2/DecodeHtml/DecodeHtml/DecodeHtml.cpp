#include "stdafx.h"
#include "DecodeHtml.h"
#include <boost/utility/string_ref.hpp>

string DecodeHtml(const string & text)
{
	map<string, string> htmlSynonym = {
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&quot;", "\"" },
		{ "&apos;", "\'" },
		{ "&amp;" , "&"}
	};
	string result = "";
	bool replaced = false;
	for (size_t i = 0; i < text.size(); ++i)
	{
		if (text[i] == '&')
		{
			replaced = false;
			for (auto synonym : htmlSynonym)
			{
				if (text.substr(i, synonym.first.size()) == synonym.first)
				{
					result.append(synonym.second);
					i += synonym.first.size() - 1;
					replaced = true;
					break;
				}
			}
			if (!replaced)
			{
				result += text[i];
			}
		}
		else
		{
			result += text[i];
		}
	}
	return result;
}