// http_url.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "HttpUrl.h"
#include <iostream>

int main()
{
	
	std::cout << CHttpUrl("https://vk.com:80/index.php").GetURL() << " == " << "http://vk.com:80/index.php" << std::endl;
	return 0;
}

