#include "stdafx.h"
#include "EncodeHtml.h"

string Replace(const string & text, const string & searchPattern, const string & replacementText)
{
	if (searchPattern.empty())
	{
		return text;
	}
	string newText;

	size_t position = 0;
	size_t oldPosition = 0;

	while ((position = text.find(searchPattern, position)) != string::npos)
	{
		newText.append(text, oldPosition, position - oldPosition).append(replacementText);
		position += searchPattern.length();
		oldPosition = position;
	}
	newText.append(text, oldPosition);
	return newText;
}

string EncodeHtml(string & text)
{
	static vector<pair<string, string>> htmlSynonym = {
		{ "<", "&lt;" },
		{ ">", "&gt;" },
		{ "\"", "&quot;" },
		{ "\'", "&apos;" },
		{ "&", "&amp;" }
	};
	for (auto it : htmlSynonym)
	{
		text = Replace(text, it.second, it.first);
	}
	return text;
}