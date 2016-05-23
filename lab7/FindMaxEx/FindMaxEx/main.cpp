// FindMaxEx.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "findMax.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	std::string s1, s2;
	// ��������� ������ � ���������� s1 � s2
	getline(cin, s1);
	getline(cin, s2);

	// �������� ��������� �� ���������� � ������� ������� ��������
	const char* p1 = s1.c_str();
	const char* p2 = s2.c_str();

	// ������������� ��������� � ������������������ �������
	Sort2(p1, p2);

	// ������� ��������� output 
	cout << p1 << "\n" << p2 << "\n";

    return EXIT_SUCCESS;
}

