// MyArray.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MyArray.h"
#include <iostream>
#include <typeinfo>
#include <array>


int main()
{
	/*arr.PushBack(1);
	std::cout << arr.GetSize() << '=' << 1 << std::endl;

	CMyArray<float> arr1({ 1.0f, 2.0f, 3.0f });
	CMyArray<int> arr2({ 1, 2, 3 });
	CMyArray<int> newArr1(arr1);

	auto newArr2 = static_cast<CMyArray<float>>(arr2);
	CMyArray<float> newArr3;
	newArr3 = arr2;


	std::cout << "size " << newArr2.GetSize() << std::endl;
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		std::cerr << arr1[i]
			<< " " << arr2[i]
			<< " " << newArr1[i]
			<< " " << newArr2[i]
			<< " " << newArr3[i]
			<< std::endl;
		std::cerr << "type " << ((typeid(arr1[i]).hash_code() == typeid(newArr3[i]).hash_code()) ? "changed" : "is not changed") << std::endl;
	}
	std::cerr << "\nsize of arr1: " << arr1.GetSize() << std::endl;
	std::cerr << "Get last element: " << arr2.GetBack() << std::endl;

	std::cout << "\nrange based for working:\n";

	for (auto it : arr2)
	{
		std::cerr << it;
	}

	std::cout << "\n\ncopy to ostream: \n";
	std::copy(arr1.begin(), arr1.end(), std::ostream_iterator<float>(std::cout, " "));*/
	struct ArrayItem
	{
		ArrayItem(int value = 0) : value(value)
		{}
		int value;
	};

	CMyArray<ArrayItem> arr;
	arr.PushBack(ArrayItem());

	arr.PushBack(ArrayItem());

	arr.PushBack(ArrayItem());

	arr.PushBack(ArrayItem());

	arr.PushBack(ArrayItem());

	arr.PushBack(ArrayItem());
	return 0;
}

