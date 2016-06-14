// MyArray.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MyArray.h"
#include <iostream>

int main()
{
	CMyArray<int> arr({ 1, 2, 3 });
	arr.Resize(10, 5);
	arr.Resize(5, 0);
	CMyArray<int> arr2(arr);
	std:: cerr << arr[7] << std::endl;
	arr.Clear();
	return 0;
}

