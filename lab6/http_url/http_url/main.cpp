// http_url.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "UrlParsingError.h"
#include <iostream>

int main()
{
	CHttpUrl url("https://habrahabr.ru/post/64226/");
	std:: cout << url.GetURL();
	return 0;
}

