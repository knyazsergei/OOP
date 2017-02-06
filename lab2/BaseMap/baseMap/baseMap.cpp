// baseMap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "Calculate.h"
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <functional>
//#include <boost/algorithm/string.hpp>    

using namespace std;
int main()
{
	vector<string> words;
	string text;//for test = "Hello world, how are you? hello";
	cin >> text;
	getline(cin, text);
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	//If you have boost, then use:
	//boost::algorithm::to_lower(text);
	string line;

	remove_copy_if(text.begin(), text.end(),
		back_inserter(line),
		ptr_fun<int, int>(&ispunct)
		);

	istringstream iss(line);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(words));

	map<string, size_t> result = CalculateCountOfWords(words);
	
	for (auto word : result)
	{
		cout << word.first << ": " << word.second << endl;
	}
	
	return 0;
}

