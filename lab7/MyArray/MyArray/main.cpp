 //MyArray.cpp: определяет точку входа для консольного приложения.


#include "stdafx.h"
#include "MyArray.h"
#include <iostream>


int main()
{
	
	CMyArray<int> arr1;
	arr1.Resize(10);
	arr1.Clear();
	arr1.GetSize();
	return 0;
}

