// parseUrl.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "parseUrl.h"

using namespace std;

int main()
{
	string url;
	cout << "Enter url:";
	cin >> url;
	ParsedUrl result = ParseURL(url);

	if (result.error != "")
	{
		cout << result.error << endl;
		return EXIT_FAILURE;
	}
	cout << "ERROR:" << result.error << endl;
	cout << "HOST:" << result.host << endl;
	cout << "PORT:" << result.port << endl;
	cout << "DOC:" << result.document << endl;
	return EXIT_SUCCESS;
}

