// http_url.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "HttpUrl.h"
#include <iostream>

int main()
{
	CHttpUrl url("http://yandex.ru:36");
	std:: cout << url.GetPort();
	return 0;
}

