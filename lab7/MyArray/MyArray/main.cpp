// MyArray.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MyArray.h"
#include <iostream>

int main()
{
	CMyArray<int> arr(10, 1);
	CMyArray<int> arr2({ 1, 2, 3 });
	std::cerr << arr.GetSize();
	std::cerr << arr2.GetBack();
	return 0;
}

