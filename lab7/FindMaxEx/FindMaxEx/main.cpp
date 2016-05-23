// FindMaxEx.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "findMax.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	std::string s1, s2;
	// Считываем строки в переменные s1 и s2
	getline(cin, s1);
	getline(cin, s2);

	// Получаем указатели на хранящиеся в строках массивы символов
	const char* p1 = s1.c_str();
	const char* p2 = s2.c_str();

	// Упорядочиваем указатели в лексикографическом порядке
	Sort2(p1, p2);

	// Выводим результат output 
	cout << p1 << "\n" << p2 << "\n";

    return EXIT_SUCCESS;
}

